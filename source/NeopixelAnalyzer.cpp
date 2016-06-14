#include "NeopixelAnalyzer.h"
#include "NeopixelAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

NeopixelAnalyzer::NeopixelAnalyzer()
:	Analyzer(),  
	mSettings( new NeopixelAnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
}

NeopixelAnalyzer::~NeopixelAnalyzer()
{
	KillThread();
}

void NeopixelAnalyzer::WorkerThread()
{
	mResults.reset( new NeopixelAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mInputChannel );

	mSampleRateHz = GetSampleRate();

	mSerial = GetAnalyzerChannelData( mSettings->mInputChannel );

	if( mSerial->GetBitState() == BIT_LOW ) {
		// Go to rising edge
		mSerial->AdvanceToNextEdge();
	} else {
		// Go to falling edge
		mSerial->AdvanceToNextEdge();
		// Go to rising edge
		mSerial->AdvanceToNextEdge();
	}

	U32 samples_per_bit = mSampleRateHz / (mSettings->mBitRate * 1000);

	for( ; ; )
	{
		U8 data = 0;
		U8 mask = 1 << 7;

		U64 starting_sample = mSerial->GetSampleNumber();
		//let's put a dot exactly where we sample this byte
		mResults->AddMarker( starting_sample, AnalyzerResults::Dot, mSettings->mInputChannel );

		for( U32 i=0; i<8; i++ )
		{
			// At rising edge
			U64 rising_sample = mSerial->GetSampleNumber();
		
			// Go to falling edge
			mSerial->AdvanceToNextEdge();

			U64 falling_sample = mSerial->GetSampleNumber();

			if(falling_sample - rising_sample > samples_per_bit / 2) {
				data |= mask;
			}

			mask = mask >> 1;

			// Go to rising edge
			mSerial->AdvanceToNextEdge();
		}

		//we have a byte to save. 
		Frame frame;
		frame.mData1 = data;
		frame.mFlags = 0;
		frame.mStartingSampleInclusive = starting_sample;
		frame.mEndingSampleInclusive = mSerial->GetSampleNumber();

		mResults->AddFrame( frame );
		mResults->CommitResults();
		ReportProgress( frame.mEndingSampleInclusive );
	}
}

bool NeopixelAnalyzer::NeedsRerun()
{
	return false;
}

U32 NeopixelAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 NeopixelAnalyzer::GetMinimumSampleRateHz()
{
	return mSettings->mBitRate * 4;
}

const char* NeopixelAnalyzer::GetAnalyzerName() const
{
	return "Neopixel";
}

const char* GetAnalyzerName()
{
	return "Neopixel";
}

Analyzer* CreateAnalyzer()
{
	return new NeopixelAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}
