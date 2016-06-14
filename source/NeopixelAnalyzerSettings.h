#ifndef NEOPIXEL_ANALYZER_SETTINGS
#define NEOPIXEL_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class NeopixelAnalyzerSettings : public AnalyzerSettings
{
public:
	NeopixelAnalyzerSettings();
	virtual ~NeopixelAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;
	U32 mBitRate;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mBitRateInterface;
};

#endif //NEOPIXEL_ANALYZER_SETTINGS
