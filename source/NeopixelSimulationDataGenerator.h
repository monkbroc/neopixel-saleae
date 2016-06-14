#ifndef NEOPIXEL_SIMULATION_DATA_GENERATOR
#define NEOPIXEL_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class NeopixelAnalyzerSettings;

class NeopixelSimulationDataGenerator
{
public:
	NeopixelSimulationDataGenerator();
	~NeopixelSimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, NeopixelAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	NeopixelAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //NEOPIXEL_SIMULATION_DATA_GENERATOR