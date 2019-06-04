// ==========  AudioToolbox.framework/Headers/AudioCodec.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AudioCodec.h>)
/*==================================================================================================
     File:       AudioToolbox/AudioCodec.h

     Contains:   A component API for encoding/decoding audio data.

     Copyright:  (c) 1985-2015 by Apple, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

==================================================================================================*/
#ifndef AudioUnit_AudioCodec_h
#define AudioUnit_AudioCodec_h

/*!
	@header AudioCodec
 
	This header defines the property sets and the public API for various audio codecs.

	<h2>Theory of Operation</h2>
 
	AudioCodec components translate audio data from one format to another. There
	are three kinds of AudioCodec components. Decoder components ('adec') 
	translate data that isn't in linear PCM into linear PCM formatted data. 
	Encoder components ('aenc') translate linear PCM data into some other format. 
	Unity codecs ('acdc') translate between different flavors of the same type 
	(e.g. 16 bit signed integer linear PCM into 32 bit floating point linear PCM).
 
	AudioCodec components are standard components and are managed by the Component
	Manager.
 
	Once an AudioCodec is found that implements the translation in question,
	it has to be set up to do the translation. This can be done by setting the
	appropriate properties or by calling AudioCodecInitialize. If the translation
	is specified by properties, AudioCodecInitialize still needs to be called
	prior to appending input data or producing output data.
 
	AudioCodecInitialize puts the codec into the "initialized" state. In this state,
	the format information for the translation cannot be changed. The codec
	has to be in the initialized state for AudioCodecAppendInputData and
	AudioCodecProduceOutputData to work. They will return kAudioCodecStateError
	if the codec isn't initialized.
 
	AudioCodecUninitialize will return the codec to the uninitialized state and
	release any allocated resources. The codec may then be configured freely. It is not
	necessary to call AudioCodecUninitialize prior to closing the codec.
 
	Once in the initialized state, the codec is ready to receive input and produce
	output using the AudioCodecAppendInputData and AudioCodecProduceOutputData
	routines. Input data can be fed into an encoder and some decoders in any size (even 
	byte by byte). Input data fed to a decoder should be in terms of whole packets in the 
	encoded format if the format is variable bit rate and is not self framing (e.g. MPEG-4 AAC). 
	Output data can only be produced in whole packet sizes. Both routines will return 
	the amount of data they consume/produce.
 
	AudioCodecProduceOutputData also returns a status code to the caller that
	indicates the result of the operation (success or failure) as well as the
	state of the input buffer.
	
	The combination of AppendInputData and ProduceOutputPackets can be thought of a "push-pull"
	model of data handling. First, the input data is pushed into the component and the 
	resulting output data gets pulled out of that same component.
 
	Basic Workflow
	1. Find the appropriate codec component
	2. Open the codec component
	3. Configure it (AudioCodecGetPropertyInfo, AudioCodecGetProperty, AudioCodecSetProperty)
	4. AudioCodecInitialize
	5. Loop
		a. AppendInputData (EOF is signaled by passing a 0-sized buffer)
		b. ProduceOutputPackets
	6. Close the codec component
	
 */

//=============================================================================

#include <TargetConditionals.h>
#include <Availability.h>

#include <AudioToolbox/AudioComponent.h>

#if defined(__cplusplus)
extern "C"
{
#endif

CF_ASSUME_NONNULL_BEGIN

//=============================================================================
#pragma mark Types specific to AudioCodecs
//=============================================================================


typedef AudioComponentInstance	AudioCodec;
typedef UInt32					AudioCodecPropertyID;

/*!
    @struct AudioCodecMagicCookieInfo
 
	@abstract Structure holding the <em>magic cookie</em> information.
 
	@discussion Passed as input to AudioCodecGetProperty for kAudioCodecPropertyFormatList.
				The first four + sizeof(void *) bytes of the buffer pointed at by outPropertyData
				will contain this struct.
 
	@var   mMagicCookieSize
        The size of the magic cookie
	@var   mMagicCookie
        Generic const pointer to magic cookie
*/
struct AudioCodecMagicCookieInfo 
{
	UInt32					mMagicCookieSize;
	const void* __nullable	mMagicCookie;
};
typedef struct AudioCodecMagicCookieInfo	AudioCodecMagicCookieInfo;

//=============================================================================
#pragma mark AudioCodec Component Constants
//=============================================================================


#if !TARGET_OS_IPHONE
/*!
	@enum           AudioCodecComponentType
 
	@discussion     Collection of audio codec component types
 
	@constant		kAudioDecoderComponentType
					A codec that translates data in some other format into linear PCM.
					The component subtype specifies the format ID of the other format.
	@constant		kAudioEncoderComponentType
					A codec that translates linear PCM data into some other format
					The component subtype specifies the format ID of the other format
	@constant		kAudioUnityCodecComponentType
					A codec that translates between different flavors of the same format
					The component subtype specifies the format ID of this format.
*/
CF_ENUM(UInt32)
{
	kAudioDecoderComponentType								= 'adec',	
	kAudioEncoderComponentType								= 'aenc',	
	kAudioUnityCodecComponentType							= 'acdc'
};
#endif

//=============================================================================
#pragma	mark Global Codec Properties

//	Used with the AudioCodecXXXXPropertyXXXX family of routines.
//	All Audio Codec properties are readable only.
//=============================================================================

/*!
	@enum		AudioCodecGlobalProperty

	@discussion	These properties reflect the capabilities of the underlying codec.
				The values of these properties are independent of the codec's internal
				state.
				
				These properties can be read at any time the codec is open.

	@constant	kAudioCodecPropertySupportedInputFormats
					An array of AudioStreamBasicDescription structs describing what formats 
					the codec supports for input data
	@constant	kAudioCodecPropertySupportedOutputFormats
					An array of AudioStreamBasicDescription structs describing what formats 
					the codec supports for output data
 	@constant	kAudioCodecPropertyAvailableInputSampleRates
					An array of AudioValueRange indicating the valid ranges for the
					input sample rate of the codec.
					Required for encoders.
					(see also kAudioCodecPropertyApplicableInputSampleRates)
	@constant	kAudioCodecPropertyAvailableOutputSampleRates
					An array of AudioValueRange indicating the valid ranges for the
					output sample rate of the codec.
					Required for encoders.
					(see also kAudioCodecPropertyApplicableOutputSampleRates)
	@constant	kAudioCodecPropertyAvailableBitRateRange
					An array of AudioValueRange that indicate the target bit rates
					supported by the encoder. This can be total bit rate or bit
					rate per channel as appropriate. 
					This property is only relevant to encoders.
					(see also kAudioCodecPropertyApplicableBitRateRange)
	@constant	kAudioCodecPropertyMinimumNumberInputPackets
					A UInt32 indicating the minimum number of input packets
					that need to be supplied to the codec. The actual input the
					codec accepts could be less than this.
					For most codecs this value will be 1.
	@constant	kAudioCodecPropertyMinimumNumberOutputPackets
					A UInt32 indicating the minimum number of output packets
					that need to be handled from the codec. The actual output
					might be less than this.
					For most codecs this value will be 1.
	@constant	kAudioCodecPropertyAvailableNumberChannels
					An array of UInt32 that specifies the number of channels the codec is
					capable of encoding or decoding to. 0xFFFFFFFF means any number
					of channels.
	@constant	kAudioCodecPropertyDoesSampleRateConversion
					A UInt32 indicating if the codec wants to do a sample rate conversion (if 
					necessary) because it can do it in a way that is meaningful for quality.
					Value is 1 if true, 0 otherwise.
	@constant	kAudioCodecPropertyAvailableInputChannelLayoutTags
					An array of AudioChannelLayoutTag that specifies what channel layouts the codec is
					capable of using on input.
	@constant	kAudioCodecPropertyAvailableOutputChannelLayoutTags
					An array of AudioChannelLayoutTag that specifies what channel layouts the codec is
					capable of using on output.
	@constant	kAudioCodecPropertyInputFormatsForOutputFormat
					An array of AudioStreamBasicDescription indicating what the codec supports
					for input data given an output format that's passed in as the first member of
					the array (and is overwritten on the reply). Always a subset of 
					kAudioCodecPropertySupportedInputFormats
	@constant	kAudioCodecPropertyOutputFormatsForInputFormat
					An array of AudioStreamBasicDescription indicating what the codec supports
					for output data given an input format that's passed in as the first member of
					the array (and is overwritten on the reply). Always a subset of 
					kAudioCodecPropertySupportedOutputFormats
	@constant	kAudioCodecPropertyFormatInfo
					Takes an AudioFormatInfo on input. This AudioformatInfo is validated either through
					the provided magic cookie or the AudioStreamBasicDescription and where applicable,
					wildcards are overwritten with default values.
*/
CF_ENUM(AudioCodecPropertyID)
{
	kAudioCodecPropertySupportedInputFormats				= 'ifm#',
	kAudioCodecPropertySupportedOutputFormats				= 'ofm#',
	kAudioCodecPropertyAvailableInputSampleRates			= 'aisr',
	kAudioCodecPropertyAvailableOutputSampleRates			= 'aosr',
	kAudioCodecPropertyAvailableBitRateRange				= 'abrt',
	kAudioCodecPropertyMinimumNumberInputPackets			= 'mnip',
	kAudioCodecPropertyMinimumNumberOutputPackets			= 'mnop',
	kAudioCodecPropertyAvailableNumberChannels				= 'cmnc',
	kAudioCodecPropertyDoesSampleRateConversion				= 'lmrc',
	kAudioCodecPropertyAvailableInputChannelLayoutTags		= 'aicl',
	kAudioCodecPropertyAvailableOutputChannelLayoutTags		= 'aocl',
	kAudioCodecPropertyInputFormatsForOutputFormat			= 'if4o',		
	kAudioCodecPropertyOutputFormatsForInputFormat			= 'of4i',
	kAudioCodecPropertyFormatInfo							= 'acfi'
};

//=============================================================================
#pragma	mark Instance Codec Properties

//	Used with the AudioCodecXXXXPropertyXXXX family of routines.
//=============================================================================

/*!
	@enum			AudioCodecInstanceProperty
 
	@discussion		Properties which can be set or read on an instance of the
					underlying audio codec. These properties are dependent on the 
					codec's current state. A property may be read/write or read
					only, depending on the data format of the codec.
					
					These properties may have different values depending on whether the
					codec is initialized or not. All properties can be read at any time
					the codec is open. However, to ensure the codec is in a valid 
					operational state and therefore the property value is valid the codec
					must be initialized at the time the property is read.
					
					Properties that are writable are only writable when the codec
					is not initialized.
 
	@constant		kAudioCodecPropertyInputBufferSize
						A UInt32 indicating the maximum input buffer size for the codec
						in bytes. 
						Not writable, but can vary on some codecs depending on the bit stream 
						format being handled.
	@constant		kAudioCodecPropertyPacketFrameSize
						A UInt32 indicating the number of frames of audio data encapsulated in each
						packet of data in the codec's format. For encoders, this is the
						output format. For decoders this is the input format.
						Formats with variable frames per packet should return a maximum value 
						for this property.
						Not writable.
	@constant		kAudioCodecPropertyHasVariablePacketByteSizes
						A UInt32 where 0 indicates that all packets in the codec's format
						have the same byte size (sometimes referred to as CBR codecs),
						and 1 indicates that they vary in size (sometimes referred to as 
						VBR codecs). The maximum size of a variable packet is up to 
						the one indicated in kAudioCodecPropertyMaximumPacketByteSize.
						Any codec that reports 1 for this property must be able to handle packet
						descriptions, though it does not have to require them.
						May be writable.
	@constant		kAudioCodecPropertyEmploysDependentPackets
						A UInt32 where 0 indicates that all packets in the codec's format
						are independently decodable, and 1 indicates that some may not be
						independently decodable.
	@constant		kAudioCodecPropertyMaximumPacketByteSize
						A UInt32 indicating the maximum number of bytes a packet of data
						in the codec's format will be. If the format is constant bit rate,
						all packets will be this size. If it is variable bit rate, the packets
						will never exceed this size.
						This always refers to the encoded data, so for encoders it refers to the
						output data and for decoders the input data.
						Not writable.
	@constant		kAudioCodecPropertyPacketSizeLimitForVBR
                        A UInt32 indicating the maximum number of bits in an output packet of an encoder.
                        The output packet size will not exceed this number. The size should be smaller 
                        than kAudioCodecPropertyMaximumPacketByteSize. This property will configure the 
                        encoder to VBR mode with the highest VBR quality that can maintain the packet 
                        size limit. kAudioCodecPropertySoundQualityForVBR can be used to retrieve the 
                        quality setting that will be used given that packet size limit.
                        Writeable if supported.
	@constant		kAudioCodecPropertyCurrentInputFormat
						An AudioStreamBasicDescription describing the format the codec
						expects its input data in
						Almost always writable, but if the codec only supports one unique input format
						it does not have to be
	@constant		kAudioCodecPropertyCurrentOutputFormat
						An AudioStreamBasicDescription describing the format the codec
						provides its output data in
						Almost always writable, but if the codec only supports one unique output format
						it does not have to be
	@constant		kAudioCodecPropertyMagicCookie
						An untyped buffer of out of band configuration data the codec
						requires to process the stream of data correctly. The contents
						of this data is private to the codec. 
						Not all codecs have magic cookies. If a call to AudioCodecGetPropertyInfo
						returns a size greater than 0 then the codec may take one.
						Writable if present.
	@constant		kAudioCodecPropertyUsedInputBufferSize
						A UInt32 indicating the number of bytes in the codec's input
						buffer. The amount of available buffer space is	simply the
						answer from kAudioCodecPropertyInputBufferSize minus the answer
						from this property.
						Not writable.
	@constant		kAudioCodecPropertyIsInitialized
						A UInt32 where 0 means the codec is uninitialized and anything
						else means the codec is initialized. This should never be settable directly.
						Must be set by AudioCodecInitialize and AudioCodecUninitialize.
	@constant		kAudioCodecPropertyCurrentTargetBitRate
						A UInt32 containing the number of bits per second to aim for when encoding
						data. This property is usually only relevant to encoders, but if a decoder
						can know what bit rate it's set to it may report it.
						This property is irrelevant if the encoder is configured as kAudioCodecBitRateControlMode_Variable.
						Writable on encoders if supported.
	@constant		kAudioCodecPropertyCurrentInputSampleRate
						A Float64 containing the current input sample rate in Hz. No Default.
						May be writable. If only one sample rate is supported it does not have to be.
	@constant		kAudioCodecPropertyCurrentOutputSampleRate
						A Float64 containing the current output sample rate in Hz. No Default.
						May be writable. If only one sample rate is supported it does not have to be.
	@constant		kAudioCodecPropertyQualitySetting
						A UInt32 that sets the tradeoff between sound quality and CPU time consumption.
						The property value is between [0 - 0x7F].
						Some enum constants are defined below for convenience.
						Writable if supported.
	@constant		kAudioCodecPropertyApplicableBitRateRange
						An array of AudioValueRange indicating the target bit rates
						supported by the encoder in its current configuration.
						This property is only relevant to encoders.
						See also kAudioCodecPropertyAvailableBitRateRange.
						Not writable.
    @constant		kAudioCodecPropertyRecommendedBitRateRange
                        An array of AudioValueRange indicating the recommended bit rates
                        at given sample rate.
                        This property is only relevant to encoders.
                        Not writable.
	@constant		kAudioCodecPropertyApplicableInputSampleRates
						An array of AudioValueRange indicating the valid ranges for the
						input sample rate of the codec for the current bit rate. 
						This property is only relevant to encoders.
						See also kAudioCodecPropertyAvailableInputSampleRates.
						Not writable.
	@constant		kAudioCodecPropertyApplicableOutputSampleRates
						An array of AudioValueRange indicating the valid ranges for the
						output sample rate of the codec for the current bit rate. 
						This property is only relevant to encoders.
						See also kAudioCodecPropertyAvailableOutputSampleRates.
						Not writable.
	@constant		kAudioCodecPropertyPaddedZeros
						A UInt32 indicating the number of zeros (samples) that were appended
						to the last packet of input data to make a complete packet encoding.
						Encoders only. No default.
						Not writable.
	@constant		kAudioCodecPropertyPrimeMethod
						A UInt32 specifying priming method.
						See enum below.
						May be writable. Some encoders offer the option of padding out the last packet, and this 
						may be set here.
	@constant		kAudioCodecPropertyPrimeInfo
						A pointer to an AudioCodecPrimeInfo struct.
						Not writable on encoders. On decoders this may be writable, telling the decoder to trim the
						first and/or last packet.
	@constant		kAudioCodecPropertyCurrentInputChannelLayout
						An AudioChannelLayout that specifies the channel layout that the codec is using for input.
						May be writable. If only one channel layout is supported it does not have to be.
	@constant		kAudioCodecPropertyCurrentOutputChannelLayout
						An AudioChannelLayout that specifies the channel layout that the codec is using for output.
						If settable on a encoder, it means the encoder can re-map channels
						May be writable. If only one channel layout is supported or the codec does no channel remapping
						(ie, output channel layout always equals the input channel layout) it does not have to be.
	@constant		kAudioCodecPropertySettings
						A CFDictionaryRef that lists both the settable codec settings and their values.
						Encoders only.
						Obviously this will be linked to many of the other properties listed herein and as such
						it potentially will cause synchronization problems. Therefore, when setting this property
						on an encoder a GetProperty should be done first to retrieve the current dictionary, 
						and only one setting within the dictionary should change with each SetProperty call, 
						as it is not guaranteed that changing one property will not have side effects.
						Writable if supported.
	@constant		kAudioCodecPropertyBitRateControlMode
						A UInt32 indicating which bit rate control mode will be applied to encoders that 
						can produce variable packet sizes (sometimes referred to as VBR encoders).
						Although the packet size may be variable, a constant bit rate can be maintained 
						over a transmission channel when decoding in real-time with a fixed end-to-end audio delay. 
						E.g., MP3 and MPEG-AAC use a bit reservoir mechanism to meet that constraint.
						See enum below. 
						Only needs to be settable if the codec supports multiple bit rate control strategies.
	@constant		kAudioCodecPropertyFormatList
						An array of AudioFormatListItem structs list all formats that can be handled by the decoder
						For decoders, takes a Magic Cookie that gets passed in on the GetProperty call. No default.
						On input, the outPropertyData parameter passed to GetProperty should begin with a 
						AudioCodecMagicCookieInfo struct which will be overwritten by the AudioFormatListItems 
						returned from the property. For encoders, returns a list of formats which will be in the
						bitstream. No input data required.
						Important note: this encoder property is only applicable to audio formats which are made of
						two or more layers where the base layers(s) can be decoded by systems which aren't capable of
						handling the enhancement layers. For example, a High Efficiency AAC bitstream which contains 
						an AAC Low Complexity base layer can be decoded by any AAC decoder.
	@constant		kAudioCodecPropertySoundQualityForVBR
						A UInt32 that sets a target sound quality level.
						Unlike kAudioCodecPropertyQualitySetting which is relevant to all BitRate Control Modes,
						this property only needs to be set by an encoder configured at kAudioCodecBitRateControlMode_Variable.
						The property value is between [0 - 0x7F].
						See also kAudioCodecPropertyQualitySetting
						Writable if supported.
    @constant       kAudioCodecPropertyBitRateForVBR
                        A UInt32 that can be used to set the target bit rate when the encoder is configured
                        for VBR mode (kAudioCodecBitRateControlMode_Variable). Writable if supported.
    @constant		kAudioCodecPropertyDelayMode
                        A UInt32 specifying the delay mode. See enum below.                        
                        Writable if supported.
	@constant		kAudioCodecPropertyAdjustLocalQuality
						An SInt32 number in the range [-128, 127] to allow encoding quality adjustements on a packet by packet basis.
						This property can be set on an initialized encoder object without having to uninitialize and re-intialize it
						and allows to adjust the encoder quality level for every packet. This is useful for packets streamed over
						unreliable IP networks where the encoder needs to adapt immediately to network condition changes.
						Escape property ID's start with a '^' symbol as the first char code. This bypasses the initilization check.
    @constant		kAudioCodecPropertyProgramTargetLevel
						A Float32 specifying the program target level in dB FS for decoders.
						Supported target levels are in the range of -31.0 to -20.0dB.
						This property controls the decoding of broadcast loudness
						normalization metadata with goal of achieving consistent loudness across various
						programs. The property complies with the target level defined in the MPEG Audio
						standard ISO/IEC 14496-3. It will override kAudioCodecPropertyProgramTargetLevelConstant.
	@constant		kAudioCodecPropertyProgramTargetLevelConstant
						A UInt32 specifying the program target level constant in dB FS (Full Scale) for decoders.
						Supported target levels are defined as enum with the prefix kProgramTargetLevel
						(see below). This property controls the decoding of broadcast loudness
						normalization metadata with the goal of achieving consistent loudness across various
						programs. The property complies with the target level defined in the MPEG Audio
						standard ISO/IEC 14496-3. The default is kProgramTargetLevel_None.
    @constant		kAudioCodecPropertyDynamicRangeControlMode
						A UInt32 specifying the DRC mode. Supported modes are defined as enum with the
						prefix kDynamicRangeControlMode (see below). This property controls which
						dynamic range compression scheme is applied if the information is present in
						the bitstream. The default is kDynamicRangeControlMode_None.
*/
CF_ENUM(AudioCodecPropertyID)
{
	kAudioCodecPropertyInputBufferSize											= 'tbuf',
	kAudioCodecPropertyPacketFrameSize											= 'pakf',
	kAudioCodecPropertyHasVariablePacketByteSizes								= 'vpk?',
	kAudioCodecPropertyEmploysDependentPackets									= 'dpk?',
	kAudioCodecPropertyMaximumPacketByteSize									= 'pakb',
    kAudioCodecPropertyPacketSizeLimitForVBR                                    = 'pakl',
	kAudioCodecPropertyCurrentInputFormat										= 'ifmt',
	kAudioCodecPropertyCurrentOutputFormat										= 'ofmt',
	kAudioCodecPropertyMagicCookie												= 'kuki',
	kAudioCodecPropertyUsedInputBufferSize										= 'ubuf',
	kAudioCodecPropertyIsInitialized											= 'init',
	kAudioCodecPropertyCurrentTargetBitRate										= 'brat',
  	kAudioCodecPropertyCurrentInputSampleRate									= 'cisr',
  	kAudioCodecPropertyCurrentOutputSampleRate									= 'cosr',
	kAudioCodecPropertyQualitySetting											= 'srcq',
	kAudioCodecPropertyApplicableBitRateRange									= 'brta',
    kAudioCodecPropertyRecommendedBitRateRange                                  = 'brtr',
	kAudioCodecPropertyApplicableInputSampleRates								= 'isra',	
	kAudioCodecPropertyApplicableOutputSampleRates								= 'osra',
	kAudioCodecPropertyPaddedZeros												= 'pad0',
	kAudioCodecPropertyPrimeMethod												= 'prmm',
	kAudioCodecPropertyPrimeInfo												= 'prim',
	kAudioCodecPropertyCurrentInputChannelLayout								= 'icl ',
	kAudioCodecPropertyCurrentOutputChannelLayout								= 'ocl ',
	kAudioCodecPropertySettings													= 'acs ',
	kAudioCodecPropertyFormatList												= 'acfl',
	kAudioCodecPropertyBitRateControlMode										= 'acbf',
	kAudioCodecPropertySoundQualityForVBR										= 'vbrq',
    kAudioCodecPropertyBitRateForVBR                                            = 'vbrb',
	kAudioCodecPropertyDelayMode                                                = 'dmod',
    kAudioCodecPropertyAdjustLocalQuality										= '^qal',
    kAudioCodecPropertyProgramTargetLevel										= 'pptl',
    kAudioCodecPropertyDynamicRangeControlMode									= 'mdrc',
    kAudioCodecPropertyProgramTargetLevelConstant								= 'ptlc',
};


/*!
	@enum			AudioCodecQuality
 
	@discussion		Constants to be used with kAudioCodecPropertyQualitySetting
 
	@constant		kAudioCodecQuality_Max
	@constant		kAudioCodecQuality_High
	@constant		kAudioCodecQuality_Medium
	@constant		kAudioCodecQuality_Low
	@constant		kAudioCodecQuality_Min
*/
CF_ENUM(UInt32)
{
	kAudioCodecQuality_Max		= 0x7F,
	kAudioCodecQuality_High		= 0x60,
	kAudioCodecQuality_Medium	= 0x40,
	kAudioCodecQuality_Low		= 0x20,
	kAudioCodecQuality_Min		= 0
};


/*!
	@enum			AudioCodecPrimeMethod
 
	@discussion		Constants to be used with kAudioCodecPropertyPrimeMethod.
 
	@constant		kAudioCodecPrimeMethod_Pre
						Primes with leading and trailing input frames
	@constant		kAudioCodecPrimeMethod_Normal
						Only primes with trailing (zero latency)
						leading frames are assumed to be silence
	@constant		kAudioCodecPrimeMethod_None
						Acts in "latency" mode
						both leading and trailing frames assumed to be silence
*/
CF_ENUM(UInt32)
{
	kAudioCodecPrimeMethod_Pre 		= 0,
	kAudioCodecPrimeMethod_Normal 	= 1,
	kAudioCodecPrimeMethod_None 	= 2
};


/*!
	@enum			kAudioCodecPropertyBitRateControlMode
 
	@discussion		Constants defining various bit rate control modes
					to be used with kAudioCodecPropertyBitRateControlMode.
					These modes are only applicable to encoders that can produce
					variable packet sizes, such as AAC.

	@constant		kAudioCodecBitRateControlMode_Constant
						The encoder maintains a constant bit rate suitable for use over a transmission 
						channel when decoding in real-time with a fixed end-to-end audio delay.  
						Note that while a constant bit rate is maintained in this mode, the number of bits 
						allocated to encode each fixed length of audio data may be variable 
						(ie. packet sizes are variable).
						E.g., MP3 and MPEG-AAC use a bit reservoir mechanism to meet that constraint.
	@constant		kAudioCodecBitRateControlMode_LongTermAverage
						 The provided target bit rate is achieved over a long term average
						 (typically after the first 1000 packets). This mode is similar to 
						 kAudioCodecBitRateControlMode_Constant in the sense that the 
						 target bit rate will be maintained in a long term average. However, it does not 
						 provide constant delay when using constant bit rate transmission. This mode offers 
						 a better sound quality than kAudioCodecBitRateControlMode_Constant 
						 can, that is, a more efficient encoding is performed. 
	@constant		kAudioCodecBitRateControlMode_VariableConstrained
						Encoder dynamically allocates the bit resources according to the characteristics
						of the underlying signal. However, some constraints are applied in order to limit 
						the variation of the bit rate.
	@constant		kAudioCodecBitRateControlMode_Variable
						Similar to the VBR constrained mode, however the packet size is virtually unconstrained.
						The coding process targets constant sound quality, and the sound quality level is 
						set by kAudioCodecPropertySoundQualityForVBR.
						This mode usually provides the best tradeoff between quality and bit rate.
*/
CF_ENUM(UInt32)
{
	kAudioCodecBitRateControlMode_Constant					= 0,
	kAudioCodecBitRateControlMode_LongTermAverage			= 1,
	kAudioCodecBitRateControlMode_VariableConstrained		= 2,
	kAudioCodecBitRateControlMode_Variable					= 3,
};

/*!
    @enum			AudioCodecDelayMode
 
    @discussion		Constants defining various delay modes to be used with kAudioCodecPropertyDelayMode.
                    The resulting priming frames are reflected in the kAudioCodecPropertyPrimeInfo property.
                    Note that for layered streams like aach and aacp, the priming information always refers
                    to the base layer.
    @constant		kAudioCodecDelayMode_Compatibility
                        In compatibility delay mode, the resulting priming corresponds to the default value defined by the
                        underlying codecs. For aac this number equals 2112 regardless of the sample rate and other settings.
    @constant		kAudioCodecDelayMode_Minimum
                        Sets the encoder, where applicable, in it's lowest possible delay mode. Any additional delays, like the one
                        introduced by filters/sample rate converters etc, aren't compensated by the encoder.
    @constant		kAudioCodecDelayMode_Optimal
                        In this mode, the resulting bitstream has the minimum amount of priming necessary for the decoder.
                        For aac this number is 1024 which corresponds to exactly one packet.
*/
CF_ENUM(UInt32)
{
    kAudioCodecDelayMode_Compatibility  = 0,
    kAudioCodecDelayMode_Minimum        = 1,
    kAudioCodecDelayMode_Optimal        = 2
};

/*!
	@enum			ProgramTargetLevel

	@discussion		Constants to be used with kAudioCodecPropertyProgramTargetLevelConstant

	@constant		kProgramTargetLevel_None
						
	@constant		kProgramTargetLevel_Minus31dB
	@constant		kProgramTargetLevel_Minus23dB
	@constant		kProgramTargetLevel_Minus20dB
*/
CF_ENUM(UInt32)
{
	kProgramTargetLevel_None		= 0,
	kProgramTargetLevel_Minus31dB	= 1,
	kProgramTargetLevel_Minus23dB	= 2,
	kProgramTargetLevel_Minus20dB	= 3
};
    
/*!
	@enum			DynamicRangeControlMode

	@discussion		Constants to be used with kAudioCodecPropertyDynamicRangeControlMode

	@constant		kDynamicRangeControlMode_None
						Dynamic range compression disabled
	@constant		kDynamicRangeControlMode_Light
						Light compression according to MPEG-Audio ISO/IEC 14496
	@constant		kDynamicRangeControlMode_Heavy
						Heavy compression according to ETSI TS 101 154
*/
CF_ENUM(UInt32)
{
	kDynamicRangeControlMode_None	= 0,
	kDynamicRangeControlMode_Light	= 1,
	kDynamicRangeControlMode_Heavy	= 2
};

/*!
	@struct			AudioCodecPrimeInfo 
 
	@discussion		Specifies the number of leading and trailing empty frames
					which have to be inserted.
 
	@var  			leadingFrames
						An unsigned integer specifying the number of leading empty frames
	@var  			trailingFrames
						An unsigned integer specifying the number of trailing empty frames 
*/
typedef struct AudioCodecPrimeInfo 
{
	UInt32		leadingFrames;
	UInt32		trailingFrames;
} AudioCodecPrimeInfo;


//=============================================================================
#pragma mark -
#pragma mark Constants for kAudioCodecPropertySettings
//=============================================================================

#define kAudioSettings_TopLevelKey		"name"
#define kAudioSettings_Version			"version"
#define kAudioSettings_Parameters 		"parameters"
#define kAudioSettings_SettingKey		"key"
#define kAudioSettings_SettingName 		"name"
#define kAudioSettings_ValueType 		"value type"
#define kAudioSettings_AvailableValues	"available values"
#define kAudioSettings_LimitedValues	"limited values"
#define kAudioSettings_CurrentValue 	"current value"
#define kAudioSettings_Summary 			"summary"
#define kAudioSettings_Hint 			"hint"
#define kAudioSettings_Unit 			"unit"


/*!
	@enum			AudioSettingsFlags
 
	@discussion		Constants to be used with kAudioSettings_Hint
					in the kAudioCodecPropertySettings property dictionary.
					Indicates any special characteristics of each parameter within the dictionary, 

	@constant		kAudioSettingsFlags_ExpertParameter
						If set, then the parameter is an expert parameter.
	@constant		kAudioSettingsFlags_InvisibleParameter
						If set, then the parameter should not be displayed. 
	@constant		kAudioSettingsFlags_MetaParameter
						If set, then changing this parameter may affect the values of other parameters. 
						If not set, then this parameter can be set without affecting the values of other parameters.
	@constant		kAudioSettingsFlags_UserInterfaceParameter
						If set, then this is only a user interface element and not reflected in the codec's bit stream.
*/
typedef CF_OPTIONS(UInt32, AudioSettingsFlags) {
	kAudioSettingsFlags_ExpertParameter			= (1L << 0),
	kAudioSettingsFlags_InvisibleParameter		= (1L << 1),
	kAudioSettingsFlags_MetaParameter			= (1L << 2),
	kAudioSettingsFlags_UserInterfaceParameter	= (1L << 3)
};


//=============================================================================
#pragma mark -
#pragma mark Status values returned from the AudioCodecProduceOutputPackets routine
//=============================================================================
/*!
	@enum			AudioCodecProduceOutputPacketStatus
 
	@discussion		Possible return status
 
	@constant		kAudioCodecProduceOutputPacketFailure
						Couldn't complete the request due to an error. It is possible
						that some output data was produced. This is reflected in the value
						returned in ioNumberPackets. 
	@constant		kAudioCodecProduceOutputPacketSuccess
						The number of requested output packets was produced without incident
						and there isn't any more input data to process
	@constant		kAudioCodecProduceOutputPacketSuccessHasMore
						The number of requested output packets was produced and there is
						enough input data to produce at least one more packet of output data
	@constant		kAudioCodecProduceOutputPacketNeedsMoreInputData
						There was insufficient input data to produce the requested
						number of output packets, The value returned in ioNumberPackets
						holds the number of output packets produced.
	@constant		kAudioCodecProduceOutputPacketAtEOF
						The end-of-file marker was hit during the processing. Fewer
						than the requested number of output packets may have been
						produced. Check the value returned in ioNumberPackets for the
						actual number produced. Note that not all formats have EOF
						markers in them. 
*/
CF_ENUM(UInt32)
{
	kAudioCodecProduceOutputPacketFailure					= 1,		
	kAudioCodecProduceOutputPacketSuccess					= 2,	
	kAudioCodecProduceOutputPacketSuccessHasMore			= 3,		
	kAudioCodecProduceOutputPacketNeedsMoreInputData		= 4,		
	kAudioCodecProduceOutputPacketAtEOF						= 5		
};


//=============================================================================
#pragma mark -
#pragma mark Selectors for the component routines
//=============================================================================
/*!
	@enum			AudioCodecSelectors
 
	@discussion		Allows selection of component routines supported the the AudioCodec API
					Used by the Component Manager.
 
	@constant		kAudioCodecGetPropertyInfoSelect
	@constant		kAudioCodecGetPropertySelect
	@constant		kAudioCodecSetPropertySelect
	@constant		kAudioCodecInitializeSelect
	@constant		kAudioCodecUninitializeSelect
	@constant		kAudioCodecAppendInputDataSelect
	@constant		kAudioCodecProduceOutputDataSelect
	@constant		kAudioCodecResetSelect
	@constant		kAudioCodecAppendInputBufferListSelect
	@constant		kAudioCodecProduceOutputBufferListSelect
*/
CF_ENUM(UInt32)
{
	kAudioCodecGetPropertyInfoSelect						= 0x0001,
	kAudioCodecGetPropertySelect							= 0x0002,
	kAudioCodecSetPropertySelect							= 0x0003,
	kAudioCodecInitializeSelect								= 0x0004,
	kAudioCodecUninitializeSelect							= 0x0005,
	kAudioCodecAppendInputDataSelect						= 0x0006,
	kAudioCodecProduceOutputDataSelect						= 0x0007,
	kAudioCodecResetSelect									= 0x0008,
	kAudioCodecAppendInputBufferListSelect					= 0x0009,
	kAudioCodecProduceOutputBufferListSelect				= 0x000A
};


//=============================================================================
#pragma mark -
#pragma mark Errors
//=============================================================================
/*!
	@enum			AudioCodecErrors
 
	@discussion		Possible errors returned by audio codec components
 
	@constant		kAudioCodecNoError
	@constant		kAudioCodecUnspecifiedError
	@constant		kAudioCodecUnknownPropertyError
	@constant		kAudioCodecBadPropertySizeError
	@constant		kAudioCodecIllegalOperationError
	@constant		kAudioCodecUnsupportedFormatError
	@constant		kAudioCodecStateError
	@constant		kAudioCodecNotEnoughBufferSpaceError
	@constant		kAudioCodecBadDataError
*/
CF_ENUM(OSStatus)
{
	kAudioCodecNoError								= 0,
	kAudioCodecUnspecifiedError						= 'what',
	kAudioCodecUnknownPropertyError					= 'who?',
	kAudioCodecBadPropertySizeError					= '!siz',
	kAudioCodecIllegalOperationError				= 'nope',
	kAudioCodecUnsupportedFormatError				= '!dat',
	kAudioCodecStateError							= '!stt',
	kAudioCodecNotEnoughBufferSpaceError			= '!buf',
	kAudioCodecBadDataError							= 'bada'
};


//=============================================================================
#pragma mark -
#pragma mark Codec Property Management
//=============================================================================

/*!
	@function		AudioCodecGetPropertyInfo
 
	@discussion		Retrieve information about the given property. The outSize argument
					will return the size in bytes of the current value of the property.
					The outWritable argument will return whether or not the property
					in question can be changed.
 
	@param			inCodec
						An AudioCodec instance
	@param			inPropertyID
						Property ID whose value should be read
	@param			outSize
						Size in bytes of the property
	@param			outWritable
						Flag indicating wether the underlying property can be modified or not 
 
	@result			The OSStatus value
*/
extern OSStatus
AudioCodecGetPropertyInfo(	AudioCodec				inCodec,
							AudioCodecPropertyID	inPropertyID,
							UInt32* __nullable		outSize,
							Boolean* __nullable		outWritable)		API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));


/*!
	@function		AudioCodecGetProperty
 
	@discussion		Retrieve the indicated property data. On input, ioDataSize has the size
					of the data pointed to by outPropertyData. On output, ioDataSize will contain
					the amount written.
 
	@param			inCodec
						An AudioCodec instance
	@param			inPropertyID
						Property ID whose value should be read
	@param			ioPropertyDataSize
						Size in bytes of the property data
	@param			outPropertyData
						Pointer to the property data buffer

	@result			The OSStatus value
*/
extern OSStatus
AudioCodecGetProperty(	AudioCodec				inCodec,
						AudioCodecPropertyID	inPropertyID,
						UInt32*					ioPropertyDataSize,
						void*					outPropertyData)		API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));


/*!
	@function		AudioCodecSetProperty

	@discussion		Set the indicated property data.
 
	@param			inCodec
						An AudioCodec instance
	@param			inPropertyID
						Property ID whose value should be changed
	@param			inPropertyDataSize
						Size in bytes of the property data
	@param			inPropertyData
						Pointer to the property data buffer
 
	@result			The OSStatus value
*/
extern OSStatus
AudioCodecSetProperty(	AudioCodec				inCodec,
						AudioCodecPropertyID	inPropertyID,
						UInt32					inPropertyDataSize,
						const void*				inPropertyData)			API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));


//=============================================================================
#pragma mark -
#pragma mark Codec Data Handling Routines
//=============================================================================

/*!
	@function		AudioCodecInitialize
 
	@discussion		This call will allocate any buffers needed and otherwise set the codec
					up to perform the indicated translation. If an argument is NULL, any
					previously set properties will be used for preparing the codec for work.
					Note that this routine will also validate the format information as useable.
 
	@param			inCodec
						An AudioCodec instance
	@param			inInputFormat
						Pointer to an input format structure
	@param			inOutputFormat
						Pointer to an output format structure
	@param			inMagicCookie
						Pointer to the magic cookie
	@param			inMagicCookieByteSize
						Size in bytes of the magic cookie
  
	@result			The OSStatus value
*/
extern OSStatus
AudioCodecInitialize(	AudioCodec										inCodec,
						const AudioStreamBasicDescription* __nullable	inInputFormat,
						const AudioStreamBasicDescription* __nullable	inOutputFormat,
						const void*	__nullable							inMagicCookie,
						UInt32											inMagicCookieByteSize)
																		API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));


/*!
	@function		AudioCodecUninitialize
  
	@discussion		This call will move the codec from the initialized state back to the
					uninitialized state. The codec will release any resources it allocated
					or claimed in AudioCodecInitialize.
 
	@param			inCodec
						An AudioCodec instance
 
	@result			The OSStatus value
*/
extern OSStatus
AudioCodecUninitialize(AudioCodec inCodec)								API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));


/*!
	@function		AudioCodecAppendInputData
 
	@discussion		Append as much of the given data in inInputData to the codec's input buffer as possible
					and return in ioInputDataByteSize the amount of data used.
 
					The inPacketDescription argument is an array of AudioStreamPacketDescription
					structs that describes the packet layout. The number of elements in this array
					is indicated on input by ioNumberPackets. On return, this number indicates the number
					of packets consumed.
 
					Note also in this case that it is an error to supply less than a full packet
					of data at a time.
 
	@param			inCodec
						An AudioCodec instance
	@param			inInputData
						A const pointer to the input data
	@param			ioInputDataByteSize
						The size in bytes of the input data in inInputData on input,
						the number of bytes consumed on output
	@param			ioNumberPackets
						The number of packets
	@param			inPacketDescription
						The packet description pointer
 
	@result			The OSStatus value
*/
extern OSStatus
AudioCodecAppendInputData(	AudioCodec										inCodec,
							const void*										inInputData,
							UInt32*											ioInputDataByteSize,
							UInt32*											ioNumberPackets,
							const AudioStreamPacketDescription*	__nullable	inPacketDescription)
																		API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));


/*!
	@function		AudioCodecProduceOutputPackets

	@discussion		Produce as many output packets as requested and the amount of input data
					allows for. The outStatus argument returns information about the codec's
					status to allow for proper data management. See the constants above for
					the possible values that can be returned.
 
					The outPacketDescription argument is an array of AudioStreamPacketDescription
					structs that describes the packet layout returned in outOutputData. This
					argument is optional. Pass NULL if this information is not to be returned.
					Note that this information is only provided when the output format isn't
					linear PCM.

					Note that decoders will always only produce linear PCM data in multiples of
					the number frames in a packet of the encoded format (as returned by
					kAudioCodecPropertyPacketFrameSize). Encoders will consume this many frames
					of linear PCM data to produce a packet of their format.
 
	@param			inCodec
						The AudioCodec instance
	@param			outOutputData
						Pointer to the output data buffer
	@param			ioOutputDataByteSize
						A pointer to the size
	@param			ioNumberPackets
						number of input/output packets
	@result			The OSStatus value
*/
extern OSStatus
AudioCodecProduceOutputPackets(	AudioCodec									inCodec,
								void*										outOutputData,
								UInt32*										ioOutputDataByteSize,
								UInt32*										ioNumberPackets,
								AudioStreamPacketDescription* __nullable	outPacketDescription,
								UInt32*										outStatus)
																		API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

extern OSStatus
AudioCodecAppendInputBufferList(	AudioCodec							inCodec,
									const AudioBufferList *				inBufferList,
									UInt32*								ioNumberPackets,
									const AudioStreamPacketDescription*	__nullable	inPacketDescription,
									UInt32*								outBytesConsumed)
																		API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));

extern OSStatus
AudioCodecProduceOutputBufferList(	AudioCodec									inCodec,
									AudioBufferList *							ioBufferList,
									UInt32*										ioNumberPackets,
									AudioStreamPacketDescription* __nullable	outPacketDescription,
									UInt32*										outStatus)
																		API_AVAILABLE(macos(10.7), ios(4.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioCodecReset

	@discussion		Flushes all the data in the codec and clears the input buffer. Note that
					the formats, and magic cookie will be retained so they won't need to be
					set up again to decode the same data.
 
	@param			inCodec The audio codec descriptor
 
	@result			the OSStatus value
*/
extern OSStatus
AudioCodecReset(AudioCodec inCodec)										API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

//=====================================================================================================================
typedef OSStatus
(*AudioCodecGetPropertyInfoProc)(void *self, AudioCodecPropertyID inPropertyID, UInt32 * __nullable outSize, Boolean * __nullable outWritable);

typedef OSStatus
(*AudioCodecGetPropertyProc)(void *self, AudioCodecPropertyID inPropertyID, UInt32 *ioPropertyDataSize, 
								void *outPropertyData);

typedef OSStatus
(*AudioCodecSetPropertyProc)(void *self, AudioCodecPropertyID inPropertyID, UInt32 inPropertyDataSize, 
								const void *inPropertyData);

typedef OSStatus
(*AudioCodecInitializeProc)(void *self, const AudioStreamBasicDescription * __nullable inInputFormat,
								const AudioStreamBasicDescription * __nullable inOutputFormat, const void * __nullable inMagicCookie,
								UInt32 inMagicCookieByteSize);

typedef OSStatus
(*AudioCodecUninitializeProc)(void *self);

typedef OSStatus
(*AudioCodecAppendInputDataProc)(void *self, const void *inInputData, UInt32 *ioInputDataByteSize, UInt32 *ioNumberPackets, 
								const AudioStreamPacketDescription * __nullable inPacketDescription);

typedef OSStatus
(*AudioCodecProduceOutputPacketsProc)(void *self, void *outOutputData, UInt32 *ioOutputDataByteSize, UInt32 *ioNumberPackets, 
								AudioStreamPacketDescription * __nullable outPacketDescription, UInt32 *outStatus);

typedef OSStatus
(*AudioCodecResetProc)(void *self);

typedef OSStatus
(*AudioCodecAppendInputBufferListProc)(void *self, const AudioBufferList *ioBufferList, UInt32 *inNumberPackets, 
								const AudioStreamPacketDescription * __nullable inPacketDescription, UInt32 *outBytesConsumed);

typedef OSStatus
(*AudioCodecProduceOutputBufferListProc)(void *self, AudioBufferList *ioBufferList, UInt32 *ioNumberPackets, 
								AudioStreamPacketDescription *__nullable outPacketDescription, UInt32 *outStatus);


//=====================================================================================================================
#pragma mark -
#pragma mark Deprecated Properties

/*!
    @enum		AudioCodecProperty
    @deprecated

    @constant	kAudioCodecPropertyMinimumDelayMode
                    A UInt32 equal 1 sets the encoder, where applicable, in it's lowest possible delay mode. An encoder
                    may prepend zero valued samples to the input signal in order to make additional delays, like e.g.
                    from a filter, coincide on a block boundary. This operation, however, results in an increased
                    encoding/ decoding delay which may be undesired and turned off with this property.
                    Use the kAudioCodecPropertyDelayMode property instead with the value set to kAudioCodecDelayMode_Minimum
*/
CF_ENUM(AudioCodecPropertyID)
{
	kAudioCodecPropertyMinimumDelayMode                 = 'mdel'
};

/*!
	@enum		AudioCodecProperty
	@deprecated	in version 10.7

	@constant	kAudioCodecPropertyNameCFString
					The name of the codec component as a CFStringRef. The CFStringRef
					retrieved via this property must be released by the caller.
	@constant	kAudioCodecPropertyManufacturerCFString
					The manufacturer of the codec as a CFStringRef. The CFStringRef 
					retrieved via this property must be released by the caller.
	@constant	kAudioCodecPropertyFormatCFString
					The name of the codec's format as a CFStringRef. The CFStringRef
					retrieved via this property must be released by the caller.

*/
CF_ENUM(AudioCodecPropertyID)
{
	kAudioCodecPropertyNameCFString			= 'lnam',
	kAudioCodecPropertyManufacturerCFString = 'lmak',
	kAudioCodecPropertyFormatCFString		= 'lfor'
};

/*!
	@enum		AudioCodecProperty
	@deprecated	in version 10.5
 
	@constant	kAudioCodecPropertyRequiresPacketDescription
					A UInt32 where a non-zero value indicates that the format the codec implements
					requires that an AudioStreamPacketDescription array must be supplied with any data
					in that format. Note that this implies that data must also be handled strictly in
					packets. For a decoder, this applies to input data. For an encoder, it applies to
					output data, which means that the encoder will be filling out provided packet descriptions
					on output.
					A decoder must be able to handle packet descriptions even if it does not require them.
					An encoder does not have to fill out packet descriptions if it does not require them.
					Redundant due to kAudioCodecPropertyHasVariablePacketByteSizes. Codecs with variable-sized 
					packets must handle packet descriptions while codecs with constant-sized packets do not 
					have to.
	@constant	kAudioCodecPropertyAvailableBitRates
					An array of UInt32 that indicates the target bit rates
					supported by the encoder. This property is only relevant to
					encoders. Replaced with kAudioCodecPropertyAvailableBitRateRange
	@constant	kAudioCodecExtendFrequencies
					A UInt32 indicating whether an encoder should extend its cutoff frequency
					if such an option exists. 0 == extended frequencies off, 1 == extended frequencies on
					e.g. some encoders normally cut off the signal at 16 kHz but can encode up to 20 kHz if 
					asked to.
					Redundant.
	@constant	kAudioCodecUseRecommendedSampleRate
					For encoders that do sample rate conversion, a UInt32 indicating whether or
					not the encoder is using the recommended sample rate for the given input. 
					A value of 0 indicates it isn't, 1 indicates it is.
					This property is read only and indicates whether or not a user has explicitly set an output 
					sample rate.
					Redundant as 0.0 for a sample rate means let the codec decide.
	@constant	kAudioCodecOutputPrecedence
					For encoders that do sample rate conversion, a UInt32 indicating whether the
					bit rate, sample rate, or neither have precedence over the other. See enum below.
					Redundant because precedence is implicitly set by either providing a non-zero bit rate or 
					sample rate and setting the other to zero (which allows the encoder to choose any applicable rate). 
					If both values are set to non-zero, neither value has precedence.
	@constant	kAudioCodecDoesSampleRateConversion
					Renamed to kAudioCodecPropertyDoesSampleRateConversion
	@constant	kAudioCodecBitRateFormat
					Renamed to kAudioCodecPropertyBitRateControlMode
	@constant	kAudioCodecInputFormatsForOutputFormat
					Renamed to kAudioCodecPropertyInputFormatsForOutputFormat
	@constant	kAudioCodecOutputFormatsForInputFormat
					Renamed to kAudioCodecPropertyOutputFormatsForInputFormat
	@constant	kAudioCodecPropertyInputChannelLayout
					Renamed to kAudioCodecPropertyCurrentInputChannelLayout
	@constant	kAudioCodecPropertyOutputChannelLayout
					Renamed to kAudioCodecPropertyCurrentOutputChannelLayout
	@constant	kAudioCodecPropertyZeroFramesPadded
					Renamed to kAudioCodecPropertyPaddedZeros
 */
CF_ENUM(AudioCodecPropertyID)
{
	kAudioCodecPropertyRequiresPacketDescription			= 'pakd',
	kAudioCodecPropertyAvailableBitRates					= 'brt#',
	kAudioCodecExtendFrequencies							= 'acef',
	kAudioCodecUseRecommendedSampleRate						= 'ursr',
	kAudioCodecOutputPrecedence								= 'oppr',
	kAudioCodecBitRateFormat								= kAudioCodecPropertyBitRateControlMode,
	kAudioCodecDoesSampleRateConversion						= kAudioCodecPropertyDoesSampleRateConversion,
	kAudioCodecInputFormatsForOutputFormat					= kAudioCodecPropertyInputFormatsForOutputFormat,
	kAudioCodecOutputFormatsForInputFormat					= kAudioCodecPropertyOutputFormatsForInputFormat,
	kAudioCodecPropertyInputChannelLayout					= kAudioCodecPropertyCurrentInputChannelLayout,
	kAudioCodecPropertyOutputChannelLayout					= kAudioCodecPropertyCurrentOutputChannelLayout,
	kAudioCodecPropertyAvailableInputChannelLayouts			= kAudioCodecPropertyAvailableInputChannelLayoutTags,
	kAudioCodecPropertyAvailableOutputChannelLayouts		= kAudioCodecPropertyAvailableOutputChannelLayoutTags,	
	kAudioCodecPropertyZeroFramesPadded						= kAudioCodecPropertyPaddedZeros
};

/*!
	@enum		AudioCodecBitRateFormat

	@deprecated	in version 10.5

	@discussion	Constants to be used with kAudioCodecBitRateFormat.
					This is deprecated. 
					Use kAudioCodecPropertyBitRateControlMode instead.
 
	@constant	kAudioCodecBitRateFormat_CBR is mapped to kAudioCodecBitRateControlMode_Constant
	@constant	kAudioCodecBitRateFormat_ABR is mapped to kAudioCodecBitRateControlMode_LongTermAverage
	@constant	kAudioCodecBitRateFormat_VBR is mapped to kAudioCodecBitRateControlMode_VariableConstrained
 */
CF_ENUM(UInt32)
{	
	kAudioCodecBitRateFormat_CBR 	=	kAudioCodecBitRateControlMode_Constant,
	kAudioCodecBitRateFormat_ABR 	=	kAudioCodecBitRateControlMode_LongTermAverage,
	kAudioCodecBitRateFormat_VBR 	=	kAudioCodecBitRateControlMode_VariableConstrained
};

/*!
	@enum		AudioCodecOutputPrecedence

	@deprecated	in version 10.5

	@discussion	Constants to be used with kAudioCodecOutputPrecedence
 
	@constant	kAudioCodecOutputPrecedenceNone
					Change in the bit rate or the sample rate are constrained by
					the other value.
	@constant	kAudioCodecOutputPrecedenceBitRate
					The bit rate may be changed freely,
					adjusting the sample rate if necessary
	@constant	kAudioCodecOutputPrecedenceSampleRate
					The sample rate may be changed freely,
					adjusting the bit rate if necessary
 */
CF_ENUM(UInt32)
{
	kAudioCodecOutputPrecedenceNone			= 0,
	kAudioCodecOutputPrecedenceBitRate		= 1,
	kAudioCodecOutputPrecedenceSampleRate 	= 2
};

/*!
	@typedef	MagicCookieInfo
 
	@deprecated	in version 10.5
 
	@discussion	renamed to AudioCodecMagicCookieInfo 
 */
typedef struct AudioCodecMagicCookieInfo MagicCookieInfo __attribute__((deprecated));

/*!
	@enum		AudioCodecSettingsHint
 
	@deprecated	in version 10.4
 
	@discussion	Constants to be used with kAudioSettings_Hint.
				This is deprecated.
				Use	AudioSettingsFlag instead.
 
	@constant	kHintBasic
	@constant	kHintAdvanced
	@constant	kHintHidden
 */
CF_ENUM(UInt32)
{
	kHintBasic		= 0,
	kHintAdvanced	= 1,
	kHintHidden		= 2
};

#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif	//	AudioUnit_AudioCodec_h
#else
#include <AudioToolboxCore/AudioCodec.h>
#endif
// ==========  AudioToolbox.framework/Headers/MusicPlayer.h
/*!
	@file		MusicPlayer.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2000-2015 by Apple, Inc., all rights reserved.

	@abstract	API's for Music sequencing and playing services
	
	@discussion
		The objects in this API set include:

			- Music Sequence: a container of music tracks
			- Music Track: a time ordered list of events
			- Music Track Iterator: an object to iterate over events in a track
			- Music Player: an object used to play a sequence
		
		A MusicSequence contains an arbitrary number of tracks (MusicTrack) each of which contains
		time-stamped (in units of beats) events in time-increasing order. There are various types of
		events, defined below, including the expected MIDI events, tempo, and extended events.
		
		A MusicTrack has properties which may be inspected and assigned, including support for
		looping, muting/soloing, and time-stamp interpretation. APIs exist for iterating through the
		events in a MusicTrack, and for performing editing operations on them.
		
		A MusicPlayer is used to play a sequence and provides control of playback rate and setting
		to a particular time.
		
		Each MusicSequence may have an associated AUGraph object, which represents a set of
		AudioUnits and the connections between them.  Then, each MusicTrack of the MusicSequence may
		address its events to a specific AudioUnit within the AUGraph. In such a manner, it's
		possible to automate arbitrary parameters of AudioUnits, and schedule notes to be played to
		MusicDevices (AudioUnit software synthesizers) within an arbitrary audio processing network
		(AUGraph). A MusicSequence or its tracks can also address a CoreMIDI endpoint directly.
*/

#ifndef AudioToolbox_MusicPlayer_h
#define AudioToolbox_MusicPlayer_h

#include <Availability.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AudioToolbox/MusicDevice.h>
#include <AudioToolbox/AUGraph.h>

#if __has_include(<CoreMIDI/MIDIServices.h>)
	#include <CoreMIDI/MIDIServices.h>
#else
	typedef UInt32 MIDIEndpointRef;
#endif


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

/*!
	@enum MusicEventType
	@abstract music event types, including both MIDI and "extended" protocol
	@constant kMusicEventType_NULL	
	@constant kMusicEventType_ExtendedNote	note with variable number of arguments (non-MIDI)
	@constant kMusicEventType_ExtendedTempo	tempo change in BPM
	@constant kMusicEventType_User			user defined data
	@constant kMusicEventType_Meta			standard MIDI file meta event
	@constant kMusicEventType_MIDINoteMessage		MIDI note-on with duration (for note-off)
	@constant kMusicEventType_MIDIChannelMessage	MIDI channel messages (other than note-on/off)
	@constant kMusicEventType_MIDIRawData			for MIDI system exclusive data
	@constant kMusicEventType_Parameter		general purpose AudioUnit parameter, added in 10.2
	@constant kMusicEventType_AUPreset		the AU's user preset CFDictionaryRef (the ClassInfo property), added 10.3
*/
CF_ENUM(UInt32)
{
	kMusicEventType_NULL					= 0,
	kMusicEventType_ExtendedNote			= 1,
	kMusicEventType_ExtendedTempo			= 3,
	kMusicEventType_User					= 4,
	kMusicEventType_Meta					= 5,
	kMusicEventType_MIDINoteMessage			= 6,
	kMusicEventType_MIDIChannelMessage		= 7,
	kMusicEventType_MIDIRawData				= 8,
	kMusicEventType_Parameter				= 9,
	kMusicEventType_AUPreset				= 10
};
typedef UInt32		MusicEventType;

/*!
	@enum MusicSequenceLoadFlags
	@abstract Flags used to customise loading behaviour
 	@constant	kMusicSequenceLoadSMF_PreserveTracks
			If this flag is set the resultant Sequence will contain:
			a tempo track
			a track for each track found in the SMF
 			This is the default behavior
	@constant	kMusicSequenceLoadSMF_ChannelsToTracks
			If this flag is set the resultant Sequence will contain:
			a tempo track
			1 track for each MIDI Channel that is found in the SMF
			1 track for SysEx or MetaEvents - this will be the last track 
			in the sequence after the LoadSMFWithFlags calls
*/
typedef CF_OPTIONS(UInt32, MusicSequenceLoadFlags)
{
	kMusicSequenceLoadSMF_PreserveTracks	= 0,
	kMusicSequenceLoadSMF_ChannelsToTracks 	= (1 << 0)
};

/*!
	@enum MusicSequenceType
	@abstract	A sequence type
	@discussion Different sequence types to describe the basic mode of operation of a sequence's time line
				You cannot change a music sequence's type to samples/seconds if there are tempo events
				The type will also define how the sequence is saved to a MIDI file:
					Beats - normal midi file
					Seconds - midi file with SMPTE time
					Samples - cannot be saved to a midi file
	@constant	kMusicSequenceType_Beats
					The default/normal type of a sequence.
					Tempo track defines the number of beats per second and can have multiple tempo events
	@constant	kMusicSequenceType_Seconds
					A music sequence with a single 60bpm tempo event
	@constant	kMusicSequenceType_Samples
					A music sequence with a single tempo event that represents the audio sample rate
*/
typedef CF_ENUM(UInt32, MusicSequenceType) {
	kMusicSequenceType_Beats		= 'beat',
	kMusicSequenceType_Seconds		= 'secs',
	kMusicSequenceType_Samples		= 'samp'
};

/*!
	@enum MusicSequenceFileTypeID
	@abstract	describes different types of files that can be parsed by a music sequence
 	@constant	kMusicSequenceFile_AnyType
 					let the system read iMelody files and read and write MIDI files (and any future types)
	@constant	kMusicSequenceFile_MIDIType
					read and write MIDI files
	@constant	kMusicSequenceFile_iMelodyType
					read iMelody files
*/
typedef CF_ENUM(UInt32, MusicSequenceFileTypeID) {
	kMusicSequenceFile_AnyType			= 0,
	kMusicSequenceFile_MIDIType			= 'midi',
	kMusicSequenceFile_iMelodyType		= 'imel'
};

/*!
	@enum MusicSequenceFileFlags
	@abstract	controls the behaviour of the create file calls
	@constant	kMusicSequenceFileFlags_Default
 					Does not overwrite existing files.  Attempts to save over an existing file
 					will return kAudio_FilePermissionError
	@constant	kMusicSequenceFileFlags_EraseFile
					Erase an existing file when creating a new file
*/
typedef CF_OPTIONS(UInt32, MusicSequenceFileFlags) {
	kMusicSequenceFileFlags_Default	  = 0,
	kMusicSequenceFileFlags_EraseFile = 1
};


/*!
	@typedef	MusicTimeStamp
	@abstract	The type used to refer to time values in a music sequence
*/
typedef Float64		MusicTimeStamp;

/*!
	@struct		kMusicTimeStamp_EndOfTrack
	@abstract	used to signal end of track
	@discussion Pass this value in to indicate a time passed the last event in the track.
				In this way, it's possible to perform edits on tracks which include all events
				starting at some particular time up to and including the last event
*/
#define kMusicTimeStamp_EndOfTrack			DBL_MAX

/*!
	@struct		MIDINoteMessage
	@discussion	The parameters to specify a MIDI note
*/
typedef struct MIDINoteMessage
{
	UInt8		channel;
	UInt8		note;
	UInt8		velocity;
	UInt8		releaseVelocity;	// was "reserved". 0 is the correct value when you don't know.
	Float32		duration;
} MIDINoteMessage;

/*!
	@struct		MIDIChannelMessage
	@discussion	The parameters to specify a MIDI channel message
*/
typedef struct MIDIChannelMessage
{
	UInt8		status;		// contains message and channel
	
	// message specific data
	UInt8		data1;		
	UInt8		data2;
	UInt8		reserved;
} MIDIChannelMessage;

/*!
	@struct		MIDIRawData
	@discussion	Generally used to represent a MIDI SysEx message
*/
typedef struct MIDIRawData
{
	UInt32		length;
	UInt8		data[1];
} MIDIRawData;

/*!
	@struct		MIDIMetaEvent
	@discussion	The parameters to specify a MIDI meta event
*/
typedef struct MIDIMetaEvent
{
	UInt8		metaEventType;
	UInt8		unused1;
	UInt8		unused2;
	UInt8		unused3;
	UInt32		dataLength;
	UInt8		data[1];
} MIDIMetaEvent;

/*!
	@struct		MusicEventUserData
	@discussion	Provides a general struct for specifying a user defined event. 
	@var  		length
					the size in bytes of the data
	@var  		data
					size bytes of user defined event data
*/
typedef struct MusicEventUserData
{
	UInt32		length;
	UInt8		data[1];
} MusicEventUserData;

/*!
	@struct		ExtendedNoteOnEvent
	@discussion	The parameters to specify an extended note on event
*/
typedef struct ExtendedNoteOnEvent
{
	MusicDeviceInstrumentID		instrumentID;
	MusicDeviceGroupID			groupID;
	Float32						duration;
	MusicDeviceNoteParams		extendedParams;
} ExtendedNoteOnEvent;

/*!
	@struct		ParameterEvent
	@discussion	The parameters to specify a parameter event to an audio unit.
*/
typedef struct ParameterEvent
{
	AudioUnitParameterID		parameterID;
	AudioUnitScope				scope;
    AudioUnitElement			element;
	AudioUnitParameterValue		value;
} ParameterEvent;

/*!
	@struct		ExtendedTempoEvent
	@discussion	specifies the value for a tempo in beats per minute
*/
typedef struct ExtendedTempoEvent
{
	Float64		bpm;
} ExtendedTempoEvent;

/*!
	@struct		AUPresetEvent
	@discussion	The parameters to specify a preset for an audio unit.
*/
typedef struct AUPresetEvent
{
	AudioUnitScope				scope;
    AudioUnitElement			element;
	CFPropertyListRef 			preset;
} AUPresetEvent;


/*!
	@struct		CABarBeatTime
	@abstract	A display representation of a musical time in beats.
	
	@var  	bar
				A measure number.
	@var  	beat
				A beat number (1..n).
	@var  	subbeat
				The numerator of the fractional number of beats.
	@var  	subbeatDivisor
				The denominator of the fractional number of beats.
	@var  	reserved
				Must be 0.
	@discussion
				A clock's internal representation of musical time is in beats based on the
				beginning of the timeline. Normally, such times should be displayed to the user
				in terms of bars, beats, and subbeats (sometimes called "units" or "parts per
				quarter" [PPQ]). This data structure is such a display representation.

				By convention, bar 1 is the beginning of the sequence. Beat 1 is the first beat
				of the measure. In 4/4 time, beat will have a value from 1 to 4. Music
				applications often use beat divisions such as 480 and 960.
*/
struct CABarBeatTime {
	SInt32				bar;
	UInt16				beat;
	UInt16				subbeat;
	UInt16				subbeatDivisor;
	UInt16				reserved;
};
typedef struct CABarBeatTime CABarBeatTime;

typedef struct OpaqueMusicPlayer		*MusicPlayer;
typedef struct OpaqueMusicSequence		*MusicSequence;
typedef struct OpaqueMusicTrack			*MusicTrack;
typedef struct OpaqueMusicEventIterator *MusicEventIterator;

/*!
	@typedef MusicSequenceUserCallback
	@discussion See MusicSequenceSetUserCallback
*/
typedef void (*MusicSequenceUserCallback)(	void * __nullable			inClientData,
											MusicSequence				inSequence,
											MusicTrack					inTrack,
											MusicTimeStamp				inEventTime,
											const MusicEventUserData *	inEventData,
											MusicTimeStamp				inStartSliceBeat,
											MusicTimeStamp				inEndSliceBeat);

/*!
	@enum MusicPlayerErrors
	@constant	kAudioToolboxErr_InvalidSequenceType
	@constant	kAudioToolboxErr_TrackIndexError
	@constant	kAudioToolboxErr_TrackNotFound
	@constant	kAudioToolboxErr_EndOfTrack
	@constant	kAudioToolboxErr_StartOfTrack
    @constant	kAudioToolboxErr_IllegalTrackDestination
    @constant	kAudioToolboxErr_NoSequence
	@constant	kAudioToolboxErr_InvalidEventType
	@constant	kAudioToolboxErr_InvalidPlayerState
	@constant	kAudioToolboxErr_CannotDoInCurrentContext
*/
CF_ENUM(OSStatus)
{
	kAudioToolboxErr_InvalidSequenceType		= -10846,
	kAudioToolboxErr_TrackIndexError 			= -10859,
	kAudioToolboxErr_TrackNotFound				= -10858,
	kAudioToolboxErr_EndOfTrack					= -10857,
	kAudioToolboxErr_StartOfTrack				= -10856,
    kAudioToolboxErr_IllegalTrackDestination	= -10855,
    kAudioToolboxErr_NoSequence 				= -10854,
	kAudioToolboxErr_InvalidEventType			= -10853,
	kAudioToolboxErr_InvalidPlayerState			= -10852,
	kAudioToolboxErr_CannotDoInCurrentContext	= -10863,
	kAudioToolboxError_NoTrackDestination		= -66720
};

/*!
	@enum MusicTrackProperties
	@discussion Property values are always get and set by reference
	
	@constant	kSequenceTrackProperty_LoopInfo
		read/write	- MusicTrackLoopInfo
		The default looping behaviour is off (track plays once)
		Looping is set by specifying the length of the loop. It loops from
			(TrackLength - loop length) to Track Length
			If numLoops is set to zero, it will loop forever.
		To turn looping off, you set this with loop length equal to zero.

	@constant	kSequenceTrackProperty_OffsetTime
		read/write	- MusicTimeStamp
		offset's the track's start time to the specified beat. By default this value is zero.
		
	@constant	kSequenceTrackProperty_MuteStatus
		read/write	- Boolean
		mute state of a track. By default this value is false (not muted)
		
	@constant	kSequenceTrackProperty_SoloStatus
		read/write	- Boolean
		solo state of a track. By default this value is false (not soloed)

	@constant	kSequenceTrackProperty_AutomatedParameters
		read/write	- UInt32
		Determines whether a track is used for automating parameters.
		If set to != 0 the track is used to automate parameter events to an AUNode.
		The track can only contain parameter events and these events are interpreted 
		as points in the automation curve
		
    @constant	kSequenceTrackProperty_TrackLength
		read/write	- MusicTimeStamp
		The time of the last event in the track plus any additional time that is allowed for fading out of ending notes
		or round a loop point to musical bar, etc.
		
		If this is not set, the track length will always be adjusted to the end of the last active event in a track and 
		is adjusted dynamically as events are added or removed.
		
		The property will return the max of the user set track length, or the calculated length
	 	
    @constant	kSequenceTrackProperty_TimeResolution
		read only	- SInt16 (only valid on the Tempo track)
		
		This retrieves the time resolution value for a sequence. This time resolution can be the resolution that
		was contained within the midi file used to construct a sequence. If you want to keep a time resolution
		when writing a new file, you can retrieve this value and then specify it when creating a new file from a sequence.
		
		It has no direct baring on the rendering or notion of time of the sequence itself (just its representation in file
		formats such as MIDI files). By default this is set to either:
			480 if the sequence is created manually
			some_value based on what was in a MIDI file if the sequence was created from a MIDI file		
*/
CF_ENUM(UInt32)
{
	kSequenceTrackProperty_LoopInfo = 0,
	kSequenceTrackProperty_OffsetTime = 1,
	kSequenceTrackProperty_MuteStatus = 2,
	kSequenceTrackProperty_SoloStatus = 3,
	// added in 10.2
	kSequenceTrackProperty_AutomatedParameters = 4,
	// added in 10.3
	kSequenceTrackProperty_TrackLength = 5,
	// added in 10.5
	kSequenceTrackProperty_TimeResolution = 6
};


/*!
	@struct		MusicTrackLoopInfo
	@discussion	Used to control the looping behaviour of a track
*/
typedef struct MusicTrackLoopInfo
{
	MusicTimeStamp		loopDuration;
	SInt32				numberOfLoops;
} MusicTrackLoopInfo;


//=====================================================================================================================
#pragma mark -

//=====================================================================================================================
#pragma mark Music Player
/*! 
	@functiongroup Music Player
*/

/*!
	@function	NewMusicPlayer
	@abstract	Create a new music player
	@discussion	A music player is used to play a sequence back. This call is used to create a player
				When a sequence is to be played by a player, it can play to either an AUGraph, a MIDI Destination or a
				mixture/combination of both.
	@param		outPlayer	the newly created player
*/
extern OSStatus
NewMusicPlayer(			MusicPlayer	__nullable * __nonnull outPlayer)			API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	DisposeMusicPlayer
	@abstract	Dispose a music player
	@param		inPlayer	the player to dispose
*/
extern OSStatus
DisposeMusicPlayer(		MusicPlayer		inPlayer)								API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));


/*!
	@function	MusicPlayerSetSequence
	@abstract	Set the sequence for the player to play
	@discussion A Sequence cannot be set on a player while it is playing. Setting a sequence
				will overide the currently set sequence.
	@param		inPlayer	the player
	@param		inSequence	the sequence for the player to play
*/
extern OSStatus
MusicPlayerSetSequence(	MusicPlayer 	inPlayer,
						MusicSequence __nullable inSequence)					API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicPlayerGetSequence
	@abstract	Get the sequence attached to a player
	@discussion If the player does not have a sequence set, this will return the _NoSequence error
	@param		inPlayer	the player
	@param		outSequence	the sequence currently set on the player
 
*/
extern OSStatus
MusicPlayerGetSequence(	MusicPlayer 	inPlayer,
						MusicSequence __nullable * __nonnull outSequence)		API_AVAILABLE(macos(10.3), ios(5.0), watchos(2.0), tvos(9.0));
								
/*!
	@function	MusicPlayerSetTime
	@abstract	Set the current time on the player
	@discussion The Get and Set Time calls take a specification of time as beats. This positions the player
				to the specified time based on the currently set sequence. No range checking on the time value
				is done. This can be set on a playing player (in which case playing will be resumed from the
				new time).
	@param		inPlayer	the player
	@param		inTime		the new time value
*/
extern OSStatus
MusicPlayerSetTime(		MusicPlayer 	inPlayer,
						MusicTimeStamp 	inTime)									API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicPlayerGetTime
	@abstract	Get the current time of the player
	@discussion The Get and Set Time calls take a specification of time as beats. This retrieves the player's
				current time. If it is playing this time is the time of the player at the time the call was made. 
	@param		inPlayer	the player
	@param		outTime		the current time value
*/
extern OSStatus
MusicPlayerGetTime(		MusicPlayer 	inPlayer,
						MusicTimeStamp	*outTime)								API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicPlayerGetHostTimeForBeats
	@abstract	Returns the host time that will be (or was) played at the specified beat.
	@discussion This call is only valid if the player is playing and will return an error if the player is not playing
				or if the starting position of the player (its "starting beat") was after the specified beat.
				For general translation of beats to time in a sequence, see the MusicSequence calls for beat<->seconds.
				
				The call uses the player's sequence's tempo map to translate a beat time from the starting time and beat
				of the player.
	@param		inPlayer	the player
	@param		inBeats		the specified beat-time value
	@param		outHostTime the corresponding host time
*/
extern OSStatus
MusicPlayerGetHostTimeForBeats(	MusicPlayer 	inPlayer,
								MusicTimeStamp	inBeats,
								UInt64 *		outHostTime)					API_AVAILABLE(macos(10.2), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicPlayerGetBeatsForHostTime
	@abstract	Returns the beat that will be (or was) played at the specified host time. 
	@discussion This call is only valid if the player is playing and will return an error if the player is not playing
				or if the starting time of the player was after the specified host time.
				For general translation of beats to time in a sequence, see the MusicSequence calls for beat<->seconds.
				
				The call uses the player's sequence's tempo map to retrieve a beat time from the starting and specified host time. 
				
	@param		inPlayer	the player
	@param		inHostTime	the specified host time value
	@param		outBeats	the corresponding beat time
*/
extern OSStatus
MusicPlayerGetBeatsForHostTime(	MusicPlayer 	inPlayer,
								UInt64			inHostTime,
								MusicTimeStamp *outBeats)						API_AVAILABLE(macos(10.2), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicPlayerPreroll
	@abstract	Prepare the player for playing
	@discussion Allows the player to prepare its state so that starting is has a lower latency. If a player is started without
				being prerolled, the player will pre-roll itself and then start.
	@param		inPlayer	the player
*/
extern OSStatus
MusicPlayerPreroll(		MusicPlayer 	inPlayer)								API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicPlayerStart
	@abstract	Start the player
	@discussion If the player has not been prerolled, it will pre-roll itself and then start.
	@param		inPlayer	the player
*/
extern OSStatus
MusicPlayerStart(		MusicPlayer 	inPlayer)								API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicPlayerStop
	@abstract	Stop the player
	@param		inPlayer	the player
*/
extern OSStatus
MusicPlayerStop(		MusicPlayer 	inPlayer)								API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

// 
/*!
	@function	MusicPlayerIsPlaying
	@abstract	Returns the playing state of the player. "Is it playing?"
	@discussion This call returns a non-zero value in outIsPlaying if the player has been
				started and not stopped. It may have "played" past the events of the attached
				MusicSequence, but it is still considered to be playing (and its time value increasing)
				until it is explicitly stopped
	@param		inPlayer		the player
	@param		outIsPlaying	false if not, true (non-zero) if is playing
*/
extern OSStatus
MusicPlayerIsPlaying(	MusicPlayer 	inPlayer,
						Boolean *		outIsPlaying)							API_AVAILABLE(macos(10.2), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicPlayerSetPlayRateScalar
	@abstract	Scale the playback rate of the player
	@param		inPlayer	the player
	@param		inScaleRate	a scalar that will be applied to the playback rate. If 2, playback is twice as fast, if
				0.5 it is half as fast. As a scalar, the value must be greater than zero.
*/
extern OSStatus
MusicPlayerSetPlayRateScalar(	MusicPlayer		inPlayer,
								Float64			inScaleRate)					API_AVAILABLE(macos(10.3), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicPlayerGetPlayRateScalar
	@abstract	Get the playback rate scalar of the player
	@param		inPlayer		the player
	@param		outScaleRate	the current scalar being applied to the player. Default value is 1.0
*/
extern OSStatus
MusicPlayerGetPlayRateScalar(	MusicPlayer		inPlayer,
								Float64 *		outScaleRate)					API_AVAILABLE(macos(10.3), ios(5.0), watchos(2.0), tvos(9.0));


//=====================================================================================================================
#pragma mark -

//=====================================================================================================================
#pragma mark Music Sequence
/*! 
	@functiongroup Music Sequence
*/
/*!
	@function	NewMusicSequence
	@abstract	Create a new empty sequence
	@discussion	A new music sequence will only have a tempo track (with a default tempo of 120 bpm), 
				and the default type is beat based.

				When a sequence is to be played by a player, it can play to either an AUGraph, a MIDI Destination or a
				mixture/combination of both. See MusicSequenceSetAUGraph and MusicSequenceSetMIDIEndpoint for the generic
				destination assignments. Specific tracks can also be assigned nodes of a graph or a MIDI endpoint as targets
				for the events that they contain; see MusicTrackSetDestNode and MusicTrackSetDestMIDIEndpoint.
				
	@param		outSequence		the new sequence
*/
extern OSStatus
NewMusicSequence(	MusicSequence __nullable * __nonnull outSequence)			API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	DisposeMusicSequence
	@abstract	Dispose the sequence
	@discussion	 A sequence cannot be disposed while a MusicPlayer has it.
	@param		inSequence		the sequence
*/
extern OSStatus
DisposeMusicSequence(		MusicSequence		inSequence)						API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceNewTrack
	@abstract	Add a new (empty) track to the sequence
	@param		inSequence		the sequence
	@param		outTrack		the new track (it is always appended to any existing tracks)
*/
extern OSStatus
MusicSequenceNewTrack(		MusicSequence 		inSequence,
							MusicTrack __nullable * __nonnull outTrack)			API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));
													
/*!
	@function	MusicSequenceDisposeTrack
	@abstract	Remove and dispose a track from a sequence
	@param		inSequence		the sequence
	@param		inTrack			the track to remove and dispose
*/
extern OSStatus
MusicSequenceDisposeTrack(	MusicSequence 		inSequence,
							MusicTrack 			inTrack)						API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceGetTrackCount
	@abstract	The number of tracks in a sequence. 
				The track count and accessors exclude the tempo track (which is treated as a special case)
	@param		inSequence			the sequence
	@param		outNumberOfTracks	the number of tracks
*/
extern OSStatus
MusicSequenceGetTrackCount(	MusicSequence 		inSequence,
							UInt32 				*outNumberOfTracks)				API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));
										
/*!
	@function	MusicSequenceGetIndTrack
	@abstract	Get a track at the specified index
	@discussion Index is zero based. It will return kAudio_ParamError if index is not in the range: 0 < TrackCount
				The track count and accessors exclude the tempo track (which is treated as a special case)
	@param		inSequence		the sequence
	@param		inTrackIndex	the index
	@param		outTrack		the track at that index
*/
extern OSStatus
MusicSequenceGetIndTrack(	MusicSequence 						inSequence,
							UInt32 								inTrackIndex,
							MusicTrack __nullable * __nonnull	outTrack)		API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceGetTrackIndex
	@abstract	Get the index for a specific track
	@discussion Index is zero based. It will return an error if the track is not a member of the sequence.
				The track count and accessors exclude the tempo track (which is treated as a special case)
	@param		inSequence		the sequence
	@param		inTrack			the track
	@param		outTrackIndex	the index of the track
*/
extern OSStatus
MusicSequenceGetTrackIndex(	MusicSequence 		inSequence,
							MusicTrack 			inTrack,
							UInt32				*outTrackIndex)					API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceGetTempoTrack
	@abstract	Get the tempo track of the sequence
	@discussion	Each sequence has a single tempo track. All tempo events are placed into this tempo track (as well
				as other appropriate events (time sig for instance from a MIDI file). The tempo track, once retrieved
				can be edited and iterated upon as any other track. Non-tempo events in a tempo track are ignored.
	@param		inSequence		the sequence
	@param		outTrack		the tempo track of the sequence
*/
extern OSStatus
MusicSequenceGetTempoTrack(	MusicSequence						inSequence,
							MusicTrack __nullable * __nonnull	outTrack)		API_AVAILABLE(macos(10.1), ios(5.0), watchos(2.0), tvos(9.0));


/*!
	@function	MusicSequenceSetAUGraph
	@abstract	Set the graph to be associated with the sequence
	@discussion	A sequence can be associated with an AUGraph and this graph will be used to render the events as 
				controlled by the sequence when it is played. By default, all of the tracks of a sequence will
				find the first AUNode that is an instance of an Apple MusicDevice audio unit (see MusicSequenceGetAUGraph).
				Specific nodes of the graph can be targeted for different tracks (see MusicTrackSetDestNode).  To render a
 				multi-track GM MIDI sequence on iOS, create a custom graph with a MIDISynth audio unit as the MusicDevice.
 				If inGraph is set to NULL, the sequence will reset to use the default graph.
	@param		inSequence		the sequence
	@param		inGraph			the graph
*/
extern OSStatus
MusicSequenceSetAUGraph(	MusicSequence 	   inSequence,
							AUGraph __nullable inGraph)							API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));


/*!
	@function	MusicSequenceGetAUGraph
	@abstract	Gets the graph currently associated with a sequence
	@discussion	By default if no graph is assigned to a sequence then the sequence will create a default graph. 
				This default graph contains a MusicDevice and a DynamicsProcessor and all tracks will be targeted
				to the MusicDevice.  On Mac OS X, this MusicDevice is an instance of a software synthesizer that is 
				compatible with the GM and GS MIDI standards.  On iOS, it is an instance of a monotimbral software 
				synthesizer designed to render events from a single MIDI channel.  To render multi-track GM MIDI
 				sequences on iOS, create a custom graph with a MIDISynth audio unit as the MusicDevice.
				
				This call will thus either return the graph as set by the user, or this default graph.
	@param		inSequence		the sequence
	@param		outGraph		the graph
*/
extern OSStatus
MusicSequenceGetAUGraph(	MusicSequence 					inSequence,
							AUGraph __nullable * __nonnull	outGraph)			API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceSetMIDIEndpoint
	@abstract	Makes the target of all of the tracks in the sequence a MIDI endpoint
	@discussion	This is a convenience function, and is equivalent to iterating through all of the tracks in a sequence
				and targeting each track to the MIDI endpoint
				
	@param		inSequence		the sequence
	@param		inEndpoint		the MIDI endpoint
*/
extern OSStatus
MusicSequenceSetMIDIEndpoint(	MusicSequence 	inSequence,
								MIDIEndpointRef	inEndpoint)						API_AVAILABLE(macos(10.1), ios(5.0), tvos(12.0)) __WATCHOS_PROHIBITED;
	
/*!
	@function	MusicSequenceSetSequenceType
	@abstract	Set the sequence type (the default is beats)
	@discussion
				These two calls allow you to get and set a MusicSequence type; specifying
					kMusicSequenceType_Beats		= 'beat',
					kMusicSequenceType_Seconds		= 'secs',
					kMusicSequenceType_Samples		= 'samp'

				The sequence type can be set to beats at any time. The sequence type can only be set to 
				seconds or samples if there are NO tempo events already in the sequence.
				
				For beats - it can have as many tempo events as you want
				For Samples and Seconds - you should add a single tempo event after setting the type
					Samples - the tempo is the desired sample rate - e.g. 44100 and each "beat" in the sequence will be
						interpreted as a sample count at that sample rate (so beat == 44100 is a second)
					Seconds - the tempo should be set to 60 - a beat is a second.

				Beats is the default (and is the behaviour on pre 10.5 systems)

				A meta event of interest for Seconds based MIDI files is the SMPTE Offset meta event - stored in the tempo track.
				The sequence doesn't do anything with this event (except store/write it)	
	@param		inSequence	the sequence
	@param		inType		the sequence type
*/
extern OSStatus
MusicSequenceSetSequenceType(	MusicSequence		inSequence,
							MusicSequenceType		inType)						API_AVAILABLE(macos(10.5), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceGetSequenceType
	@abstract	Get the sequence type
	@discussion	See SetSequence for a full description
	@param		inSequence		the sequence
	@param		outType			the type
*/
extern OSStatus
MusicSequenceGetSequenceType(	MusicSequence		inSequence,
							MusicSequenceType * 	outType)					API_AVAILABLE(macos(10.5), ios(5.0), watchos(2.0), tvos(9.0));


/*!
	@function	MusicSequenceFileLoad
	@abstract	Load the data contained within the referenced file to the sequence
	@discussion	This function will parse the file referenced by the URL and add the events to the sequence.
	@param		inSequence		the sequence
	@param		inFileRef		a file:// URL that references a file
	@param		inFileTypeHint	provides a hint to the sequence on the file type being imported
	@param		inFlags			flags that can control how the data is parsed in the file and laid out in the tracks
								that will be created and added to the sequence in this operation
*/
extern OSStatus
MusicSequenceFileLoad (MusicSequence				inSequence,
						CFURLRef					inFileRef,
						MusicSequenceFileTypeID		inFileTypeHint, // can be zero in many cases
						MusicSequenceLoadFlags		inFlags)					API_AVAILABLE(macos(10.5), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceFileLoadData
	@abstract	Load the data to the sequence
	@discussion	This function will parse the data and add the events to the sequence. The data provided needs to 
				be of a particular file type as specified by the fileTypeHint.
	@param		inSequence		the sequence
	@param		inData			the contents of a valid file loaded into a CFData object
	@param		inFileTypeHint	provides a hint to the sequence on the file type being imported
	@param		inFlags			flags that can control how the data is parsed in the file and laid out in the tracks
								that will be created and added to the sequence in this operation
*/
extern OSStatus
MusicSequenceFileLoadData (MusicSequence			inSequence,
						CFDataRef					inData,
						MusicSequenceFileTypeID		inFileTypeHint, // can be zero in many cases
						MusicSequenceLoadFlags		inFlags)					API_AVAILABLE(macos(10.5), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceSetSMPTEResolution
	@abstract	Helper function to establish the SMPTE based MIDI file resolution for the specified ticks
	@discussion SMPTE resolution helpers for dealing with the interpretation and creation of
				tick values for standard MIDI files (see MusicSequenceFileCreate)
	@param		fps		the frames per second
	@param		ticks	the ticks per quarter note
	@result		the resolution that can be used when creating a MIDI file derived from the two parameters
*/
CF_INLINE SInt16 
MusicSequenceSetSMPTEResolution (SignedByte fps, Byte ticks) 
{
	SInt8 res8 = fps < 0 ? fps : -fps;
	SInt16 res = (SInt16) (res8 << 8);
	res += ticks;
	return res;
}

/*!
	@function	MusicSequenceGetSMPTEResolution
	@abstract	Helper function to get the fps and ticks from their representation in a SMPTE based MIDI file
	@discussion SMPTE resolution helpers for dealing with the interpretation and creation of
				tick values for standard MIDI files (see MusicSequenceFileCreate)
	@param		inRes	the resolution from a MIDI file
	@param		fps		the frames per second
	@param		ticks	the ticks per quarter note
*/
CF_INLINE void 
MusicSequenceGetSMPTEResolution (SInt16 inRes, SignedByte * fps, Byte * ticks) 
{
	*fps = (SignedByte)((0xFF00 & inRes) >> 8);
	*ticks = 0x7F & inRes;			
}

/*!
	@function	MusicSequenceFileCreate
	@abstract	Create a file from a sequence
	@discussion	This function can be (and is most commonly) used to create a MIDI file from the events in a sequence.
				Only MIDI based events are used when creating the MIDI file. MIDI files are normally beat based, but
				can also have a SMPTE (or real-time rather than beat time) representation.
				
				inResolution is relationship between "tick" and quarter note for saving to Standard MIDI File
					- pass in zero to use default - this will be the value that is currently set on the tempo track
					- see the comments for the set track property's time resolution
				
				The different Sequence types determine the kinds of files that can be created:

				Beats
					When saving a MIDI file, it saves a beats (PPQ) based axis

				Seconds
					When saving a MIDI file, it will save it as a SMPTE resolution - so you should specify this resolution
					when creating the MIDI file. 
					If zero is specified, 25 fps and 40 ticks/frame is used (a time scale of a millisecond)
			
				Samples
					You cannot save to a MIDI file with this sequence type

				The complete meaning of the 16-bit "division" field in a MIDI File's MThd chunk.

				If it is positive, then a tick represents 1/D quarter notes.

				If it negative:

				bits 14-8 are a signed 7-bit number representing the SMPTE format:
					-24, -25, -29 (drop), -30
				bits 7-0 represents the number of ticks per SMPTE frame
					typical values: 4, 10, 80, 100

				You can obtain millisecond resolution by specifying 25 frames/sec and 40 divisions/frame.

				30 fps with 80 bits (ticks) per frame: 0xE250  ((char)0xE2 == -30)

	@param		inSequence		the sequence
	@param		inFileRef		the location of the file to create
	@param		inFileType		the type of file to create
	@param		inFlags			flags to control the file creation
	@param		inResolution	the resolution (depending on file type and sequence type)
*/
extern OSStatus
MusicSequenceFileCreate (MusicSequence				inSequence,
						CFURLRef					inFileRef,
						MusicSequenceFileTypeID		inFileType,
						MusicSequenceFileFlags		inFlags,
						SInt16						inResolution)				API_AVAILABLE(macos(10.5), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceFileCreateData
	@abstract	Create a data object from a sequence
	@discussion	The same basic parameters apply to this as with the MusicSequenceFileCreate function. The difference
				being that that function will create a file on disk, whereas this one will create a CFData object
				that is a file in memory. The CFData object should be released by the caller.
	@param		inSequence		the sequence
	@param		inFileType		the type of file to create
	@param		inFlags			flags to control the file creation
	@param		inResolution	the resolution (depending on file type and sequence type)
	@param		outData			the resulting data object
*/
extern OSStatus
MusicSequenceFileCreateData (MusicSequence					inSequence,
						MusicSequenceFileTypeID				inFileType,
						MusicSequenceFileFlags				inFlags,
						SInt16								inResolution,
						CFDataRef __nullable * __nonnull	outData)			API_AVAILABLE(macos(10.5), ios(5.0), watchos(2.0), tvos(9.0));


/*!
	@function	MusicSequenceReverse
	@abstract	Reverse in time all events in a sequence, including the tempo events
	@param		inSequence		the sequence
*/
extern OSStatus
MusicSequenceReverse(		MusicSequence	inSequence)							API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceGetSecondsForBeats
	@abstract	Returns a seconds value that would correspond to the supplied beats
	@discussion	Uses the sequence's tempo events 
	@param		inSequence		the sequence
	@param		inBeats			the beats
	@param		outSeconds		the seconds (time from 0 beat)
*/
extern OSStatus
MusicSequenceGetSecondsForBeats(	MusicSequence		inSequence,
									MusicTimeStamp		inBeats,
									Float64 *			outSeconds)				API_AVAILABLE(macos(10.2), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceGetBeatsForSeconds
	@abstract	Returns a beat value that would correspond to the supplied seconds from zero.
	@discussion	Uses the sequence's tempo events 
	@param		inSequence		the sequence
	@param		inSeconds		the seconds
	@param		outBeats		the corresponding beat
*/
extern OSStatus
MusicSequenceGetBeatsForSeconds(	MusicSequence		inSequence,
									Float64				inSeconds,
									MusicTimeStamp *	outBeats)				API_AVAILABLE(macos(10.2), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceSetUserCallback
	@abstract	Establish a user callback for a sequence
	@discussion	This call is used to register (or remove if inCallback is NULL) a callback
				that the MusicSequence will call for ANY UserEvents that are added to any of the
				tracks of the sequence.
				
				If there is a callback registered, then UserEvents will be chased when
				MusicPlayerSetTime is called. In that case the inStartSliceBeat and inEndSliceBeat
				will both be the same value and will be the beat that the player is chasing too.
				
				In normal cases, where the sequence data is being scheduled for playback, the
				following will apply:
					inStartSliceBeat <= inEventTime < inEndSliceBeat
				
				The only exception to this is if the track that owns the MusicEvent is looping.
				In this case the start beat will still be less than the end beat (so your callback
				can still determine that it is playing, and what beats are currently being scheduled),
				however, the inEventTime will be the original time-stamped time of the user event. 
	@param		inSequence		the sequence
	@param		inCallback		the callback
	@param		inClientData	client (user supplied) data provided back to the callback when it is called by the sequence
*/
extern OSStatus
MusicSequenceSetUserCallback(	MusicSequence							inSequence,
								MusicSequenceUserCallback __nullable	inCallback,
								void * __nullable						inClientData)		API_AVAILABLE(macos(10.3), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceBeatsToBarBeatTime
	@abstract	Convenience function to format a sequence's beat time to its bar-beat time
	@discussion	The sequence's tempo track Time Sig events are used to
				to calculate the bar-beat representation. If there are no Time Sig events added to the sequence
				4/4 is assumed. A Time Sig event is a MIDI Meta Event as specified for MIDI files.
	@param		inSequence		the sequence
	@param		inBeats			the beat which should be represented by the bar-beat
	@param		inSubbeatDivisor	The denominator of the fractional number of beats.
	@param		outBarBeatTime	the formatted bar/beat time
*/
extern OSStatus
MusicSequenceBeatsToBarBeatTime(MusicSequence				inSequence,
								MusicTimeStamp				inBeats,
								UInt32						inSubbeatDivisor,
								CABarBeatTime *				outBarBeatTime)		API_AVAILABLE(macos(10.5), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceBarBeatTimeToBeats
	@abstract	Convenience function to format a bar-beat time to a sequence's beat time
	@discussion	The sequence's tempo track Time Sig events are used to
				to calculate the bar-beat representation. If there are no Time Sig events added to the sequence
				4/4 is assumed. A Time Sig event is a MIDI Meta Event as specified for MIDI files.
	@param		inSequence		the sequence
	@param		inBarBeatTime	the bar-beat time
	@param		outBeats		the sequence's beat time for that bar-beat time
*/
extern OSStatus
MusicSequenceBarBeatTimeToBeats(MusicSequence				inSequence,
								const CABarBeatTime *		inBarBeatTime,
								MusicTimeStamp *			outBeats)			API_AVAILABLE(macos(10.5), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicSequenceGetInfoDictionary
	@abstract	Returns a dictionary containing meta-data derived from a sequence
	@discussion	The dictionary can contain one or more of the kAFInfoDictionary_* 
				keys specified in <AudioToolbox/AudioFile.h>
				
				The caller should release the returned dictionary. If the call fails it will return NULL

	@param		inSequence		the sequence
	@result		a CFDictionary or NULL if the call fails.
*/

CF_IMPLICIT_BRIDGING_ENABLED

extern CFDictionaryRef
MusicSequenceGetInfoDictionary(	MusicSequence				inSequence)			API_AVAILABLE(macos(10.5), ios(5.0), watchos(2.0), tvos(9.0));

CF_IMPLICIT_BRIDGING_DISABLED

//=====================================================================================================================
#pragma mark -

//=====================================================================================================================
#pragma mark Music Track
/*! 
	@functiongroup Music Track
*/

/*!
	@function	MusicTrackGetSequence
	@abstract	Gets the sequence which the track is a member of
	@param		inTrack		the track
	@param		outSequence the track's sequence
*/
extern OSStatus
MusicTrackGetSequence(	MusicTrack 			inTrack,
						MusicSequence __nullable * __nonnull outSequence)		API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicTrackSetDestNode
	@abstract	Sets the track's target to the specified AUNode
	@discussion	The node must be a member of the graph that the track's sequence is using. When played, the track
				will send all of its events to that node.
	@param		inTrack		the track
	@param		inNode		the new node
*/
extern OSStatus
MusicTrackSetDestNode(	MusicTrack 			inTrack,
						AUNode				inNode)								API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicTrackSetDestMIDIEndpoint
	@abstract	Sets the track's target to the specified MIDI endpoint
	@discussion	When played, the track will send all of its events to the specified MIDI Endpoint.
	@param		inTrack		the track
	@param		inEndpoint	the new MIDI endpoint
*/
extern OSStatus
MusicTrackSetDestMIDIEndpoint(	MusicTrack			inTrack,
								MIDIEndpointRef		inEndpoint)					API_AVAILABLE(macos(10.1), ios(5.0), tvos(12.0)) __WATCHOS_PROHIBITED;
	
/*!
	@function	MusicTrackGetDestNode
	@abstract	Gets the track's target if it is an AUNode
	@discussion	Returns kAudioToolboxErr_IllegalTrackDestination if the track's target is a MIDIEndpointRef 
				and NOT an AUNode
	@param		inTrack		the track
	@param		outNode		the node target for the track
*/
extern OSStatus
MusicTrackGetDestNode(			MusicTrack 			inTrack,
								AUNode *			outNode)					API_AVAILABLE(macos(10.1), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicTrackGetDestMIDIEndpoint
	@abstract	Gets the track's target if it is a MIDI Endpoint
	@discussion	Returns kAudioToolboxErr_IllegalTrackDestination if the track's target is an AUNode 
				and NOT a MIDI Endpoint
	@param		inTrack		the track
	@param		outEndpoint	the MIDI Endpoint target for the track
*/
extern OSStatus
MusicTrackGetDestMIDIEndpoint(	MusicTrack			inTrack,
								MIDIEndpointRef	*	outEndpoint)				API_AVAILABLE(macos(10.1), ios(5.0), tvos(12.0)) __WATCHOS_PROHIBITED;
	
/*!
	@function	MusicTrackSetProperty
	@abstract	Sets the specified property value
	@discussion Property values are always get and set by reference
	@param		inTrack			the track
	@param		inPropertyID	the property ID
	@param		inData			the new property value
	@param		inLength		the size of the property value being set
*/
extern OSStatus
MusicTrackSetProperty(	MusicTrack 			inTrack,
						UInt32 				inPropertyID,
						void				*inData,
						UInt32				inLength)							API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicTrackGetProperty
	@abstract	Gets the specified property value
	@discussion	If outData is NULL, then the size of the data will be passed back in ioLength
				This allows the client to allocate a buffer of the correct size (useful for variable
				length properties -- currently all properties have fixed size)
				Property values are always get and set by reference
	@param		inTrack			the track
	@param		inPropertyID	the property ID
	@param		outData			if not NULL, points to data of size ioLength
	@param		ioLength		on input the available size of outData, on output the size of the valid data that outData
								will then point too.
*/
extern OSStatus
MusicTrackGetProperty(	MusicTrack 			inTrack,
						UInt32 				inPropertyID,
						void				*outData,
						UInt32				*ioLength)							API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Editing operations on sequence tracks

/*!
	@function	MusicTrackMoveEvents
	@abstract	Move events in a track
	@discussion	Moves all of the events in the specified time range by the moveTime. MoveTime maybe negative to 
				move events backwards (towards zero).
				
				All time ranges are [starttime < endtime]
				
	@param		inTrack			the track
	@param		inStartTime		the start time for the range of events
	@param		inEndTime		the end time up to which will form the range of the events to move
	@param		inMoveTime		amount of beats to move the selected events.
*/
extern OSStatus
MusicTrackMoveEvents(	MusicTrack 			inTrack,
						MusicTimeStamp		inStartTime,
						MusicTimeStamp		inEndTime,
						MusicTimeStamp		inMoveTime)							API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicTrackClear
	@abstract	Removes all events within the specified range
	@discussion	All time ranges are [starttime < endtime]
	@param		inTrack		the track
	@param		inStartTime	the start time for the range of events
	@param		inEndTime	the end time up to which will form the range of the events to clear
*/
extern OSStatus
MusicTrackClear(		MusicTrack 			inTrack,
						MusicTimeStamp		inStartTime,
						MusicTimeStamp		inEndTime)							API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicTrackCut
	@abstract	Removes all the events within the specified range
	@discussion	Events that fall past the specified range will be moved back by the specified range time.
				
				All time ranges are [starttime < endtime]
				
	@param		inTrack		the track
	@param		inStartTime	the start time for the range of events
	@param		inEndTime	the end time up to which will form the range of the events to cut out
*/
extern OSStatus
MusicTrackCut(			MusicTrack 			inTrack,
						MusicTimeStamp		inStartTime,
						MusicTimeStamp		inEndTime)							API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicTrackCopyInsert
	@abstract	Copies events from one track and inserts them into another
	@discussion	Copies all of the events with the specified time range of the source track. It then inserts
				those events into the destination track. All events at and after inDestInsertTime in inDestTrack 
				are moved forward by the range's duration
				
				All time ranges are [starttime < endtime]
				
	@param		inSourceTrack		the source track
	@param		inSourceStartTime	the start time for the range of events
	@param		inSourceEndTime		the end time up to which will form the range of the events to copy from the source track
	@param		inDestTrack			the destination track to copy too
	@param		inDestInsertTime	the time at which the copied events will be inserted.
*/
extern OSStatus
MusicTrackCopyInsert(	MusicTrack 			inSourceTrack,
						MusicTimeStamp		inSourceStartTime,
						MusicTimeStamp		inSourceEndTime,
						MusicTrack 			inDestTrack,
						MusicTimeStamp		inDestInsertTime)					API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicTrackMerge
	@abstract	Copies events from one track and merges them into another
	@discussion	Copies all of the events with the specified time range of the source track. It then merges
				those events into the destination track starting at inDestInsertTime.
				
				All time ranges are [starttime < endtime]
				
	@param		inSourceTrack		the source track
	@param		inSourceStartTime	the start time for the range of events
	@param		inSourceEndTime		the end time up to which will form the range of the events to copy from the source track
	@param		inDestTrack			the destination track to copy too
	@param		inDestInsertTime	the time at which the copied events will be merged.
*/
extern OSStatus
MusicTrackMerge(		MusicTrack 			inSourceTrack,
						MusicTimeStamp		inSourceStartTime,
						MusicTimeStamp		inSourceEndTime,
						MusicTrack 			inDestTrack,
						MusicTimeStamp		inDestInsertTime)					API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));


//=====================================================================================================================
#pragma mark -

//=====================================================================================================================
#pragma mark Music Events
/*! 
	@functiongroup Music Events
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// adding time-stamped events to the track

/*!
	@function	MusicTrackNewMIDINoteEvent
	@abstract	Adds a MIDINoteMessage event to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inMessage		the event
*/
extern OSStatus
MusicTrackNewMIDINoteEvent(			MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MIDINoteMessage *		inMessage)		API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicTrackNewMIDIChannelEvent
	@abstract	Adds a MIDIChannelMessage event to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inMessage		the event
*/
extern OSStatus
MusicTrackNewMIDIChannelEvent(		MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MIDIChannelMessage *	inMessage)		API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicTrackNewMIDIRawDataEvent
	@abstract	Adds a MIDIRawData event to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inRawData		the event
*/
extern OSStatus
MusicTrackNewMIDIRawDataEvent(		MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MIDIRawData *			inRawData)		API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicTrackNewExtendedNoteEvent
	@abstract	Adds a ExtendedNoteOnEvent to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inInfo			the event
*/
extern OSStatus
MusicTrackNewExtendedNoteEvent(		MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const ExtendedNoteOnEvent	*inInfo)		API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));
										
/*!
	@function	MusicTrackNewParameterEvent
	@abstract	Adds a ParameterEvent to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inInfo			the event
*/
extern OSStatus
MusicTrackNewParameterEvent(		MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const ParameterEvent *		inInfo)			API_AVAILABLE(macos(10.2), ios(5.0), watchos(2.0), tvos(9.0));
										
/*!
	@function	MusicTrackNewExtendedTempoEvent
	@abstract	Adds a tempo event to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inBPM			the event
*/
extern OSStatus
MusicTrackNewExtendedTempoEvent(	MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									Float64						inBPM)			API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));
										
/*!
	@function	MusicTrackNewMetaEvent
	@abstract	Adds a MIDIMetaEvent to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inMetaEvent		the event
*/
extern OSStatus
MusicTrackNewMetaEvent(				MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MIDIMetaEvent *		inMetaEvent)	API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));
										
/*!
	@function	MusicEventUserData
	@abstract	Adds a MusicEventUserData event to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inUserData		the event
*/
extern OSStatus
MusicTrackNewUserEvent(				MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const MusicEventUserData *	inUserData)		API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicTrackNewAUPresetEvent
	@abstract	Adds a AUPresetEvent to a track
	@discussion	The event is added at the specified time stamp. The time stamp should not be less than zero.
	@param		inTrack			the track
	@param		inTimeStamp		the time stamp
	@param		inPresetEvent	the event
*/
extern OSStatus
MusicTrackNewAUPresetEvent(			MusicTrack 					inTrack,
									MusicTimeStamp			 	inTimeStamp,
									const AUPresetEvent *		inPresetEvent)	API_AVAILABLE(macos(10.3), ios(5.0), watchos(2.0), tvos(9.0));



//=====================================================================================================================
#pragma mark -

//=====================================================================================================================
#pragma mark Music Event Iterator
/*! 
	@functiongroup Music Event Iterator
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// actual event representation and manipulation within a track....
//
// Here we need to be very careful to be able to deal with both SMF type of MIDI events, and
// also be upwardly compatible with an extended MPEG4-SA like paradigm!
//
// The solution is to hide the internal event representation from the client
// and allow access to the events through accessor functions.  The user, in this way, can
// examine and create standard events, or any user-defined event.


/*!
	@function	NewMusicEventIterator
	@abstract	Creates an iterator to iterator over a track's events
	@discussion	The iterator should be considered invalid if a track is edited. In that case you should create a new
				iterator and seek it to the desired position.
				
	@param		inTrack			the track upon which to iterate
	@param		outIterator		the new iterator
*/
extern OSStatus
NewMusicEventIterator(		MusicTrack 									inTrack,
							MusicEventIterator __nullable * __nonnull	outIterator)	API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));
													
/*!
	@function	DisposeMusicEventIterator
	@abstract	Dispose an iterator
	@param		inIterator		the iterator
*/
extern OSStatus
DisposeMusicEventIterator(			MusicEventIterator	inIterator)				API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicEventIteratorSeek
	@abstract	Move the iterator to an event at the specified time
	@discussion If there is no event at the specified time, the iterator will point to the first event after
				that time.
				By specifying kMusicTimeStamp_EndOfTrack you will position the iterator to the end of track
				(which is pointing to the space just AFTER the last event). You can use MusicEventIteratorPreviousEvent 
				to backup to the last event.
				By specifying 0, you will position the iterator at the first event
	@param		inIterator		the iterator
	@param		inTimeStamp		the time stamp to seek too
*/
extern OSStatus
MusicEventIteratorSeek(				MusicEventIterator 	inIterator,
									MusicTimeStamp 		inTimeStamp)			API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicEventIteratorNextEvent
	@abstract	Move the iterator to the next event
	@discussion If the iterator was at the last event, then it will move past the last event and will no longer point
				to an event. You can use check MusicEventIteratorHasCurrentEvent to see if there is an event at the 
				iterator's current position. See also MusicEventIteratorHasNextEvent.
				
				Typically this call is used to move the iterator forwards through the track's events.
	@param		inIterator		the iterator
*/
extern OSStatus
MusicEventIteratorNextEvent(		MusicEventIterator 	inIterator)				API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicEventIteratorPreviousEvent
	@abstract	Move the iterator to the previous event
	@discussion If the iterator was at the first event, then it will leave the iterator unchanged and return an error. 
				See also MusicEventIteratorHasPreviousEvent

				Typically this call is used to move the iterator backwards through the track's events.
	@param		inIterator		the iterator
*/
extern OSStatus
MusicEventIteratorPreviousEvent(	MusicEventIterator 	inIterator)				API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicEventIteratorGetEventInfo
	@abstract	Retrieves the event data at the iterator.
	@discussion Retrieves the event and other information from the iterator's current position.
	
				If you do not want specific information (eg, the time stamp) pass in NULL for that parameter.
				
	@param		inIterator		the iterator
	@param		outTimeStamp	the time stamp of the event
	@param		outEventType	one of kMusicEventType_XXX that indicates what kind of event type the iterator
								is currently pointing too
	@param		outEventData	a reference to the event data. The type of data is described by the eventType. This data
								is read only and should not be edited in place.
	@param		outEventDataSize	the size of the data referenced by outEventData
*/
extern OSStatus
MusicEventIteratorGetEventInfo(		MusicEventIterator 		inIterator,
									MusicTimeStamp *		outTimeStamp,
									MusicEventType *		outEventType,
									const void * __nullable * __nonnull outEventData,
									UInt32 *				outEventDataSize)	API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));
	
/*!
	@function	MusicEventIteratorSetEventInfo
	@abstract	Changes the type or value of an event
	@discussion Allows you to change either the event type, or the values of the event data, that the iterator is 
				currently pointing too. You cannot change the event's time (to do that you should use 
				MusicEventIteratorSetEventTime).
				
	@param		inIterator		the iterator
	@param		inEventType		the new (or existing) type of the event you are changing
	@param		inEventData		the new event data. The size and type of this event data must match the inEventType
*/
extern OSStatus
MusicEventIteratorSetEventInfo(		MusicEventIterator 		inIterator,
									MusicEventType			inEventType,
									const void *			inEventData)		API_AVAILABLE(macos(10.2), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicEventIteratorSetEventTime
	@abstract	Set a new time for an event
	@discussion The iterator will still be pointing to the same event, but as the event will have moved, 
				it may or may not have a next or previous event now (depending of course on the time
				you moved it too).
				
	@param		inIterator		the iterator
	@param		inTimeStamp		the new time stamp of the event
*/
extern OSStatus
MusicEventIteratorSetEventTime(		MusicEventIterator 		inIterator,
									MusicTimeStamp			inTimeStamp)		API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicEventIteratorDeleteEvent
	@abstract	Deletes the event pointed to by the iterator
	@discussion The iterator will reference the next event after the event has been deleted.
				
	@param		inIterator		the iterator
*/
extern OSStatus
MusicEventIteratorDeleteEvent(		MusicEventIterator	 	inIterator)			API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicEventIteratorHasPreviousEvent
	@abstract	Does the track have an event previous to the event the iterator is pointing to?
	@discussion To use the iterator going backwards through a track:
					iter = New Iterator (points at first event)
					MusicEventIteratorSeek (iter, kMusicTimeStamp_EndOfTrack) // will point it past the last event
					bool hasPreviousEvent;
					MusicEventIteratorHasPreviousEvent (iter, &hasPreviousEvent)
					while (hasPreviousEvent) {
						MusicEventIteratorPreviousEvent (iter)
						// 	do work... MusicEventIteratorGetEventInfo (iter, ...
						
						MusicEventIteratorHasPreviousEvent (iter, &hasPreviousEvent);
					}				
	@param		inIterator		the iterator
	@param		outHasPrevEvent	true if there is a previous event, false if not
*/
extern OSStatus
MusicEventIteratorHasPreviousEvent(	MusicEventIterator 	inIterator,
									Boolean	*			outHasPrevEvent)		API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicEventIteratorHasNextEvent
	@abstract	Does the track have an event past the event the iterator is pointing too?
	@discussion To use the iterator going forwards through a track:
					iter = New Iterator (points at first event)
					bool hasCurrentEvent;
					MusicEventIteratorHasCurrentEvent(iter, &hasCurrentEvent);
					while (hasCurrentEvent) {
						// do work... MusicEventIteratorGetEventInfo (iter, ...
						
						MusicEventIteratorNextEvent (iter)
						MusicEventIteratorHasCurrentEvent(iter, &hasCurrentEvent);
					}
				
	@param		inIterator		the iterator
	@param		outHasNextEvent	true if there is a next event, false if not
*/
extern OSStatus
MusicEventIteratorHasNextEvent(		MusicEventIterator	inIterator,
									Boolean	*			outHasNextEvent)		API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicEventIteratorHasCurrentEvent
	@abstract	Is there an event at the iterator's current position?
	@param		inIterator		the iterator
	@param		outHasCurEvent	true if there is an event, false if not
*/
extern OSStatus
MusicEventIteratorHasCurrentEvent(	MusicEventIterator	inIterator,
									Boolean	*			outHasCurEvent)			API_AVAILABLE(macos(10.2), ios(5.0), watchos(2.0), tvos(9.0));



//=====================================================================================================================
#pragma mark -

#pragma mark -- Deprecated
// standard MIDI files (SMF, and RMF)

// MusicSequenceLoadSMF() also intelligently parses an RMID file to extract SMF part
#if !TARGET_RT_64_BIT
extern OSStatus
MusicSequenceLoadSMFData(	MusicSequence	inSequence,
							CFDataRef		inData)					API_DEPRECATED("no longer supported", macos(10.2, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
#endif // !TARGET_RT_64_BIT


// passing a value of zero for the flags makes this call equivalent to MusicSequenceLoadSMFData
// a kAudio_ParamError is returned if the sequence has ANY data in it and the flags value is != 0
// This will create a sequence with the first tracks containing MIDI Channel data
// IF the MIDI file had Meta events or SysEx data, then the last track in the sequence
// will contain that data.
extern OSStatus
MusicSequenceLoadSMFWithFlags(		MusicSequence			inSequence,
									const struct FSRef *			inFileRef,
									MusicSequenceLoadFlags	inFlags)	API_DEPRECATED("no longer supported", macos(10.3, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);

extern OSStatus
MusicSequenceLoadSMFDataWithFlags(	MusicSequence	inSequence,
									CFDataRef				inData,
									MusicSequenceLoadFlags	inFlags)	API_DEPRECATED("no longer supported", macos(10.3, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
// inFlags must be zero
extern OSStatus
MusicSequenceSaveMIDIFile(	MusicSequence	inSequence,
							const struct FSRef *inParentDirectory,
							CFStringRef		inFileName,
							UInt16			inResolution,
							UInt32			inFlags)				API_DEPRECATED("no longer supported", macos(10.4, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);

extern OSStatus
MusicSequenceSaveSMFData(	MusicSequence	inSequence,
							CFDataRef __nullable * __nonnull outData,
							UInt16			inResolution)			API_DEPRECATED("no longer supported", macos(10.2, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);

extern OSStatus
NewMusicTrackFrom(		MusicTrack			inSourceTrack,
						MusicTimeStamp		inSourceStartTime,
						MusicTimeStamp		inSourceEndTime,
						MusicTrack __nullable * __nonnull outNewTrack)	API_DEPRECATED("no longer supported", macos(10.0, 10.6)) API_UNAVAILABLE(ios, watchos, tvos);

#if !TARGET_OS_IPHONE
enum {
	kMusicEventType_ExtendedControl			= 2
};

typedef struct ExtendedControlEvent
{
	MusicDeviceGroupID			groupID;
	AudioUnitParameterID		controlID;
	AudioUnitParameterValue		value;
} ExtendedControlEvent;

extern OSStatus
MusicTrackNewExtendedControlEvent(	MusicTrack 					inTrack,
									MusicTimeStamp				inTimeStamp,
									const ExtendedControlEvent	*inInfo)		
																	API_DEPRECATED("no longer supported", macos(10.0, 10.7)) API_UNAVAILABLE(ios, watchos, tvos);
#endif

#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#pragma clang diagnostic pop

#endif // AudioToolbox_MusicPlayer_h
// ==========  AudioToolbox.framework/Headers/AudioQueue.h
/*!
	@file		AudioQueue.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2006-2015 by Apple, Inc., all rights reserved.
    @abstract   API's to record and play audio buffers.

    @discussion
    
	Audio queues are software objects you use for recording or playing audio in Mac OS X. Audio
	queues perform the following tasks:

		- Connect to audio hardware
		- Manage audio data buffers
		- Employ codecs, as necessary, for compressed audio formats
		- Mediate playback or recording

	Audio queues can record and play audio in linear PCM, in compressed formats (such as Apple
	Lossless, AAC, and MP3), and in other formats for which users have installed codecs. The API set
	includes high-level support for the use of hardware recording and playback devices, and lets you
	use sophisticated codecs without knowledge of how they work.

	Additional advanced features support scheduled playback and synchronization of multiple audio
	queues and synchronization of audio with video.
*/

#ifndef AudioToolbox_AudioQueue_h
#define AudioToolbox_AudioQueue_h

#include <Availability.h>
#include <CoreAudioTypes/CoreAudioTypes.h>
#include <CoreFoundation/CoreFoundation.h>

#if defined(__BLOCKS__)
    #include <dispatch/dispatch.h>
#endif

CF_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif


#pragma mark -
#pragma mark Constants


#pragma mark -
#pragma mark Types
//==================================================================================================
//  TYPES
//==================================================================================================

/*!
    @typedef    AudioQueuePropertyID
    @abstract   A value that uniquely identifies an audio queue property.
*/
typedef UInt32      AudioQueuePropertyID;

/*!
    @typedef    AudioQueueParameterID
    @abstract   A value that uniquely identifies an audio queue parameter.
*/
typedef UInt32      AudioQueueParameterID;

/*!
    @typedef    AudioQueueParameterID
    @abstract   A value for an audio queue parameter.
*/
typedef Float32     AudioQueueParameterValue;

/*!
    @typedef    AudioQueueRef
    @abstract   Defines an opaque data type that represents an audio queue.
*/
typedef struct OpaqueAudioQueue *   AudioQueueRef;

/*!
    @typedef    AudioQueueTimelineRef
    @abstract   Defines an opaque data type that represents an audio queue timeline.
    @discussion
        You can use this object to observe any overloads in the audio device associated with the
        audio queue. A timeline object receives notifications of discontinuities in the audio
        hardware's sample timeline--for instance, a period of silence when sound was expected.
        Causes of discontinuities include changes in the device state or processing overloads.
        See Technical Q & A: QA 1467 for a discussion of Core Audio overload warnings. These
        warnings indicate you are taking too long to process audio data and the system has cut
        you off. You query a timeline object by passing it as a parameter to
        AudioQueueGetCurrentTime, which means a discontinuity has occurred.
*/
typedef struct OpaqueAudioQueueTimeline *   AudioQueueTimelineRef;


//==================================================================================================
//  CONSTANTS
//==================================================================================================
/*!
    @enum Result Codes
    @abstract   The OSStatus result codes returned by Audio Queue functions.

    @constant   kAudioQueueErr_InvalidBuffer        The specified buffer does not belong to the
                                                    audio queue.
    @constant   kAudioQueueErr_BufferEmpty          The buffer is empty (that is, the
                                                    mAudioDataByteSize field = 0).
    @constant   kAudioQueueErr_DisposalPending      The function cannot act on the audio queue
                                                    because it is being asynchronously disposed of.
    @constant   kAudioQueueErr_InvalidProperty      The specified property ID is invalid.
    @constant   kAudioQueueErr_InvalidPropertySize  The size of the specified property is invalid.
    @constant   kAudioQueueErr_InvalidParameter     The specified parameter ID is invalid.
    @constant   kAudioQueueErr_CannotStart          The audio queue has encountered a problem and
                                                    cannot start.
    @constant   kAudioQueueErr_InvalidDevice        The device assigned to the queue could not
                                                    be located, or is not properly configured.
    @constant   kAudioQueueErr_BufferInQueue        The buffer cannot be disposed of when it is
                                                    enqueued.
    @constant   kAudioQueueErr_InvalidRunState      The queue is running but the function can
                                                    only operate on the queue when it is stopped,
                                                    or vice versa.
    @constant   kAudioQueueErr_InvalidQueueType     The queue is an input queue but the function can
                                                    only operate on an output queue, or vice versa.
    @constant   kAudioQueueErr_Permissions          You do not have the required permissions to call 
                                                    the function
    @constant   kAudioQueueErr_InvalidPropertyValue The specified property value is invalid.
    @constant   kAudioQueueErr_PrimeTimedOut        During Prime, the queue's AudioConverter failed to
                                                    convert the requested number of sample frames.
    @constant   kAudioQueueErr_CodecNotFound        The required audio codec was not found.
    @constant   kAudioQueueErr_InvalidCodecAccess   Access to the required codec is not permitted
                                                    (possibly due to incompatible AudioSession
                                                    settings on iPhoneOS).
    @constant   kAudioQueueErr_QueueInvalidated     On iPhoneOS, the audio server has exited, causing
                                                    this audio queue to have become invalid.
    @constant   kAudioQueueErr_TooManyTaps          There can only be one processing tap per
                                                    audio queue.
    @constant   kAudioQueueErr_InvalidTapContext    GetTapSourceAudio can only be called from the
                                                    tap's callback.
    @constant   kAudioQueueErr_InvalidTapType       GetTapQueueTime can only be called on an output queue's
                                                    tap.
    @constant   kAudioQueueErr_RecordUnderrun       During recording, data was lost because there
                                                    was no enqueued buffer into which to store it.
    @constant   kAudioQueueErr_BufferEnqueuedTwice  A buffer was enqueued twice on an input queue
                                                    (before being returned as a result of being filled
                                                    or from Reset).
    @constant   kAudioQueueErr_CannotStartYet       Starting the audio queue failed because an internal
                                                    reconfiguration (typically initiated by a hardware
                                                    stream format or sample rate change) was in progress.
                                                    Sleeping briefly and retrying is recommended.
    @constant   kAudioQueueErr_EnqueueDuringReset   During Reset, Stop, or Dispose, it is not
                                                    permitted to enqueue buffers.
    @constant   kAudioQueueErr_InvalidOfflineMode   The operation requires the queue to be in
                                                    offline mode but it isn't, or vice versa.
                                                    (Offline mode is entered and exited via
                                                    AudioQueueSetOfflineRenderFormat).
*/
CF_ENUM(OSStatus) {
    kAudioQueueErr_InvalidBuffer        = -66687,
    kAudioQueueErr_BufferEmpty          = -66686,
    kAudioQueueErr_DisposalPending      = -66685,
    kAudioQueueErr_InvalidProperty      = -66684,
    kAudioQueueErr_InvalidPropertySize  = -66683,
    kAudioQueueErr_InvalidParameter     = -66682,
    kAudioQueueErr_CannotStart          = -66681,
    kAudioQueueErr_InvalidDevice        = -66680,
    kAudioQueueErr_BufferInQueue        = -66679,
    kAudioQueueErr_InvalidRunState      = -66678,
    kAudioQueueErr_InvalidQueueType     = -66677,
    kAudioQueueErr_Permissions          = -66676,
    kAudioQueueErr_InvalidPropertyValue = -66675,
    kAudioQueueErr_PrimeTimedOut        = -66674,
    kAudioQueueErr_CodecNotFound        = -66673,
    kAudioQueueErr_InvalidCodecAccess   = -66672,
    kAudioQueueErr_QueueInvalidated     = -66671,
    kAudioQueueErr_TooManyTaps          = -66670,
    kAudioQueueErr_InvalidTapContext    = -66669,
    kAudioQueueErr_RecordUnderrun       = -66668,
    kAudioQueueErr_InvalidTapType       = -66667,
    kAudioQueueErr_BufferEnqueuedTwice  = -66666,
    kAudioQueueErr_CannotStartYet       = -66665,
    kAudioQueueErr_EnqueueDuringReset   = -66632,
    kAudioQueueErr_InvalidOfflineMode   = -66626,
};


/*!
    @enum Audio Queue Property IDs
    @abstract   Constants that identify properties for audio queues.
    @discussion
    @constant   kAudioQueueProperty_IsRunning
        A read-only property whose value is a UInt32 that indicates whether or not the queue is
        running. A notification is sent when the audio device starts or stops, which is not
        necessarily when the start or stop function is called.
    @constant   kAudioQueueDeviceProperty_SampleRate
        A read-only property whose value is a Float64 that indicates the sampling rate of the
        associated audio device.
    @constant   kAudioQueueDeviceProperty_NumberChannels
        A read-only property whose value is a UInt32 that indicates the number of channels in
        the associated audio device.
    @constant   kAudioQueueProperty_CurrentDevice
        A read/write property whose value is a CFStringRef that contains the unique identifier
        (UID) of the associated audio device.
		If the audio queue is tracking the default system device and the device changes, it will
		generate a property changed notification for this property. You can then query the HAL 
		for info on the new default system device.
    @constant   kAudioQueueProperty_MagicCookie
        A read/write property whose value is an audio format magic cookie. If the audio format
        requires a magic cookie, you must set this property before enqueuing any buffers.
    @constant   kAudioQueueProperty_MaximumOutputPacketSize
        A read-only UInt32 that indicates the size in bytes of the largest single packet of
        data in the output format. This is mostly useful for recording/encoding variable bit rate
        compressed data.
    @constant   kAudioQueueProperty_StreamDescription
        A read-only AudioStreamBasicDescription that indicates the queue's recording format.
        This is useful when recording, where you may specify a sample rate of 0 during
        construction, 
    @constant   kAudioQueueProperty_ChannelLayout
        A read/write property whose value is an audio channel layout structure that describes
        the audio queue's channel layout. The number of channels must match the format of the
        queue. If more than two channels (for instance, a five-channel surround sound) exist in
        the queue, there may be a need to specify a channel layout. This layout indicates the
        specific order in which the channels do appear, such as left, then center, then right.
    @constant   kAudioQueueProperty_EnableLevelMetering
        A read-write property whose value is a UInt32 that indicates whether metering of
        audio levels is enabled for the audio queue. (0=off, 1=on).
    @constant   kAudioQueueProperty_CurrentLevelMeter
        A read-only property whose value is an array of AudioQueueLevelMeter structures, one
        array element per audio channel. The values in the AudioQueueLevelMeters are in the
        range 0-1.
    @constant   kAudioQueueProperty_CurrentLevelMeterDB
        A read-only property whose value is an array of AudioQueueLevelMeter structures, one
        array element per audio channel. The values in the AudioQueueLevelMeters are in
        decibels.
    @constant   kAudioQueueProperty_DecodeBufferSizeFrames
        A read/write property whose value is a UInt32 that is the size of the buffer into which
        an output audio queue decodes buffers. A large buffer provides more reliability and
        better long-term performance at the expense of memory and decreased responsiveness
        in some situations.
    @constant   kAudioQueueProperty_ConverterError
        A read-only property whose value is a UInt32 indicating the most recent error (if any)
        encountered by the queue's internal encoding/decoding process.
    @constant   kAudioQueueProperty_EnableTimePitch
        A read/write property whose value is a UInt32 describing whether there is a time/pitch unit
        inserted into the queue's audio signal chain. This property may only be set while
        the queue is stopped.
    @constant   kAudioQueueProperty_TimePitchAlgorithm
        A read/write property whose value is a UInt32 describing the time/pitch algorithm in use.
        This property is only valid while a time/pitch has been inserted, and may only be changed
        when the queue is not running.
    @constant   kAudioQueueProperty_TimePitchBypass
        A read/write property whose value is a UInt32 describing whether the time/pitch unit
        has been bypassed (1=bypassed, 0=not bypassed).
*/
CF_ENUM(AudioQueuePropertyID) {
    kAudioQueueProperty_IsRunning               = 'aqrn',       // value is UInt32

    kAudioQueueDeviceProperty_SampleRate        = 'aqsr',       // value is Float64
    kAudioQueueDeviceProperty_NumberChannels    = 'aqdc',       // value is UInt32
    kAudioQueueProperty_CurrentDevice           = 'aqcd',       // value is CFStringRef
    
    kAudioQueueProperty_MagicCookie             = 'aqmc',       // value is void*
    kAudioQueueProperty_MaximumOutputPacketSize = 'xops',       // value is UInt32
    kAudioQueueProperty_StreamDescription       = 'aqft',       // value is AudioStreamBasicDescription
       
    kAudioQueueProperty_ChannelLayout           = 'aqcl',       // value is AudioChannelLayout
    kAudioQueueProperty_EnableLevelMetering     = 'aqme',       // value is UInt32
    kAudioQueueProperty_CurrentLevelMeter       = 'aqmv',       // value is array of AudioQueueLevelMeterState, 1 per channel
    kAudioQueueProperty_CurrentLevelMeterDB     = 'aqmd',       // value is array of AudioQueueLevelMeterState, 1 per channel

    kAudioQueueProperty_DecodeBufferSizeFrames  = 'dcbf',       // value is UInt32
    kAudioQueueProperty_ConverterError          = 'qcve',       // value is UInt32

    kAudioQueueProperty_EnableTimePitch         = 'q_tp',       // value is UInt32, 0/1
    kAudioQueueProperty_TimePitchAlgorithm      = 'qtpa',       // value is UInt32. See values below.
    kAudioQueueProperty_TimePitchBypass         = 'qtpb',       // value is UInt32, 1=bypassed
};

/*!
    @enum       Time/Pitch algorithms
    @abstract   Constants that identify values of kAudioQueueProperty_TimePitchAlgorithm

    @constant kAudioQueueTimePitchAlgorithm_Spectral
        Highest quality, most computationally expensive. Suitable for music.
        Default algorithm on OS X.
    @constant kAudioQueueTimePitchAlgorithm_TimeDomain
        Modest quality, less expensive. Suitable for voice.
    @constant kAudioQueueTimePitchAlgorithm_Varispeed
        High quality, but pitch varies with rate.
*/
CF_ENUM(UInt32) {
    kAudioQueueTimePitchAlgorithm_Spectral      = 'spec',
    kAudioQueueTimePitchAlgorithm_TimeDomain    = 'tido',
    kAudioQueueTimePitchAlgorithm_Varispeed     = 'vspd'
};

#if TARGET_OS_IPHONE && !TARGET_OS_UIKITFORMAC
/*!	@enum		Time/Pitch algorithms (iOS only)
    @constant kAudioQueueTimePitchAlgorithm_LowQualityZeroLatency
        Low quality, very inexpensive. Suitable for brief fast-forward/rewind effects,
        low quality voice. Default algorithm on iOS.
*/
CF_ENUM(UInt32) {
    kAudioQueueTimePitchAlgorithm_LowQualityZeroLatency API_DEPRECATED("Low Quality Zero Latency algorithm is now Deprecated. Please choose from other available options", ios(2.0, 13.0), watchos(2.0, 6.0), tvos(9.0, 13.0)) API_UNAVAILABLE(macos)     = 'lqzl',
};
#endif

#if TARGET_OS_IPHONE
/*!
    @enum Audio Queue Property IDs
    @abstract Audio Queue Property IDs (iOS 3.0 or greater only)
    
    @constant   kAudioQueueProperty_HardwareCodecPolicy
        A UInt32 describing how the audio queue is to choose between a hardware or
        software version of the codec required for its audio format. Its value is one of
        the AudioQueueHardwareCodecPolicy constants below.
        
        If the chosen codec is not available, or if a hardware codec is chosen and the 
        AudioSession category does not permit use of hardware codecs, attempts to Prime or Start
        the queue will fail.

        Use kAudioFormatProperty_Encoders or kAudioFormatProperty_Decoders to determine
        whether the codec you are interested in using is available in hardware form,
        software, or both.
        
        Changing this property is not permitted while the queue is primed or running. Changing
        this property at other times may cause any properties set on the codec to be lost.
 
        DEPRECATED: Hardware codecs are no longer supported.
*/
CF_ENUM(AudioQueuePropertyID) {
    kAudioQueueProperty_HardwareCodecPolicy             = 'aqcp'        // value is UInt32
};

/*!
    @enum       AudioQueueHardwareCodecPolicy constants
    @abstract   Values of kAudioQueueProperty_HardwareCodecPolicy (iOS 3.0 or greater only)
    
    @constant kAudioQueueHardwareCodecPolicy_Default
        If the required codec is available in both hardware and software forms, the audio queue
        will choose a hardware codec if its AudioSession category permits, software otherwise.
        If the required codec is only available in one form, that codec is chosen.
    @constant kAudioQueueHardwareCodecPolicy_UseSoftwareOnly
        The audio queue will choose a software codec if one is available.
    @constant kAudioQueueHardwareCodecPolicy_UseHardwareOnly
        The audio queue will choose a hardware codec if one is available and its use permitted
        by the AudioSession category.
    @constant kAudioQueueHardwareCodecPolicy_PreferSoftware
        The audio queue will choose a software codec if one is available; if not, it will choose a
        hardware codec if one is available and its use permitted by the AudioSession category.
    @constant kAudioQueueHardwareCodecPolicy_PreferHardware
        The audio queue will choose a hardware codec if one is available and its use permitted
        by the AudioSession category; otherwise, it will choose a software codec if one is available.

	DEPRECATED: Hardware codecs are no longer supported.
*/
CF_ENUM(UInt32) {
    kAudioQueueHardwareCodecPolicy_Default              = 0,
    kAudioQueueHardwareCodecPolicy_UseSoftwareOnly      = 1,
    kAudioQueueHardwareCodecPolicy_UseHardwareOnly      = 2,
    kAudioQueueHardwareCodecPolicy_PreferSoftware       = 3,
    kAudioQueueHardwareCodecPolicy_PreferHardware       = 4
};
#endif // TARGET_OS_IPHONE

/*!
    @enum Audio Queue Property IDs
    @abstract Audio Queue Property IDs (iOS 6.0 or greater only)

    @constant   kAudioQueueProperty_ChannelAssignments
        A write-only property whose value is an array of AudioQueueChannelAssignment. There must be
        one array element for each channel of the queue's format as specified in the
        AudioStreamBasicDescription passed to AudioQueueNewOutput or AudioQueueNewInput.
        (New in iOS 6.0).
*/
CF_ENUM(AudioQueuePropertyID) {
    kAudioQueueProperty_ChannelAssignments      = 'aqca'
} API_AVAILABLE(ios(9.0), watchos(2.0), tvos(9.0), macos(10.15));

/*!
    @enum       AudioQueueParameterID
    @abstract   Constants that identify the parameters for audio queues.
    @discussion
        You can set a parameter in one of two ways:
        
        <ul>
        <li>    Assign a parameter value to an audio queue to take effect immediately using
                AudioQueueSetParameter.</li>
        <li>    Schedule a parameter to take effect when a buffer is enqueued. You supply the
                parameter when you queue a buffer, and the new value of the parameter is applied
                when that buffer is rendered.
        </ul>
        
        AudioQueueGetParameter always returns the current value of the parameter

    @constant   kAudioQueueParam_Volume
        A value from 0.0 to 1.0 indicating the linearly scaled gain for the queue. A value of
        1.0 (the default) indicates unity gain. A value of 0.0 indicates zero gain, or silence.
    @constant   kAudioQueueParam_PlayRate
        A value from 0.5 to 2.0 indicating the rate at which the queue is to play. A value of
        1.0 (the default) indicates that the queue should play at its normal rate. Only
        applicable when the time/pitch processor has been enabled and on Mac OS X 10.6 and higher.
    @constant   kAudioQueueParam_Pitch
        A value from -2400 to 2400 indicating the number of cents to pitch-shift the queue's
        playback. (1200 cents is one octave.) Only applicable when the time/pitch processor has 
        been enabled with the spectral algorithm, and on Mac OS X 10.6 and higher.
    @constant   kAudioQueueParam_VolumeRampTime
        A value indicating the number of seconds over which subsequent volume changes will be
        ramped. For example, to fade out from full unity gain to silence over the course of 1
        second, set kAudioQueueParam_VolumeRampTime to 1 then kAudioQueueParam_Volume to 0.
    @constant   kAudioQueueParam_Pan
        A value from -1 to 1 indicating the pan position of a mono source (-1 = hard left, 0 =
        center, 1 = hard right). For a stereo source this parameter affects left/right balance.
        For multi-channel sources, this parameter has no effect.
*/
CF_ENUM(AudioQueueParameterID)
{
    kAudioQueueParam_Volume         = 1,
    kAudioQueueParam_PlayRate       = 2,
    kAudioQueueParam_Pitch          = 3,
    kAudioQueueParam_VolumeRampTime = 4,
    kAudioQueueParam_Pan            = 13
};

/*!
    @enum       AudioQueueProcessingTap flags
    @abstract   Flags used in conjunction with processing taps

    @discussion
        In the flags passed to AudioQueueProcessingTapNew, either the PreEffects
        or PostEffects flag must be set, but not both. 

    @constant   kAudioQueueProcessingTap_PreEffects
        Signifies that the processing tap is inserted before any effects.
        Passed to AudioQueueProcessingTapNew and to the callback.
    @constant   kAudioQueueProcessingTap_PostEffects
        Signifies that the processing tap is inserted after any effects.
        Passed to AudioQueueProcessingTapNew and to the callback.
    @constant   kAudioQueueProcessingTap_Siphon
        Signifies that the processing tap is a siphon; it does not call
        GetSourceAudio. The callback instead receives the source audio
        and may not modify it. Passed to AudioQueueProcessingTapNew and to the callback.
    @constant   kAudioQueueProcessingTap_StartOfStream
        Signifies that the source audio is the beginning of a continuous stream,
        i.e. following the beginning or resumption of playback or recording.
        Returned from GetSourceAudio.
    @constant   kAudioQueueProcessingTap_EndOfStream
        Signifies that the source audio is past the end of stream. This happens when
        the audio queue is being stopped asynchronously and has finished playing
        all of its data. Returned from GetSourceAudio and should be propagated
        on return from the callback.
*/
typedef CF_OPTIONS(UInt32, AudioQueueProcessingTapFlags) {
    //  these are flags that are passed to both the constructor and the callback
    kAudioQueueProcessingTap_PreEffects         = (1 << 0),     // 0x01
    kAudioQueueProcessingTap_PostEffects        = (1 << 1),     // 0x02
    kAudioQueueProcessingTap_Siphon             = (1 << 2),     // 0x04

    //  these are flags that are passed to the callback and from GetSourceAudio
    kAudioQueueProcessingTap_StartOfStream      = (1 << 8),     // 0x100
    kAudioQueueProcessingTap_EndOfStream        = (1 << 9),     // 0x200
};

#pragma mark -
#pragma mark Structs
//==================================================================================================
//  STRUCTS
//==================================================================================================

/*!
    @struct     AudioQueueBuffer
    @abstract   Defines a buffer of audio data to be managed by an audio queue.
    @discussion 
        Each audio queue has an associated set of audio queue buffers. You can request that a
        queue allocate buffers using the AudioQueueAllocateBuffer function and dispose of them
        using the AudioQueueFreeBuffer function.
        
        You may also use AudioQueueAllocateBufferWithPacketDescriptions to allocate buffers
        with space for AudioPacketDescriptions, as used in VBR formats. The 
        mPacketDescriptionCapacity, mmPacketDescriptions, and mPacketDescriptionCount
        fields may only be used with buffers allocated with this function.
        
    @var        mAudioDataBytesCapacity
        The size of the buffer, in bytes. This size is set when the buffer is allocated and
        cannot be changed.
    @var        mAudioData
       A pointer to the audio data in the buffer. Although you can write data to this buffer,
       you cannot make it point to another address.
    @var        mAudioDataByteSize
        The number of bytes of valid audio data in the buffer. You set this value when providing
        data for playback; the audio queue sets this value when recording data from a recording
        queue.
    @var        mUserData
        A value you may specify to identify the buffer when it is passed back in recording or
        playback callback functions.
    @var        mPacketDescriptionCapacity
        The maximum number of packet descriptions that can be stored in mPacketDescriptions.
    @var        mPacketDescriptions
        An array of AudioStreamPacketDescriptions associated with the buffer.
    @var        mPacketDescriptionCount
        The number of valid packet descriptions in the buffer. You set this value when providing
        buffers for playback; the audio queue sets this value when returning buffers from
        a recording queue.
*/

typedef struct AudioQueueBuffer {
    const UInt32                    mAudioDataBytesCapacity;
    void * const                    mAudioData;
    UInt32                          mAudioDataByteSize;
    void * __nullable               mUserData;

    const UInt32                    mPacketDescriptionCapacity;
    AudioStreamPacketDescription * const __nullable mPacketDescriptions;
    UInt32                          mPacketDescriptionCount;
#ifdef __cplusplus
    AudioQueueBuffer() : mAudioDataBytesCapacity(0), mAudioData(0), mPacketDescriptionCapacity(0), mPacketDescriptions(0) { }
#endif
} AudioQueueBuffer;

/*!
    @typedef    AudioQueueBufferRef
    @abstract   An pointer to an AudioQueueBuffer.
*/
typedef AudioQueueBuffer *AudioQueueBufferRef;

/*!
    @struct     AudioQueueParameterEvent
    @abstract   Specifies a value for an audio queue parameter.
    @discussion
        Two ways are available to supply an audio queue with parameters:
        
        <ul>
        <li>    Provide one or more parameters by calling the
                AudioQueueEnqueueBufferWithParameters function. In this case, the parameters are
                applied to the specified buffer when it is played.</li>
        <li>    Assign a parameter value immediately to an audio queue by calling the
                AudioQueueSetParameter function.</li>
        </ul>
        
        Note that the AudioQueueGetParameter function always returns the actual value of the
        parameter.

        In Mac OS X v10.5, audio queues have one parameter available: kAudioQueueParam_Volume,
        which controls the queue's playback volume.
        
    @var        mID
        The parameter.
    @var        mValue
        The value of the specified parameter.
*/
struct AudioQueueParameterEvent {
    AudioQueueParameterID           mID;
    AudioQueueParameterValue        mValue;
};
typedef struct AudioQueueParameterEvent AudioQueueParameterEvent;


/*!
    @struct     AudioQueueLevelMeterState
    @abstract   Specifies the current level metering information for one channel of an audio queue.
    @var        mAveragePower
        The audio channel's average RMS power.
    @var        mPeakPower
        The audio channel's peak RMS power
*/
typedef struct AudioQueueLevelMeterState {
    Float32     mAveragePower;
    Float32     mPeakPower;
} AudioQueueLevelMeterState;

/*!
    @typedef    AudioQueueProcessingTapRef
    @abstract   An object for intercepting and processing audio within an audio queue.
*/
typedef struct OpaqueAudioQueueProcessingTap *   AudioQueueProcessingTapRef;

/*!
    @struct     AudioQueueChannelAssignment
    @abstract   Specifies an audio device channel to which the queue will play or from which
                it will record.
    @var        mDeviceUID
        On iOS, this is a port UID obtained from AVAudioSession. On OS X, this is the UID
        obtained from an AudioDeviceID.
    @var        mChannelNumber
        The 1-based index of the channel.
*/
typedef struct AudioQueueChannelAssignment {
    CFStringRef     mDeviceUID;
    UInt32          mChannelNumber;
} AudioQueueChannelAssignment;

#pragma mark -
#pragma mark Callbacks
//==================================================================================================
//  CALLBACKS
//==================================================================================================

#if defined(__BLOCKS__)
/*!
    @typedef    AudioQueueOutputCallbackBlock
    @abstract   Defines a pointer to a block that is called when a playback audio
                queue has finished taking data from a buffer.

    @discussion
        A playback buffer callback is invoked when the audio queue has finished with the data to
        be played and the buffer is available to your application for reuse. Your application
        might want to immediately refill and re-enqueue the completed buffer at this time.
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inBuffer
        The audio queue buffer made available by the audio queue.
*/
typedef void (^AudioQueueOutputCallbackBlock)(
                                    AudioQueueRef                   inAQ,
                                    AudioQueueBufferRef             inBuffer);

/*!
    @typedef    AudioQueueInputCallbackBlock
    @abstract   Defines a pointer to a block that is called when a recording audio
                queue has finished filling a buffer.
    @discussion
        You specify a recording buffer callback when calling AudioQueueNewInput. Your callback
        is invoked each time the recording audio queue has filled a buffer with input data.
        Typically, your callback should write the audio queue buffer's data to a file or other
        buffer, and then re-queue the audio queue buffer to receive more data.
        
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inBuffer
        An audio queue buffer, newly filled by the audio queue, containing the new audio data
        your callback needs to write.
    @param      inStartTime
        A pointer to an audio time stamp structure corresponding to the first sample contained
        in the buffer. This contains the sample time of the first sample in the buffer.
    @param      inNumberPacketDescriptions
        The number of audio packets contained in the data provided to the callback
    @param      inPacketDescs
        For compressed formats which require packet descriptions, the packet descriptions
        produced by the encoder for the incoming buffer.
*/
typedef void (^AudioQueueInputCallbackBlock)(
                                    AudioQueueRef                   inAQ,
                                    AudioQueueBufferRef             inBuffer,
                                    const AudioTimeStamp *          inStartTime,
                                    UInt32                          inNumberPacketDescriptions,
                                    const AudioStreamPacketDescription * __nullable inPacketDescs);
#endif // defined(__BLOCKS__)

/*!
    @typedef    AudioQueueOutputCallback
    @abstract   Defines a pointer to a callback function that is called when a playback audio
                queue has finished taking data from a buffer.

    @discussion
        A playback buffer callback is invoked when the audio queue has finished with the data to
        be played and the buffer is available to your application for reuse. Your application
        might want to immediately refill and re-enqueue the completed buffer at this time.
    @param      inUserData
        The value specified by the inUserData parameter of the AudioQueueNewOutput function.
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inBuffer
        The audio queue buffer made available by the audio queue.
*/
typedef void (*AudioQueueOutputCallback)(
                                    void * __nullable       inUserData,
                                    AudioQueueRef           inAQ,
                                    AudioQueueBufferRef     inBuffer);

/*!
    @typedef    AudioQueueInputCallback
    @abstract   Defines a pointer to a callback function that is called when a recording audio
                queue has finished filling a buffer.
    @discussion
        You specify a recording buffer callback when calling AudioQueueNewInput. Your callback
        is invoked each time the recording audio queue has filled a buffer with input data.
        Typically, your callback should write the audio queue buffer's data to a file or other
        buffer, and then re-queue the audio queue buffer to receive more data.
        
    @param      inUserData
        The value you've specified in the inUserData parameter of the AudioQueueNewInput
        function.
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inBuffer
        An audio queue buffer, newly filled by the audio queue, containing the new audio data
        your callback needs to write.
    @param      inStartTime
        A pointer to an audio time stamp structure corresponding to the first sample contained
        in the buffer. This contains the sample time of the first sample in the buffer.
    @param      inNumberPacketDescriptions
        The number of audio packets contained in the data provided to the callback
    @param      inPacketDescs
        For compressed formats which require packet descriptions, the packet descriptions
        produced by the encoder for the incoming buffer.
*/
typedef void (*AudioQueueInputCallback)(
                                    void * __nullable               inUserData,
                                    AudioQueueRef                   inAQ,
                                    AudioQueueBufferRef             inBuffer,
                                    const AudioTimeStamp *          inStartTime,
                                    UInt32                          inNumberPacketDescriptions,
                                    const AudioStreamPacketDescription * __nullable inPacketDescs);


/*!
    @typedef    AudioQueuePropertyListenerProc
    @abstract   Defines a pointer to a callback function that is called when a specified
                property changes value.
    @discussion
        You assign a property listener callback when calling AudioQueueAddPropertyListener.
        
    @param      inUserData
        A pointer to the data specified by the inUserData parameter of the
        AudioQueueAddPropertyListener function.
    @param      inAQ
        The audio queue that invoked the callback.
    @param      inID
        The ID of the property that invoked the callback.
*/
typedef void (*AudioQueuePropertyListenerProc)(  
                                    void * __nullable       inUserData,
                                    AudioQueueRef           inAQ,
                                    AudioQueuePropertyID    inID);

/*!
@typedef    AudioQueueProcessingTapCallback
@abstract   A function called when an audio queue has data to be processed by its tap

@discussion
    A processing callback is invoked when the audio queue has data that can be processed by a given
    tap.

    The audio queue will call the processing callback when it has sufficient data to provide for
    processing.

    In the case of a siphoning tap, the callback function can inspect the audio data in ioData, but
    should not otherwise modify it. The callback should not call
    AudioQueueProcessingTapGetSourceAudio.

    A non-siphoning callback should call AudioQueueProcessingTapGetSourceAudio to request from the
    queue as much source data as it needs in order to produce the requested number of output
    samples. When the callback requests source data it may receive less data than it requests.

    In the case of a tap on an audio output queue, the tap must emit the exact number of sample
    frames that the queue requests. In normal circumstances, the tap's requests for source data will
    be satisfied (as the client running the audio queue is also providing the queue with the audio
    source material). If there is insufficient source data available (this is indicated by the
    outNumberFrames from the GetSource call), then the processing tap should deal as best as it can;
    it can either return less data than was requested or insert silence, noise, etc. itself. If it
    returns less data than requested, the hosting audio queue will fill in the remainder with
    silence.

    In the case of a tap on an audio input queue, the tap may provide back less audio data than is
    being requested. Typically this will occur because the tap will ask for source data that is not
    available at this time (the audio input hasn't arrived yet), so the tap should cache the source
    data that it needs and return as many processed samples as it can. If the processing tap falls
    behind and is not providing data quickly enough silence will be generated in the data provided
    to the client (and there is no signal about this either).

    A processing tap executes in a semi-real-time context, so the general limitations for real-time
    processing apply. Avoid using API's which may block. In particular, it is not safe to call the
    audio queue on which the tap was installed, with the exceptions of
    AudioQueueProcessingTapGetSourceAudio and AudioQueueProcessingTapGetQueueTime.

    In normal operation the source data will be continuous from the last time the callback was
    called and the processed samples should be continuous from the previous samples returned. If
    there is any discontinuity between the last samples provided for processing the audio queue will
    set the bit for kAudioQueueProcessing_StartOfStream in the inFlags. After a discontinuity the
    first sample that the processing tap outputs should correspond to the first sample that was
    provided in the source samples (so a reset and then consequent process serves to re-anchor a
    relationship between the processing tap's source and processed samples). In this case the
    processing tap will typically discard any previous state (for instance, if a processing tap was
    adding a reverb to a signal, then the discontinuity flag would act the same as AudioUnitReset;
    any previous source information in the processing tap should be discarded).

    The caller is responsible for absorbing any processing delays. For example, if the processing is
    to be done by an audio unit that reports a processing latency, then the caller should remove
    those latency samples from the audio unit's rendering and not return them to the audio queue.

    The processing tap is able to operate on the provided source data in place (that is, it can do
    "in place processing") and return pointers to that buffer rather than its own. This works in a
    similar way as AudioUnit render operations.

    When an output audio queue is being stopped asynchronously, the processing tap will see the
    kAudioQueueProcessingTap_EndOfStream bit set on return from GetSourceAudio, and is responsible
    for propagating this bit from the callback when its processing has reached this point.

    A processing tap will NEVER see the same source data again, so, it should keep its own copy if
    it needs to keep it for further reference past the duration of this call. It also cannot assume
    that the pointers to the source data that it retrieves will remain valid AFTER the processing
    tap has executed.

    The processing tap should ensure that the data pointers it provides in outProcessedData remain
    valid until the tap is executed again.

    A processing tap is destroyed implicitly when its audio queue is disposed. It may also be
    removed explicitly, via AudioQueueProcessingTapDispose.

    @param      inClientData
                    the client data pointer passed to AudioQueueProcessingTapNew
    @param      inAQTap
                    The tap for this callback.
    @param      inNumberFrames
                    The requested number of sample frames to be rendered.
    @param      ioFlags
                    On entry, the flags passed at construction time are provided. On exit,
                    the start/end of stream flags should be set when appropriate.
    @param      ioTimeStamp
                    On an input audio queue, the timestamp must be returned from this function.
                    On an output audio queue, the callback is provided a continuous timestamp.
    @param      outNumberFrames
                    The number of frames of audio data provided in the processed data. Can be 0.
    @param      ioData
                    For non-siphoning taps, on entry, the buffer pointers are null and the lengths
                    are zero. On exit, they should contain the tap's output.
                    
                    Siphoning taps receive valid buffers which they must not alter.
*/
typedef void (*AudioQueueProcessingTapCallback)(
                                    void *                          inClientData,
                                    AudioQueueProcessingTapRef      inAQTap,
                                    UInt32                          inNumberFrames,
                                    AudioTimeStamp *                ioTimeStamp,
                                    AudioQueueProcessingTapFlags *  ioFlags,
                                    UInt32 *                        outNumberFrames,
                                    AudioBufferList *               ioData);

//==================================================================================================
//  FUNCTIONS
//==================================================================================================

#pragma mark -
#pragma mark Creating/destroying queues
//=============================================================================
//  Creating/destroying queues
//=============================================================================

/*!
    @function   AudioQueueNewOutput
    @abstract   Creates a new audio queue for playing audio data.
    @discussion
        To create an playback audio queue, you allocate buffers, then queue buffers (using
        AudioQueueEnqueueBuffer). The callback receives buffers and typically queues them again.
        To schedule a buffer for playback, providing parameter and start time information, call
        AudioQueueEnqueueBufferWithParameters.
       
    @param      inFormat
        A pointer to a structure describing the format of the audio data to be played. For
        linear PCM, only interleaved formats are supported. Compressed formats are supported.
    @param      inCallbackProc
        A pointer to a callback function to be called when the audio queue has finished playing
        a buffer.
    @param      inUserData
        A value or pointer to data that you specify to be passed to the callback function.
    @param      inCallbackRunLoop
        The event loop on which inCallbackProc is to be called. If you specify NULL, the
        callback is called on one of the audio queue's internal threads.
    @param      inCallbackRunLoopMode
        The run loop mode in which to call the callback. Typically, you pass
        kCFRunLoopCommonModes. (NULL also specifies kCFRunLoopCommonModes). Other
        possibilities are implementation specific. You can choose to create your own thread with
        your own run loops. For more information on run loops, see Run Loops or CFRunLoop
        Reference.
    @param      inFlags
        Reserved for future use. Pass 0.
    @param      outAQ
        On return, this variable contains a pointer to the newly created playback audio queue
        object.
    @result     An OSStatus result code.
*/
extern OSStatus             
AudioQueueNewOutput(                const AudioStreamBasicDescription *inFormat,
                                    AudioQueueOutputCallback        inCallbackProc,
                                    void * __nullable               inUserData,
                                    CFRunLoopRef __nullable         inCallbackRunLoop,
                                    CFStringRef __nullable          inCallbackRunLoopMode,
                                    UInt32                          inFlags,
                                    AudioQueueRef __nullable * __nonnull outAQ)          API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));


/*!
    @function   AudioQueueNewInput
    @abstract   Creates a new audio queue for recording audio data.
    @discussion
        Outline of how to use the queue for input:
        
        - create input queue
        - allocate buffers
        - enqueue buffers (AudioQueueEnqueueBuffer, not with parameters, no packet descriptions)
        - the callback receives buffers and re-enqueues them
        
    @param      inFormat
        A pointer to a structure describing the format of the audio data to be recorded. For
        linear PCM, only interleaved formats are supported. Compressed formats are supported.
    @param      inCallbackProc
        A pointer to a callback function to be called when the audio queue has finished filling
        a buffer.
    @param      inUserData
        A value or pointer to data that you specify to be passed to the callback function.
    @param      inCallbackRunLoop
        The event loop on which inCallbackProc is to be called. If you specify NULL, the
        callback is called on one of the audio queue's internal threads.
    @param      inCallbackRunLoopMode
        The run loop mode in which to call the callback. Typically, you pass
        kCFRunLoopCommonModes. (NULL also specifies kCFRunLoopCommonModes). Other
        possibilities are implementation specific. You can choose to create your own thread with
        your own run loops. For more information on run loops, see Run Loops or CFRunLoop
        Reference.
    @param      inFlags
        Reserved for future use. Pass 0.
    @param      outAQ
        On return, this variable contains a pointer to the newly created recording audio queue
        object.
    @result     An OSStatus result code.
*/
extern OSStatus             
AudioQueueNewInput(                 const AudioStreamBasicDescription *inFormat,
                                    AudioQueueInputCallback         inCallbackProc,
                                    void * __nullable               inUserData,
                                    CFRunLoopRef __nullable         inCallbackRunLoop,
                                    CFStringRef __nullable          inCallbackRunLoopMode,
                                    UInt32                          inFlags,
                                    AudioQueueRef __nullable * __nonnull outAQ)          API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

#if defined(__BLOCKS__)
/*!
    @function   AudioQueueNewOutputWithDispatchQueue
    @abstract   Creates a new audio queue for playing audio data.
    @discussion
        To create an playback audio queue, you allocate buffers, then queue buffers (using
        AudioQueueEnqueueBuffer). The callback receives buffers and typically queues them again.
        To schedule a buffer for playback, providing parameter and start time information, call
        AudioQueueEnqueueBufferWithParameters.
       
    @param      outAQ
        On return, this variable contains a pointer to the newly created playback audio queue
        object.
    @param      inFormat
        A pointer to a structure describing the format of the audio data to be played. For
        linear PCM, only interleaved formats are supported. Compressed formats are supported.
    @param      inFlags
        Reserved for future use. Pass 0.
    @param      inCallbackDispatchQueue
        The dispatch queue from which inCallbackBlock is to be called.
    @param      inCallbackBlock
        A pointer to a callback block to be called when the audio queue has finished playing
        a buffer.
    @result     An OSStatus result code.
*/
extern OSStatus             
AudioQueueNewOutputWithDispatchQueue(AudioQueueRef __nullable * __nonnull outAQ,
                                    const AudioStreamBasicDescription *inFormat,
                                    UInt32                          inFlags,
                                    dispatch_queue_t                inCallbackDispatchQueue,
                                    AudioQueueOutputCallbackBlock   inCallbackBlock)
										API_AVAILABLE(macos(10.6), ios(10.0), watchos(3.0), tvos(10.0));

/*!
    @function   AudioQueueNewInputWithDispatchQueue
    @abstract   Creates a new audio queue for recording audio data.
    @discussion
        Outline of how to use the queue for input:
        
        - create input queue
        - allocate buffers
        - enqueue buffers (AudioQueueEnqueueBuffer, not with parameters, no packet descriptions)
        - the callback receives buffers and re-enqueues them
        
    @param      outAQ
        On return, this variable contains a pointer to the newly created recording audio queue
        object.
    @param      inFormat
        A pointer to a structure describing the format of the audio data to be recorded. For
        linear PCM, only interleaved formats are supported. Compressed formats are supported.
    @param      inFlags
        Reserved for future use. Pass 0.
    @param      inCallbackDispatchQueue
        The dispatch queue from which inCallbackBlock is to be called.
    @param      inCallbackBlock
        A pointer to a callback block to be called when the audio queue has finished filling
        a buffer.
    @result     An OSStatus result code.
*/
extern OSStatus             
AudioQueueNewInputWithDispatchQueue(AudioQueueRef __nullable * __nonnull outAQ,
                                    const AudioStreamBasicDescription *inFormat,
                                    UInt32                          inFlags,
                                    dispatch_queue_t                inCallbackDispatchQueue,
                                    AudioQueueInputCallbackBlock    inCallbackBlock)
										API_AVAILABLE(macos(10.6), ios(10.0), watchos(3.0), tvos(10.0));
#endif // defined(__BLOCKS__)

/*!
    @function   AudioQueueDispose
    @abstract   Disposes an existing audio queue.
    @discussion
        Disposing of the audio queue also disposes of all its resources, including its buffers.
    @param      inAQ
        The audio queue you want to dispose of
    @param      inImmediate
        If you pass true, the audio queue is disposed of immediately (that is, synchronously).
        If you pass false, disposal does not take place until all enqueued buffers are
        processed. Whether you call AudioQueueDispose synchronously or asynchronously, you can
        no longer interact with the queue, and the queue no longer invokes any callbacks to your
        application after the function returns.
		
		Note that if AudioQueueDispose is called from a buffer completion callback or property
		listener, you may receive further callbacks afterwards.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueDispose(                  AudioQueueRef           inAQ, 
                                    Boolean                 inImmediate)            API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

#pragma mark -
#pragma mark Buffer Management
//=============================================================================
//  Buffer Management
//=============================================================================

/*!
    @function   AudioQueueAllocateBuffer
    @abstract   Asks an audio queue to allocate a buffer.
    @discussion
        Once allocated, the pointer to the buffer and the buffer's size are fixed and cannot be
        changed. The mAudioDataByteSize field in the audio queue buffer structure,
        AudioQueueBuffer, is initially set to 0.
        
    @param      inAQ
        The audio queue you want to allocate a buffer.
    @param      inBufferByteSize
        The desired size of the new buffer, in bytes. An appropriate buffer size depends on the
        processing you will perform on the data as well as on the audio data format.
    @param      outBuffer
        On return, points to the newly created audio buffer. The mAudioDataByteSize field in the
        audio queue buffer structure, AudioQueueBuffer, is initially set to 0.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueAllocateBuffer(           AudioQueueRef           inAQ,
                                    UInt32                  inBufferByteSize,
                                    AudioQueueBufferRef __nullable * __nonnull outBuffer)              API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueAllocateBufferWithPacketDescriptions
    @abstract   Asks an audio queue to allocate a buffer with space for packet descriptions.
    @discussion
        Once allocated, the pointer to the buffer and the buffer's size are fixed and cannot be
        changed. The mAudioDataByteSize field in the audio queue buffer structure,
        AudioQueueBuffer, is initially set to 0.
        
    @param      inAQ
        The audio queue you want to allocate a buffer.
    @param      inBufferByteSize
        The desired size of the new buffer, in bytes. An appropriate buffer size depends on the
        processing you will perform on the data as well as on the audio data format.
    @param      inNumberPacketDescriptions
        The desired capacity of the packet description array in the new buffer.
    @param      outBuffer
        On return, points to the newly created audio buffer. The mAudioDataByteSize field in the
        audio queue buffer structure, AudioQueueBuffer, is initially set to 0.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueAllocateBufferWithPacketDescriptions(
                                    AudioQueueRef           inAQ,
                                    UInt32                  inBufferByteSize,
                                    UInt32                  inNumberPacketDescriptions,
                                    AudioQueueBufferRef __nullable * __nonnull outBuffer)              API_AVAILABLE(macos(10.6), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueFreeBuffer
    @abstract   Disposes of an audio queue buffer.
    @discussion
        This function disposes of the buffer allocated by AudioQueueAllocateBuffer. Disposing of
        an audio queue also automatically disposes of any associated buffers and timeline
        objects. Call this function only if you want to dispose of a particular buffer while
        continuing to use an audio queue. You can dispose of buffers only when the associated
        queue is stopped (that is, not processing audio data).
    @param      inAQ
        The queue from which the buffer was allocated.
    @param      inBuffer
        The buffer to be disposed.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueFreeBuffer(               AudioQueueRef           inAQ,
                                    AudioQueueBufferRef     inBuffer)           API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));



/*!
    @function   AudioQueueEnqueueBuffer
    @abstract   Assigns a buffer to an audio queue for recording or playback.
    @discussion
        If the buffer was allocated with AudioQueueAllocateBufferWithPacketDescriptions,
        the client should provide packet descriptions in the buffer's mPacketDescriptions
        and mPacketDescriptionCount fields rather than in inPacketDescs and
        inNumPacketDescs, which should be NULL and 0, respectively, in this case.
        
        For an input queue, pass 0 and NULL for inNumPacketDescs and inPacketDescs,
        respectively. Your callback will receive packet descriptions owned by the audio queue.

    @param      inAQ
        The audio queue you are assigning the buffer to.
    @param      inBuffer
        The buffer to queue (that is, to be recorded into or played from).
    @param      inNumPacketDescs
        The number of packet descriptions pointed to by the inPacketDescs pointer. Applicable
        only for output queues and required only for variable-bit-rate (VBR) audio formats. Pass
        0 for input queues (no packet descriptions are required).
    @param      inPacketDescs
        An array of packet descriptions. Applicable only for output queues and required only for
        variable-bit-rate (VBR) audio formats. Pass NULL for input queues (no packet
        descriptions are required).
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueEnqueueBuffer(            AudioQueueRef                       inAQ,
                                    AudioQueueBufferRef                 inBuffer,
                                    UInt32                              inNumPacketDescs,
                                    const AudioStreamPacketDescription * __nullable inPacketDescs)      API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueEnqueueBufferWithParameters
    @abstract   Assigns a buffer to an audio queue for playback, providing parameters
                and start time information.
    @discussion
        You can exert some control of the buffer queue by using this function. You can assign
        audio queue settings that are in effect carried by an audio queue buffer as you enqueue
        it. Hence, these changes only take effect when an audio queue buffer begins playing.
        
        This function queues a buffer for playback only, not for recording. Audio queues for
        recording have no parameters, do not support variable-bit-rate (VBR) formats (which
        might require trimming), and have a different way to handle timing. When queued for
        playback, the buffer must contain the audio data to be played back. See
        AudioQueueEnqueueBuffer for details on queuing a buffer for recording.

        If the buffer was allocated with AudioQueueAllocateBufferWithPacketDescriptions,
        the client should provide packet descriptions in the buffer's mPacketDescriptions
        and mPacketDescriptionCount fields rather than in inPacketDescs and
        inNumPacketDescs, which should be NULL and 0, respectively, in this case.
    @param      inAQ
        The audio queue associated with the buffer.
    @param      inBuffer
        The buffer to be played from.
    @param      inNumPacketDescs
        The number of packet descriptions pointed to by the inPacketDescs parameter. Required
        only for variable-bit-rate (VBR) audio formats. Pass 0 if no packet descriptions are
        required.
    @param      inPacketDescs
        A pointer to an array of audio stream packet descriptions. Required only for VBR audio
        formats. Pass NULL if no packet descriptions are required.
    @param      inTrimFramesAtStart
        The number of priming frames to skip at the start of the buffer.
    @param      inTrimFramesAtEnd
        The number of frames to skip at the end of the buffer.
    @param      inNumParamValues
        The number of parameter values pointed to by the inParamValues parameter.
    @param      inParamValues
        An array of parameter values. (In Mac OS X v10.5, there is only one parameter,
        kAudioQueueParam_Volume.) These values are set before buffer playback and cannot be
        changed while the buffer is playing. How accurately changes in parameters can be
        scheduled depends on the size of the buffer. If there are no parameters to set
        (inNumParamValues = 0), pass NULL.
    @param      inStartTime
        A pointer to a structure containing the desired start time for playing the buffer. If
        you specify the time using the mSampleTime field of the AudioTimeStamp structure, the
        sample time is relative to the time the queue started. If you pass NULL for the start
        time, the buffer starts immediately after the previously queued buffer, or as soon as
        possible if no buffers are queued ahead of it. Buffers are played in the order they are
        queued. If multiple buffers are queued, their times must be in ascending order or NULL;
        otherwise, an error occurs. The start time indicates when the actual audio data in the
        buffer is to be played (that is, the trim frames are not counted).
        
        Note: When specifying a start time for a buffer, if the buffer is not the first enqueued
        since AudioQueueStop or AudioQueueReset, it is normally necessary to call AudioQueueFlush
        before AudioQueueEnqueueBufferWithParameters.
    @param      outActualStartTime
        On return, points to an AudioTimeStamp structure indicating when the buffer will
        actually play.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueEnqueueBufferWithParameters(
                                    AudioQueueRef                                inAQ,
                                    AudioQueueBufferRef                          inBuffer,
                                    UInt32                                       inNumPacketDescs,
                                    const AudioStreamPacketDescription * __nullable inPacketDescs,
                                    UInt32                                       inTrimFramesAtStart,
                                    UInt32                                       inTrimFramesAtEnd,
                                    UInt32                                       inNumParamValues,
                                    const AudioQueueParameterEvent * __nullable  inParamValues,
                                    const AudioTimeStamp * __nullable            inStartTime,
                                    AudioTimeStamp * __nullable                  outActualStartTime)     API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

#pragma mark -
#pragma mark Queue Control
//=============================================================================
//  Queue Control
//=============================================================================

/*!
    @function   AudioQueueStart
    @abstract   Begins playing or recording audio.
    @discussion
        If the audio hardware is not already running, this function starts it.
    @param      inAQ
        The audio queue to start.
    @param      inStartTime
        A pointer to the time at which the audio queue should start. If you specify the time
        using the mSampleTime field of the AudioTimeStamp structure, the sample time is
        referenced to the sample frame timeline of the associated audio device. May be NULL.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueStart(                    AudioQueueRef                     inAQ,
                                    const AudioTimeStamp * __nullable inStartTime)        API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueuePrime
    @abstract   Begins decoding buffers in preparation for playback.
    @discussion
        This function begins decoding buffers in preparation for playback. It returns when at
        least the number of audio sample frames are decoded and ready to play or when all
        enqueued buffers have been completely decoded. To ensure that a buffer has been decoded
        and is completely ready for playback, before playback:
            1.  Call AudioQueueEnqueueBuffer.
            2.  Call AudioQueuePrime, which waits if you pass 0 to have a default number of
                frames decoded.
            3.  Call AudioQueueStart.

        Calls to AudioQueuePrime following AudioQueueStart/AudioQueuePrime, and before
        AudioQueueReset/AudioQueueStop, will have no useful effect. In this situation,
        outNumberOfFramesPrepared will not have a useful return value.
    @param      inAQ
        The audio queue to be primed.
    @param      inNumberOfFramesToPrepare
        The number of frames to decode before returning. Pass 0 to decode all enqueued buffers.
    @param      outNumberOfFramesPrepared
        If not NULL, on return, a pointer to the number of frames actually decoded and prepared
        for playback.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueuePrime(                    AudioQueueRef           inAQ,
                                    UInt32                  inNumberOfFramesToPrepare,
                                    UInt32 * __nullable     outNumberOfFramesPrepared)  API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueStop
    @abstract   Stops playing or recording audio.
    @discussion
        This function resets the audio queue and stops the audio hardware associated with the
        queue if it is not in use by other audio services. Synchronous stops occur immediately,
        regardless of previously buffered audio data. Asynchronous stops occur after all queued
        buffers have been played or recorded.
    @param      inAQ
        The audio queue to stop.
    @param      inImmediate
        If you pass true, the stop request occurs immediately (that is, synchronously), and the
        function returns when the audio queue has stopped. Buffer callbacks are invoked during
        the stopping. If you pass false, the function returns immediately, but the queue does
        not stop until all its queued buffers are played or filled (that is, the stop occurs
        asynchronously). Buffer callbacks are invoked as necessary until the queue actually
        stops. Also, a playback audio queue callback calls this function when there is no more
        audio to play.

        Note that when stopping immediately, all pending buffer callbacks are normally invoked
        during the process of stopping. But if the calling thread is responding to a buffer
        callback, then it is possible for additional buffer callbacks to occur after
        AudioQueueStop returns.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueStop(                     AudioQueueRef           inAQ,
                                    Boolean                 inImmediate)            API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueuePause
    @abstract   Pauses audio playback or recording.
    @discussion
        Pausing the queue does not affect buffers or reset the audio queue. To resume playback
        or recording using the audio queue, call AudioQueueStart.
    @param      inAQ
        The queue to be paused.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueuePause(                    AudioQueueRef           inAQ)       API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueFlush
    @abstract   Resets the audio queue's decoder state.
    @discussion
        After all queued buffers have been played, the function cleans up all decoder state
        information. You must call this function following a sequence of buffers of encoded
        audio; otherwise, some of the audio might not play in the next set of queued buffers.
        The only time it is not necessary to call AudioQueueFlush is following AudioQueueStop
        with inImmediate=false. (This action internally calls AudioQueueFlush.)
        
        Also, you might wish to call this function before calling AudioQueueStop depending on
        whether you want to stop immediately regardless of what has played or whether you want
        to ensure that all buffered data and all data that is in the middle of processing gets
        recorded or played before stopping.
        
    @param      inAQ
        The audio queue to be flushed.
        
    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueFlush(                    AudioQueueRef           inAQ)            API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueReset
    @abstract   Resets an audio queue.
    @discussion
        This function immediately resets an audio queue, flushes any queued buffer, removes all
        buffers from previously scheduled use, and resets any decoder and digital signal
        processing (DSP) state information. It also invokes callbacks for any flushed buffers.
        If you queue any buffers after calling this function, processing does not occur until
        the decoder and DSP state information is reset. Hence, a discontinuity (that is, a
        "glitch") might occur.

        Note that when resetting, all pending buffer callbacks are normally invoked
        during the process of resetting. But if the calling thread is responding to a buffer
        callback, then it is possible for additional buffer callbacks to occur after
        AudioQueueReset returns.
    @param      inAQ
        The audio queue to reset.

    @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueReset(                    AudioQueueRef           inAQ)            API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

#pragma mark -
#pragma mark Parameter Management
//=============================================================================
//  Parameter Management
//=============================================================================

/*!
    @function   AudioQueueGetParameter
    @abstract   Obtains an audio queue parameter value.
    @discussion
        You can access the current parameter values for an audio queue at any time with this
        function.
    @param      inAQ
        The audio queue whose parameter value you want to obtain.
    @param      inParamID
        The ID of the parameter you want to obtain. In Mac OS X v10.5, audio queues have one
        parameter available: kAudioQueueParam_Volume, which controls the queue's playback
        volume.
    @param      outValue
        On return, points to the current value of the specified parameter.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueGetParameter(             AudioQueueRef               inAQ,
                                    AudioQueueParameterID       inParamID,
                                    AudioQueueParameterValue *  outValue)       API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueSetParameter
    @abstract   Sets an audio queue parameter value.
    @param      inAQ
        The audio queue whose parameter value you want to set.
    @param      inParamID
        The ID of the parameter you want to set.
    @param      inValue
        The parameter value to set.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueSetParameter(             AudioQueueRef               inAQ,
                                    AudioQueueParameterID       inParamID,
                                    AudioQueueParameterValue    inValue)        API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

                                                                        
#pragma mark -
#pragma mark Property Management
//=============================================================================
//  Property Management
//=============================================================================

/*!
    @function   AudioQueueGetProperty
    @abstract   Obtains an audio queue property value.
    @param      inAQ
        The audio queue whose property value you want to obtain.
    @param      inID
        The ID of the property you want to obtain. See "Audio Queue Property IDs."
    @param      outData
        On return, points to the desired property value.
    @param      ioDataSize
        A pointer to the size of the property data. On input, points to the maximum bytes of
        space the caller expects to receive. On return, points to the actual data size.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueGetProperty(              AudioQueueRef           inAQ,
                                    AudioQueuePropertyID    inID,
                                    void *                  outData,
                                    UInt32 *                ioDataSize)             API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueSetProperty
    @abstract   Sets an audio queue property value.
    @param      inAQ
        The audio queue whose property value you want to set.
    @param      inID
        The ID of the property you want to set. See "Audio Queue Property IDs" for the various
        audio queue properties.
    @param      inData
        A pointer to the property value to set.
    @param      inDataSize
        The size of the property data.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueSetProperty(              AudioQueueRef           inAQ,
                                    AudioQueuePropertyID    inID,
                                    const void *            inData,
                                    UInt32                  inDataSize)             API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));


/*!
    @function   AudioQueueGetPropertySize
    @abstract   Obtains the size of an audio queue property.
    @param      inAQ
        The audio queue containing the property value whose size you want to obtain.
    @param      inID
        The ID of the property value whose size you want to obtain. See "Audio Queue Property
        IDs" for possible values.
    @param      outDataSize
        On return, points to the size of the specified property value.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueGetPropertySize(          AudioQueueRef           inAQ,
                                    AudioQueuePropertyID    inID,
                                    UInt32 *                outDataSize)            API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueAddPropertyListener
    @abstract   Adds a listener callback for a property.
    @discussion 
        This callback is used to act upon a change in an audio queue property such as
        kAudioQueueProperty_IsRunning. For instance, if your application has a user interface
        with a Play/Stop button, and kAudioQueueProperty_IsRunning changes, you need to update
        your button.
    @param      inAQ
        The audio queue that owns the property you want to assign the listener callback to.
    @param      inID
        The ID of the property to which you want to assign a listener callback. See "Audio Queue Property IDs".
    @param      inProc
        The listener callback to be called when the property value changes.
    @param      inUserData
        A value to be passed to the listener callback when it is called.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueAddPropertyListener(      AudioQueueRef                   inAQ,
                                    AudioQueuePropertyID            inID,
                                    AudioQueuePropertyListenerProc  inProc,
                                    void * __nullable               inUserData)     API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueRemovePropertyListener
    @abstract   Removes a listener callback for a property.
    @param      inAQ
        The audio queue that owns the property from which you want to remove a listener.
    @param      inID
        The ID of the property from which you want to remove a listener.
    @param      inProc
        The listener being removed.
    @param      inUserData
        The same inUserData value that was previously passed to AudioQueueAddPropertyListener.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueRemovePropertyListener(   AudioQueueRef                   inAQ,
                                    AudioQueuePropertyID            inID,
                                    AudioQueuePropertyListenerProc  inProc,
                                    void * __nullable               inUserData)     API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

                                    

#pragma mark -
#pragma mark Handling Timing
//=============================================================================
//  Handling Timing
//=============================================================================

/*!
    @function   AudioQueueCreateTimeline
    @abstract   Creates a timeline object.
    @discussion
        You need to instantiate a timeline object if you want to know about any timeline
        discontinuities. See AudioQueueGetCurrentTime for more details.
    @param      inAQ
        The audio queue to associate with the new timeline object.
    @param      outTimeline
        On return, points to the newly created timeline object.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueCreateTimeline(           AudioQueueRef           inAQ,
                                    AudioQueueTimelineRef __nullable * __nonnull outTimeline)            API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueDisposeTimeline
    @abstract   Disposes of a timeline object.
    @discussion
        Disposing of an audio queue automatically disposes of any associated timeline objects.
        Call this function only if you want to dispose of a timeline object and not the audio
        queue associated with it.
    @param      inAQ
        The audio queue associated with the timeline object you want to dispose of.
    @param      inTimeline
        The timeline object to dispose of.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueDisposeTimeline(          AudioQueueRef           inAQ,
                                    AudioQueueTimelineRef   inTimeline)             API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueGetCurrentTime
    @abstract   Obtains the current audio queue time.
    @discussion
        You must specify a timeline object if you want to be notified about any timeline
        discontinuities in the outTimelineDiscontinuity parameter. If you don't care about
        discontinuities, pass NULL in the inTimeLine and outTimelineDiscontinuity parameters.
    @param      inAQ
        The audio queue whose current time you want to obtain.
    @param      inTimeline
        The audio queue timeline object to which any timeline discontinuities are reported. May
        be NULL.
    @param      outTimeStamp
        On return, points to an audio timestamp structure containing the current audio queue
        time. The mSampleTime field is in terms of the audio queue's sample rate, and relative
        to the time at which the queue has started or will start.
    @param      outTimelineDiscontinuity
        Can be NULL. On return, only set to true or false if the inTimeLine parameter is not
        NULL. Set to true if a discontinuity has occurred in the sample timeline of the audio
        queue. For instance, the device's sample rate changed and a gap occurred in playback or
        recording, or the audio queue was unable to prepare and playback in time because it was
        late.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueGetCurrentTime(           AudioQueueRef                    inAQ,
                                    AudioQueueTimelineRef __nullable inTimeline,
                                    AudioTimeStamp * __nullable      outTimeStamp,
                                    Boolean * __nullable             outTimelineDiscontinuity)       API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueDeviceGetCurrentTime
    @abstract   Obtains the current time of the audio device associated with an audio queue.
    @discussion
        If the audio device associated with the audio queue is not running, the only valid field
        in the audio timestamp structure is mHostTime. This result differentiates the action of
        this function from that of the AudioDeviceGetCurrentTime function, (declared in
        AudioHardware.h) which returns an error if the audio device is not running.
    @param      inAQ
        The audio queue whose audio device is to be queried.
    @param      outTimeStamp
        A pointer to a structure that, on return, contains the current time of the audio device
        associated with the audio queue.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueDeviceGetCurrentTime(     AudioQueueRef           inAQ,
                                    AudioTimeStamp *        outTimeStamp)      API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueDeviceTranslateTime
    @abstract   Converts the time in the time base of the associated audio device from one
                representation to another.
    @discussion
        This function converts from one time representation to another (for example, from sample
        time to host time or vice versa):
        
        <ul>
        <li>    Sample time is the absolute sample frame time.
        Sample numbers are the count of the samples on the audio device.</li>
        <li>    Host time is the
        time base of the host machine such as the time of the bus clock on the CPU.</li>
        </ul>

        The mSampleTime field in the AudioTimestamp structure (described in Core Audio Data
        Types Reference) is always in device time, not in audio queue time. Audio queue time is
        relative to the audio queue's start time. The associated audio device has to be running
        for the AudioQueueDeviceTranslateTime function to provide a result.
    @param      inAQ
        The queue whose audio device is to perform the requested time translation.
    @param      inTime
        A pointer to a structure containing the time to be translated.
    @param      outTime
        A pointer to the the translated time.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueDeviceTranslateTime(      AudioQueueRef           inAQ,
                                    const AudioTimeStamp *  inTime,
                                    AudioTimeStamp *        outTime)        API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueDeviceGetNearestStartTime
    @abstract   Obtains an audio device's start time that is closest to a requested start time.
    @param      inAQ
        The audio queue whose device's nearest start time you want to obtain.
    @param      ioRequestedStartTime
        On entry, points to the requested start time. On return, points to the actual start time.
    @param      inFlags
        Reserved for future use. Pass 0.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueDeviceGetNearestStartTime(AudioQueueRef           inAQ,
                                    AudioTimeStamp *        ioRequestedStartTime,
                                    UInt32                  inFlags)        API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

#pragma mark -
#pragma mark Offline Rendering
//=============================================================================
//  Offline Rendering
//=============================================================================

/*!
    @function   AudioQueueSetOfflineRenderFormat
    @abstract   Specify an audio format to which the queue will perform subsequent offline rendering,
                or disable offline rendering.
    @discussion
                An output queue's audio playback can be redirected for capture to an audio file,
                to support an export function, for example. AudioQueueSetOfflineRenderFormat switches
                a queue between normal and offline rendering modes.
    @param      inAQ
        The output queue whose offline rendering mode is to be changed.
    @param      inFormat
        The desired format for offline rendering. Pass NULL to disable offline rendering and return the
        queue to normal output to an audio device. This format must be linear PCM and (if not mono)
        interleaved.
    @param      inLayout
        The desired channel layout for offline rendering; also NULL when disabling offline rendering.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueSetOfflineRenderFormat(   AudioQueueRef                                  inAQ,
                                    const AudioStreamBasicDescription * __nullable inFormat,
                                    const AudioChannelLayout * __nullable          inLayout)
																		API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueOfflineRender
    @abstract   Obtain a buffer of audio output from a queue in offline rendering mode.
    @param      inAQ
        The output queue from which to obtain output.
    @param      inTimestamp
        The point in time corresponding to the beginning of the output buffer. Only mSampleTime
        is used. mFlags must include kAudioTimeStampSampleTimeValid.
    @param      ioBuffer
        The buffer into which the queue will render.
    @param      inNumberFrames
        The number of frames of audio to render. Note that fewer frames than requested may be returned.
        This can happen if insufficient data was enqueued.
    @result
        An OSStatus result code.
*/
extern OSStatus
AudioQueueOfflineRender(            AudioQueueRef           inAQ,
                                    const AudioTimeStamp *  inTimestamp,
                                    AudioQueueBufferRef     ioBuffer,
                                    UInt32                  inNumberFrames)     API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

#pragma mark -
#pragma mark Processing Taps
//=============================================================================
//  Processing Taps
//=============================================================================


/*!
    @function   AudioQueueProcessingTapNew
    @abstract   Create a new processing tap
    @discussion
                This function creates a processing tap on a given audio queue. A
                processing tap can only be established (or removed) on an audio queue that is
                stopped (paused is not sufficient). The processing tap will then be used to
                process either decoded data in the case of an output queue, or input data
                (before it is encoded) in the case of an input queue.

                The processing is performed on audio either before or after any effects or other
                processing (varispeed, etc) is applied by the audio queue, depending on inFlags.
    
    @param      inAQ    
                    The audio queue from which to create the processing tap
    @param      inCallback
                    A callback which the queue will call to process the audio
    @param      inClientData
                    Client data provided to the callback
    @param      inFlags
                    Flags that are used to control aspects of the processing tap.
                    Valid flags are:
                        - kAudioQueueProcessingTap_PreEffects: processing is done before any
                            further effects are applied by the audio queue to the audio
                        - kAudioQueueProcessingTap_PostEffects: processing is done after all
                            processing is done, including that of other taps.
                        - kAudioQueueProcessingTap_Siphon
    @param      outMaxFrames
                    The maximum number of sample frames that can be requested of a processing
                    tap at any one time. Typically this will be approximately 50 msec of audio
                    (2048 samples @ 44.1kHz)
    @param      outProcessingFormat
                    The format in which the client will receive the audio data to be processed.
                    This will always be the same sample rate as the client format and usually
                    the same number of channels as the client format of the audio queue. (NOTE:
                    the number of channels may be different in some cases if the client format
                    has some channel count restrictions, for instance the client provides 5.1
                    AAC, but the decoder can only produce stereo). The channel order, if the
                    same as the client format, will be the same as the client channel order. If
                    the channel count is changed, it will be to either 1 (mono) or 2 (stereo, in
                    which case the first channel is left, the second right).

                    If the data is not in a convenient format for the client to process in, then
                    the client should convert the data to and from that format. This is the most
                    efficient mechanism to use (as the audio queue can chose a format that is
                    most efficient from its playback (or recording) requirement.
    @param      outAQTap
                    The processing tap object.
                    
    @result     An OSStatus result code.
*/
extern OSStatus 
AudioQueueProcessingTapNew(         AudioQueueRef                   inAQ,
                                    AudioQueueProcessingTapCallback inCallback,
                                    void * __nullable               inClientData,
                                    AudioQueueProcessingTapFlags    inFlags,
                                    UInt32 *                        outMaxFrames,
                                    AudioStreamBasicDescription *   outProcessingFormat,
                                    AudioQueueProcessingTapRef __nullable * __nonnull outAQTap)
                                        API_AVAILABLE(macos(10.7), ios(6.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueProcessingTapDispose
    @abstract   Dispose a processing tap object
    @discussion 
                As with AudioQueueProcessingTapNew, this call can only be made on an
                audio queue that is stopped (paused is not sufficient)
    
    @param      inAQTap
                    The processing tap to dispose.

   @result     An OSStatus result code.
*/
extern OSStatus 
AudioQueueProcessingTapDispose(     AudioQueueProcessingTapRef      inAQTap)
                                        API_AVAILABLE(macos(10.7), ios(6.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueProcessingTapGetSourceAudio
    @abstract   Used by a processing tap to retrieve source audio.
    @discussion 
        This function may only be called from the processing tap's callback.
    
    @param      inAQTap
                    the processing tap
    @param      inNumberFrames
                    the number of frames the processing tap requires for its processing
    @param      ioTimeStamp
                    On an input audio queue, the timestamp is returned from this function.
                    On an output audio queue, the caller must provide a continuous timestamp.
    @param      outFlags
                    flags to describe state about the input requested, e.g.
                    discontinuity/complete
    @param      outNumberFrames
                    the number of source frames that have been provided by the parent audio
                    queue. This can be less than the number of requested frames specified in
                    inNumberFrames
    @param      ioData
                    the audio buffer list which will contain the source data. The audio queue owns
                    the buffer pointers if NULL pointers were provided (recommended). In this case
                    the source buffers are only valid for the duration of the processing tap
                    callback. If the buffer pointers are non-NULL, then they must be big enough to
                    hold inNumberFrames, and the audio queue will copy its source data into those
                    buffers.
                    
   @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueProcessingTapGetSourceAudio(
                                    AudioQueueProcessingTapRef      inAQTap,
                                    UInt32                          inNumberFrames,
                                    AudioTimeStamp *                ioTimeStamp,
                                    AudioQueueProcessingTapFlags *  outFlags,
                                    UInt32 *                        outNumberFrames,
                                    AudioBufferList *               ioData)
                                        API_AVAILABLE(macos(10.7), ios(6.0), watchos(2.0), tvos(9.0));

/*!
    @function   AudioQueueProcessingTapGetQueueTime
    @abstract   Used by a processing tap to retrieve the queue's current time.
    @discussion 
        This function may only be called from the processing tap's callback, and only
        for audio output queues. It must be called after calling
        AudioQueueProcessingTapGetSourceAudio.
    
    @param      inAQTap
                    the processing tap
    @param      outQueueSampleTime
                    the current sample time of the audio queue. This will appear to be stationary
                    if the queue is paused.
    @param      outQueueFrameCount
                    the number of sample frames of queue time corresponding to the current chunk of
                    audio being processed by the tap. This will differ from the frame count passed
                    to the tap if the queue's playback rate is currently other than 1.0, due to the
                    use of time compression/expansion. The frame count can also be 0 if the queue is
                    paused.
                    
   @result     An OSStatus result code.
*/
extern OSStatus
AudioQueueProcessingTapGetQueueTime(    AudioQueueProcessingTapRef  inAQTap,
                                        Float64 *                   outQueueSampleTime,
                                        UInt32 *                    outQueueFrameCount)
                                        API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioQueue_h

// ==========  AudioToolbox.framework/Headers/AudioComponent.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AudioComponent.h>)
/*!
	@file		AudioComponent.h
 	@framework	AudioToolbox.framework
 	@copyright	(c) 2007-2015 Apple, Inc. All rights reserved.
	@brief		API's to locate, get information about, and open audio components.

	@discussion

	This file defines a collection of APIs to find, get information about, and open
	audio components (such as audio units, audio codecs, and audio file components).

	Originally, CoreServices' Component Manager was used for the registration, discovery, and
	packaging of these loadable code modules. However, in order to provide an API that will be
	supported going forward from Mac OS X 10.6 and iOS 2.0, it is advised that applications use the
	Audio Component APIs to find and load (open) audio components such as audio units.

	The type "AudioComponent" or "AudioComponentInstance" should be seen and used as a distinct type
	from the Component Manager types of "Component" and "ComponentInstance". It is never safe to
	assume a direct cast is compatible between this type and the other.

	Beginning with Mac OS X 10.7, AudioComponents can be registered and used directly without
	involving the Component Manager. The system scans certain directories for bundles with names
	ending in ".audiocomp" or ".component" (the latter permits registering plug-ins in a single
	bundle with both the Component Manager and the Audio Component system). These directories are
	scanned non-recursively:

		~/Library/Audio/Plug-Ins/Components
		/Library/Audio/Plug-Ins/Components
		/System/Library/Components

	Bundles' Info.plist dictionaries should contain an "AudioComponents" item whose value
	is an array of dictionaries, e.g.

	@textblock
		<key>AudioComponents</key>
		<array>
			<dict>
				<key>type</key>
				<string>aufx</string>
				<key>subtype</key>
				<string>XMPL</string>
				<key>manufacturer</key>
				<string>ACME</string>
				<key>name</key>
				<string>AUExample</string>
				<key>version</key>
				<integer>12345</integer>
				<key>factoryFunction</key>
				<string>AUExampleFactory</string>
				
				<!-- An AudioComponent is sandbox safe -->
				
				<key>sandboxSafe</key>
				<true/>
				
				<!-- or it can describe its resource usage -->
				
				<key>resourceUsage</key>
				<dict>
					<key>iokit.user-client</key>
					<array>
						<string>CustomUserClient1</string>
						<string>CustomUserClient2</string>
					</array>
					<key>mach-lookup.global-name</key>
					<array>
						<string>MachServiceName1</string>
						<string>MachServiceName2</string>
					</array>
					<key>network.client</key>
					<true/>
					<key>temporary-exception.files.all.read-write</key>
					</true>
				</dict>

				<!-- An AudioComponent can define its tags -->
				
				<key>tags</key>
				<array>
					<string>Effect</string>
					<string>Equalizer</string>
				</array>
			</dict>
		</array>
	@/textblock

	The type, subtype and manufacturer keys correspond to the OSType fields of the
	AudioComponentDescription structure. They can be strings if they are 4 ASCII characters;
	otherwise they must be 32-bit integers.

	The "factoryFunction" is the name of a AudioComponentFactoryFunction in the bundle's binary.


	SANDBOX-SAFETY

	The "sandboxSafe" key is used to indicate whether or not an AudioComponent can be loaded
	directly into a sandboxed process. This key is reflected in the componentFlags field of the the
	AudioComponentDescription for the AudioComponent with the constant,
	kAudioComponentFlag_SandboxSafe. Note that if this key is not present, it is assumed that the
	AudioComponent is not sandbox safe.

	The "resourceUsage" key describes the system resources used by an AudioComponent that is not
	sandbox safe. The keys for this dictionary are described below. If the "sandboxSafe" key is
	true, this dictionary should not be included.

	The "iokit.user-client" key is a "resourceUsage" key that describes the IOKit user-client
	objects the AudioComponent will open. It is an array of the user-clients' class names.

	The "mach-lookup.global-name" key is a "resourceUsage" key that describes the mach services the
	AudioComponent needs to connect to. It is an array of the names of the services. Note that these
	services can be direct mach services found via bootstrap_look_up() or XPC services found via
	xpc_connection_create_mach_service().

	The "network.client" key is a "resourceUsage" key that indicates that the AudioComponent will
	receive data from the network.

	The "temporary-exception.files.all.read-write" key is a "resourceUsage" key that indicates that
	the AudioComponent needs arbitrary access to the file system. This is for backward compatibility
	for AudioComponents that have not yet adopted the usage of security scope bookmarks and/or the
	usage of the standard file dialog for discovering, accessing and storing persistent references
	to files on the file system. In a future OS release, this key will not be supported.

	Note that a sandbox-safe AudioComponent can function correctly in even the most severely
	sandboxed process. This means that the process will have curtailed or no access to common system
	resources like the file system, device drivers, the network, and communication with other
	processes.

	When instantiating a sandbox unsafe AudioComponent in a sandboxed process, the system evaluates
	the "resourceUsage" information against the restrictions the process is under. If the
	"resourceUsage" will not violate those restrictions, the AudioComponent will be instantiated and
	can be used as normal. Note that the system will set kAudioComponentFlag_SandboxSafe in the
	AudioComponentDescription in this case.

	If the "resourceUsage" information includes things that can't be accessed from the process and
	the process has the entitlement, "com.apple.security.temporary-exception.audio-unit-host", the
	system will ask the user whether or not it is acceptable for the process to open the unsafe
	AudioComponent. If the user says yes, the system will suspend the process's sandbox and allow
	the unsafe AudioComponent to be opened and used.


	TAGS

	The "tags" key is an array of tags associated with the defined AudioComponent. The following are
	the set of predefined standard tags that are localized and can be used in the audio unit
	definition. "Equalizer", "Dynamics", "Distortion", "Synthesizer", "Effects", "Filter", "Dynamics
	Processor", "Delay", "Reverb", "Pitch", "Panner", "Imaging", "Sampler", "Mixer", "Format
	Converter", "Time Effect", "Output", "Offline Effect", "Drums", "Guitar", "Vocal", "Bass",
	"MIDI". 

	These standard tags should not be localized in the audio unit.

	Localizing the tags is similar to localizing AudioUnit parameter strings. Create a strings 
	resource file and name it "AudioUnitTags.strings".
	For more information on strings resource file please check
	https://developer.apple.com/library/mac/documentation/macosx/conceptual/bpinternational/Articles/StringsFiles.html
*/

#ifndef AudioUnit_AudioComponent_h
#define AudioUnit_AudioComponent_h

//=====================================================================================================================
#pragma mark Overview

#include <TargetConditionals.h>
#include <Availability.h>
#include <CoreAudioTypes/CoreAudioTypes.h>
#include <CoreFoundation/CoreFoundation.h>

CF_ASSUME_NONNULL_BEGIN

//=====================================================================================================================
#pragma mark Constants

/*!
	@constant	kAudioComponentFlag_Unsearchable

	When this bit in AudioComponentDescription's componentFlags is set, AudioComponentFindNext
	will only return this component when performing a specific, non-wildcard search for the
	component, i.e. with non-zero values of componentType, componentSubType, and
	componentManufacturer. This can be useful when privately registering a component.
	
	@constant	kAudioComponentFlag_SandboxSafe
	
	An AudioComponent sets this bit in its componentFlags to indicate to the system that the
	AudioComponent is safe to open in a sandboxed process.
	
	@constant	kAudioComponentFlag_IsV3AudioUnit
	
	The system sets this flag automatically when registering components which implement a version 3
	Audio Unit.
	
	@constant	kAudioComponentFlag_RequiresAsyncInstantiation
	
	The system sets this flag automatically when registering components which require asynchronous
	instantiation via AudioComponentInstantiate (v3 audio units with views).
	
	@constant	kAudioComponentFlag_CanLoadInProcess
	
	The system sets this flag automatically when registering components which can be loaded into
	the current process. This is always true for V2 audio units; it depends on the packaging
	in the case of a V3 audio unit.
*/
typedef CF_OPTIONS(UInt32, AudioComponentFlags) {
    kAudioComponentFlag_Unsearchable                CF_ENUM_AVAILABLE(10_7, 5_0)   = 1,
    kAudioComponentFlag_SandboxSafe                 CF_ENUM_AVAILABLE(10_8, 6_0)   = 2,
    kAudioComponentFlag_IsV3AudioUnit               CF_ENUM_AVAILABLE(10_11, 9_0)  = 4,
    kAudioComponentFlag_RequiresAsyncInstantiation  CF_ENUM_AVAILABLE(10_11, 9_0)  = 8,
	kAudioComponentFlag_CanLoadInProcess			CF_ENUM_AVAILABLE(10_11, 9_0)  = 0x10
};

/*! @enum       AudioComponentInstantiationOptions
    @brief      Options controlling component instantiation.
    @discussion
        Most component instances are loaded into the calling process.

        A version 3 audio unit, however, can be loaded into a separate extension service process,
        and this is the default behavior for these components. To be able to load one in-process
        requires that the developer package the audio unit in a bundle separate from the application
        extension, since an extension's main binary cannot be dynamically loaded into another
        process.
        
        An OS X host may request in-process loading of such audio units using
        kAudioComponentInstantiation_LoadInProcess.

        kAudioComponentFlag_IsV3AudioUnit specifies whether an audio unit is implemented using API
        version 3.

        These options are just requests to the implementation. It may fail and fall back to the
        default.
    @constant kAudioComponentInstantiation_LoadOutOfProcess
        Attempt to load the component into a separate extension process.
    @constant kAudioComponentInstantiation_LoadInProcess
        Attempt to load the component into the current process. Only available on OS X.
*/
typedef CF_OPTIONS(UInt32, AudioComponentInstantiationOptions) {
    kAudioComponentInstantiation_LoadOutOfProcess   CF_ENUM_AVAILABLE(10_11,  9_0) = 1,
    kAudioComponentInstantiation_LoadInProcess      CF_ENUM_AVAILABLE(10_11,  NA)  = 2
};


//=====================================================================================================================
#pragma mark Data Types

/*!
    @struct         AudioComponentDescription
    @discussion     A structure used to describe the unique and identifying IDs of an audio component 
    @var            componentType
                        A unique 4-byte code identifying the generic type of an audio component
    @var            componentSubType
                        the particular flavor of this instance
    @var            componentManufacturer
                        vendor identification
    @var            componentFlags
                        must be set to zero unless a known specific value is requested
    @var            componentFlagsMask
                        must be set to zero unless a known specific value is requested
*/
#pragma pack(push, 4)
typedef struct AudioComponentDescription {
    OSType              componentType;
    OSType              componentSubType;
    OSType              componentManufacturer;
    UInt32              componentFlags;
    UInt32              componentFlagsMask;
} AudioComponentDescription;
#pragma pack(pop)

/*!
    @typedef        AudioComponent
    @abstract       The type used to represent a class of particular audio components
    @discussion     An audio component is usually found through a search and is then uniquely
                    identified by the triple of an audio component's type, subtype and
                    manufacturer.
                    
                    It can have properties associated with it (such as a name, a version).

                    It is then used as a factory (like a class in an object-oriented programming
                    language) from which to create instances. The instances are used to do the
                    actual work.

                    For example: the AudioComponentDescription 'aufx'/'dely'/'appl' describes the
                    delay audio unit effect from Apple, Inc. You can find this component by
                    searching explicitly for the audio component that matches this pattern (this is
                    an unique identifier - there is only one match to this triple ID). Then once
                    found, instances of the Apple delay effect audio unit can be created from its
                    audio component and used to apply that effect to an audio signal. A single
                    component can create any number of component instances.
*/
typedef struct OpaqueAudioComponent *   AudioComponent;

/*!
    @typedef        AudioComponentInstance
    @abstract       The type used to represent an instance of a particular audio component
    @discussion     An audio component instance is created from its factory/producer audio
                    component. It is the body of code that does the work.
    
                    A special note: While on the desktop this is typedef'd to a
                    ComponentInstanceRecord *, you should not assume that this will always be
                    compatible and usable with Component Manager calls.
*/
#if TARGET_OS_IPHONE || (defined(AUDIOCOMPONENT_NOCARBONINSTANCES) && AUDIOCOMPONENT_NOCARBONINSTANCES)
    typedef struct OpaqueAudioComponentInstance *   AudioComponentInstance;
#else
    typedef struct ComponentInstanceRecord *        AudioComponentInstance;
#endif

/*!
    @typedef        AudioComponentMethod
    @abstract       Generic prototype for an audio plugin method.
    @discussion     Every audio plugin will implement a collection of methods that match a particular
					selector. For example, the AudioUnitInitialize API call is implemented by a
					plugin implementing the kAudioUnitInitializeSelect selector. Any function implementing
					an audio plugin selector conforms to the basic pattern where the first argument
					is a pointer to the plugin instance structure, has 0 or more specific arguments,  
					and returns an OSStatus.
*/
typedef OSStatus (*AudioComponentMethod)(void *self, ...);

/*!
    @struct         AudioComponentPlugInInterface
    @discussion     A structure used to represent an audio plugin's routines 
    @var            Open
                        the function used to open (or create) an audio plugin instance
    @var            Close
                        the function used to close (or dispose) an audio plugin instance
    @var            Lookup
                        this is used to return a function pointer for a given selector, 
						or NULL if that selector is not implemented
    @var            reserved
                        must be NULL
*/
typedef struct AudioComponentPlugInInterface {
	OSStatus						(*Open)(void *self, AudioComponentInstance mInstance);
	OSStatus						(*Close)(void *self);
	AudioComponentMethod __nullable	(* __nonnull Lookup)(SInt16 selector);
	void * __nullable				reserved;
} AudioComponentPlugInInterface;

/*!
    @typedef        AudioComponentFactoryFunction
    @abstract       A function that creates AudioComponentInstances.
    @discussion
                    Authors of AudioComponents may register them from bundles as described
                    above in the discussion of this header file, or dynamically within a single
                    process, using AudioComponentRegister.
    
    @param          inDesc
                        The AudioComponentDescription specifying the component to be instantiated.
    @result         A pointer to a AudioComponentPlugInInterface structure.
*/
typedef AudioComponentPlugInInterface * __nullable (*AudioComponentFactoryFunction)(const AudioComponentDescription *inDesc);

//=====================================================================================================================
#pragma mark Functions

#ifdef __cplusplus
extern "C" {
#endif

/*!
    @function       AudioComponentFindNext
    @abstract       Finds an audio component.
    @discussion     This function is used to find an audio component that is the closest match
                    to the provided values. Note that the list of available components may change
					dynamically in situations involving inter-app audio on iOS, or version 3
					audio unit extensions. See kAudioComponentRegistrationsChangedNotification.

    @param          inComponent
                        If NULL, then the search starts from the beginning until an audio
                        component is found that matches the description provided by inDesc.
                        If non-NULL, then the search starts (continues) from the previously
                        found audio component specified by inComponent, and will return the next
                        found audio component.
    @param          inDesc
                        The type, subtype and manufacturer fields are used to specify the audio
                        component to search for. A value of 0 (zero) for any of these fields is
                        a wildcard, so the first match found is returned.
    @result         An audio component that matches the search parameters, or NULL if none found.
*/
extern AudioComponent __nullable
AudioComponentFindNext (    AudioComponent __nullable           inComponent,
                            const AudioComponentDescription *   inDesc) 
                                                                            API_AVAILABLE(macos(10.6), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function       AudioComponentCount
    @abstract       Counts audio components.
    @discussion     Returns the number of AudioComponents that match the specified
                    AudioComponentDescription.
    @param          inDesc
                        The type, subtype and manufacturer fields are used to specify the audio
                        components to count A value of 0 (zero) for any of these fields is a
                        wildcard, so will match any value for this field
    @result         a UInt32. 0 (zero) means no audio components were found that matched the
                    search parameters.
*/
extern UInt32
AudioComponentCount (   const AudioComponentDescription *       inDesc)
                                                                            API_AVAILABLE(macos(10.6), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function       AudioComponentCopyName
    @abstract       Retrieves the name of an audio component.
    @discussion     the name of an audio component
    @param          inComponent
                        the audio component (must not be NULL)
    @param          outName
                        a CFString that is the name of the audio component. This string should
                        be released by the caller.
    @result         an OSStatus result code.
*/
extern OSStatus 
AudioComponentCopyName (    AudioComponent                      inComponent, 
                            CFStringRef __nullable * __nonnull  outName)
                                                                            API_AVAILABLE(macos(10.6), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function       AudioComponentGetDescription
    @abstract       Retrieve an audio component's description.
    @discussion     This will return the fully specified audio component description for the
                    provided audio component.
    @param          inComponent
                        the audio component (must not be NULL)
    @param          outDesc
                        the audio component description for the specified audio component
    @result         an OSStatus result code.
*/
extern OSStatus 
AudioComponentGetDescription(   AudioComponent                  inComponent,
                                AudioComponentDescription *     outDesc)
                                                                            API_AVAILABLE(macos(10.6), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function       AudioComponentGetVersion
    @abstract       Retrieve an audio component's version.
    @param          inComponent
                        the audio component (must not be NULL)
    @param          outVersion
                        the audio component's version in the form of 0xMMMMmmDD (Major, Minor, Dot)
    @result         an OSStatus result code.
*/
extern OSStatus 
AudioComponentGetVersion(   AudioComponent                      inComponent, 
                            UInt32 *                            outVersion)
                                                                            API_AVAILABLE(macos(10.6), ios(2.0), watchos(2.0), tvos(9.0));

#if defined(__OBJC__) && !TARGET_OS_IPHONE
@class NSImage;

/*!
    @function       AudioComponentGetIcon
    @abstract       Fetches an icon representing the component.
    @param          comp
        The component whose icon is to be retrieved.
    @result
        An autoreleased NSImage object.
    @discussion
        For a component originating in an app extension, the returned icon will be that of the
        application containing the extension.
        
        For components loaded from bundles, the icon will be that of the bundle.
*/
extern NSImage * __nullable
AudioComponentGetIcon(AudioComponent comp)
                                                                            API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, watchos, tvos);
#endif

/*!
    @function       AudioComponentInstanceNew
    @abstract       Creates an audio component instance.
    @discussion     This function creates an instance of a given audio component. The audio
                    component instance is the object that does all of the work, whereas the
                    audio component is the way an application finds and then creates this object
                    to do this work. For example, an audio unit is a type of audio component
                    instance, so to use an audio unit, one finds its audio component, and then
                    creates a new instance of that component. This instance is then used to
                    perform the audio tasks for which it was designed (process, mix, synthesise,
                    etc.).
    @param          inComponent
                        the audio component (must not be NULL)
    @param          outInstance
                        the audio component instance
    @result         an OSStatus result code.
*/
extern OSStatus 
AudioComponentInstanceNew(      AudioComponent                                inComponent,
                                AudioComponentInstance __nullable * __nonnull outInstance)
                                                                            API_AVAILABLE(macos(10.6), ios(2.0), watchos(2.0), tvos(9.0));
/*!
    @function       AudioComponentInstantiate
    @abstract       Creates an audio component instance, asynchronously.
    @discussion     This is an asynchronous version of AudioComponentInstanceNew(). It must be
                    used to instantiate any component with kAudioComponentFlag_RequiresAsyncInstantiation
                    set in its component flags. It may be used for other components as well.
					
					Note: Do not block the main thread while waiting for the completion handler
					to be called; this can deadlock.
    @param          inComponent
                        the audio component
    @param          inOptions
                        see AudioComponentInstantiationOptions
    @param          inCompletionHandler
                        called in an arbitrary thread context when instantiation is complete.
*/
extern void
AudioComponentInstantiate(      AudioComponent                      inComponent,
                                AudioComponentInstantiationOptions  inOptions,
                                void (^inCompletionHandler)(AudioComponentInstance __nullable, OSStatus))
                                                                            API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

/*!
    @function       AudioComponentInstanceDispose
    @abstract       Disposes of an audio component instance.
    @discussion     This function will dispose the audio component instance that was created
                    with the New call. It will deallocate any resources that the instance was using.
    @param          inInstance
                        the audio component instance to dispose (must not be NULL)
    @result         an OSStatus result code.
*/
extern OSStatus 
AudioComponentInstanceDispose(  AudioComponentInstance          inInstance)
                                                                            API_AVAILABLE(macos(10.6), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function       AudioComponentInstanceGetComponent
    @abstract       Retrieve the audio component from its instance
    @discussion     Allows the application at any time to retrieve the audio component that is
                    the factory object of a given instance (i.e., the audio component that was
                    used to create the instance in the first place). This allows the application
                    to retrieve general information about a particular audio component (its
                    name, version, etc) when one just has an audio component instance to work
                    with
    @param          inInstance
                        the audio component instance (must not be NULL, and instance must be valid - that is, not disposed)
    @result         a valid audio component or NULL if no component was found.
*/
extern AudioComponent 
AudioComponentInstanceGetComponent (    AudioComponentInstance      inInstance)
                                                                            API_AVAILABLE(macos(10.6), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function       AudioComponentInstanceCanDo
    @discussion     Determines if an audio component instance implements a particular component
                    API call as signified by the specified selector identifier token.
    @param          inInstance
                        the audio component instance
    @param          inSelectorID
                        a number to signify the audio component API (component selector) as appropriate for the instance's component type.
    @result         a boolean
*/
extern Boolean 
AudioComponentInstanceCanDo (   AudioComponentInstance              inInstance, 
                                SInt16                              inSelectorID)
                                                                            API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/*!
    @function       AudioComponentRegister
    @abstract       Dynamically registers an AudioComponent within the current process
    @discussion
        AudioComponents are registered either when found in appropriate bundles in the filesystem,
        or via this call. AudioComponents registered via this call are available only within
        the current process.
    
    @param          inDesc
                        The AudioComponentDescription that describes the AudioComponent. Note that
                        the registrar needs to be sure to set the flag kAudioComponentFlag_SandboxSafe
                        in the componentFlags field of the AudioComponentDescription to indicate that
                        the AudioComponent can be loaded directly into a sandboxed process.
    @param          inName
                        the AudioComponent's name
    @param          inVersion
                        the AudioComponent's version
    @param          inFactory
                        an AudioComponentFactoryFunction which will create instances of your
                        AudioComponent
    @result         an AudioComponent object
*/
extern AudioComponent
AudioComponentRegister(     const AudioComponentDescription *   inDesc,
                            CFStringRef                         inName,
                            UInt32                              inVersion,
                            AudioComponentFactoryFunction       inFactory)
                                                    API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/*!
    @function       AudioComponentCopyConfigurationInfo
    @abstract       Fetches the basic configuration info about a given AudioComponent
    @discussion     Currently, only AudioUnits can supply this information.
    @param          inComponent
                        The AudioComponent whose info is being fetched.
    @param          outConfigurationInfo
                        On exit, this is CFDictionaryRef that contains information describing the
                        capabilities of the AudioComponent. The specific information depends on the
                        type of AudioComponent. The keys for the dictionary are defined in
                        AudioUnitProperties.h (or other headers as appropriate for the component type).
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
AudioComponentCopyConfigurationInfo(    AudioComponent      inComponent,
                                        CFDictionaryRef __nullable * __nonnull outConfigurationInfo)
                                                    API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
	 @enum		 AudioComponentValidationResult
	 @abstract	 Constants for describing the result of validating an AudioComponent
	 @constant	 kAudioComponentValidationResult_Passed
					The AudioComponent passed validation.
	 @constant	 kAudioComponentValidationResult_Failed
					The AudioComponent failed validation.
	 @constant	 kAudioComponentValidationResult_TimedOut
					The validation operation timed out before completing.
	 @constant	 kAudioComponentValidationResult_UnauthorizedError_Open
					The AudioComponent failed validation during open operation as it is not authorized.
	 @constant	 kAudioComponentValidationResult_UnauthorizedError_Init
					The AudioComponent failed validation during initialization as it is not authorized.
*/
typedef CF_ENUM(UInt32, AudioComponentValidationResult)
{
	kAudioComponentValidationResult_Unknown = 0,
	kAudioComponentValidationResult_Passed,
	kAudioComponentValidationResult_Failed,
	kAudioComponentValidationResult_TimedOut,
	kAudioComponentValidationResult_UnauthorizedError_Open,
	kAudioComponentValidationResult_UnauthorizedError_Init
};
	
/*!
	@define		kAudioComponentConfigurationInfo_ValidationResult
	@abstract	Dictionary that contains the AudioComponentValidationResult for the component.
	@discussion
		The keys in this dictionary are the CPU architectures (e.g. "i386") that generated each result.
*/
#define kAudioComponentConfigurationInfo_ValidationResult	"ValidationResult"
	
/*!
	@function		AudioComponentValidate
	@abstract		Tests a specified AudioComponent for API and behavioral conformance.
	@discussion	Currently, only AudioUnits can can be validated.
	@param			inComponent
						The AudioComponent to validate.
	@param			inValidationParameters
						A CFDictionaryRef that contains parameters for the validation operation.
						Passing NULL for this argument tells the system to use the default
						parameters.
	@param			outValidationResult
						On exit, this is an AudioComponentValidationResult.
	@result			an OSStatus result code.
*/
extern OSStatus
AudioComponentValidate( AudioComponent					inComponent,
						CFDictionaryRef __nullable		inValidationParameters,
						AudioComponentValidationResult *outValidationResult)
                                                    API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, watchos, tvos);
	
/*!
	@define		kAudioComponentValidationParameter_TimeOut
	@discussion This is a number that indicates the time in seconds to wait for a validation
				operation to complete. Note that if a validation operation times out, it will return
				kAudioComponentValidationResult_TimedOut as its result.
*/
#define kAudioComponentValidationParameter_TimeOut				"TimeOut"
	
/*!
	 @define	 kAudioComponentValidationParameter_ForceValidation
	 @discussion
	 	This is a bool that indicates to ignore the cached value and run validation on the specified
	 	audio unit and update the cache.
*/
#define kAudioComponentValidationParameter_ForceValidation		 "ForceValidation"


#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioUnit_AudioComponent_h
#else
#include <AudioToolboxCore/AudioComponent.h>
#endif
// ==========  AudioToolbox.framework/Headers/AUGraph.h
/*!
	@file		AUGraph.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2000-2015 by Apple, Inc., all rights reserved.
	@abstract	API's to manage graphs of AudioUnits.

	@discussion
		An AUGraph is a complete description of an audio signal processing network. The AUGraph
		API's maintain a set of AudioUnits, audio connections between their inputs and outputs, and
		any callbacks used to provide inputs. It also allows the embedding of sub-graphs within
		parent graphs to allow for a logical organization of parts of an overall signal chain. The
		graph's AudioUnits do the actual audio processing.

		The AUGraph may be introspected, in order to get complete information about all of the
		AudioUnits in the graph.  The various nodes (AUNode) in the AUGraph representing AudioUnits
		or sub graphs may be added or removed, and the interactions between them modified.

		An AUGraph's state can be manipulated in both the rendering thread and in other threads.
		Consequently, any activities that affect the state of the graph are guarded with locks and a
		messaging model between any calling thread and the thread upon which the AUGraph's output
		unit is called (the render thread).

		An AUGraph will have a single head node - what is referred to below as its output unit. The
		output unit is used to both start and stop the rendering operations of a graph, and as the
		dispatch point for the safe manipulation of the state of the graph while it is running.
*/

#ifndef AudioToolbox_AUGraph_h
#define AudioToolbox_AUGraph_h

#include <AudioToolbox/AudioUnit.h>

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

#define AUGRAPH_DEPRECATED(macos_intro) API_DEPRECATED("AUGraph is deprecated in favor of AVAudioEngine", macos(macos_intro, API_TO_BE_DEPRECATED), ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED))

/*!
	@typedef	AUGraph
	@abstract	A reference to an AUGraph object.
*/
typedef	struct OpaqueAUGraph	*AUGraph;

/*!
	@typedef	AUNode
	@abstract	Used to represent a member of an AUGraph
*/
typedef SInt32 	AUNode;

/*!
    @enum AUGraph error codes
    @abstract   These are the error codes returned from the AUGraph API.
    @constant   kAUGraphErr_NodeNotFound
				The specified node cannot be found
	@constant	kAUGraphErr_InvalidConnection
				The attempted connection between two nodes cannot be made
	@constant	kAUGraphErr_OutputNodeErr
				AUGraphs can only contain one OutputUnit.
				this error is returned if trying to add a second output unit
				or the graph's output unit is removed while the graph is running
	@constant	kAUGraphErr_CannotDoInCurrentContext
				To avoid spinning or waiting in the render thread (a bad idea!), many of the
				calls to AUGraph can return: kAUGraphErr_CannotDoInCurrentContext. This
				result is only generated when you call an AUGraph API from its render
				callback. It means that the lock that it required was held at that time, by
				another thread. If you see this result code, you can generally attempt the
				action again - typically the NEXT render cycle (so in the mean time the lock
				can be cleared), or you can delegate that call to another thread in your
				app. You should not spin or put-to-sleep the render thread.

	@constant	kAUGraphErr_InvalidAudioUnit
*/
CF_ENUM(OSStatus)
{
	kAUGraphErr_NodeNotFound 				= -10860,
	kAUGraphErr_InvalidConnection 			= -10861,
	kAUGraphErr_OutputNodeErr				= -10862,
	kAUGraphErr_CannotDoInCurrentContext	= -10863,
	kAUGraphErr_InvalidAudioUnit			= -10864
};

#pragma mark -
/*!
    @function	NewAUGraph
    @abstract   creates a new AUGraph
    @discussion	creates a new AUGraph
    @param		outGraph		the new AUGraph object
*/
extern OSStatus
NewAUGraph(			AUGraph	__nullable * __nonnull outGraph)		AUGRAPH_DEPRECATED(10.0);

/*!
    @function	DisposeAUGraph
    @abstract   dispose an AUGraph
    @discussion	deallocates the AUGraph along with its nodes and their resources.
    @param		inGraph		the AUGraph object to be disposed
*/
extern OSStatus
DisposeAUGraph(		AUGraph			inGraph)						AUGRAPH_DEPRECATED(10.0);


#pragma mark -
#pragma mark Node State
/*! 
	@functiongroup AU Node management
*/

/*!
    @function	AUGraphAddNode
    @abstract   Add a node to an AUGraph
    @discussion	This creates a node in the graph that is an AudioUnit, using the supplied
				AudioComponentDescription to find and open that unit.
    @param		inGraph			the AUGraph object
    @param		inDescription	the AudioComponentDescription used to find and open the AudioUnit
    @param		outNode			the newly added node
*/
extern OSStatus
AUGraphAddNode(		AUGraph								inGraph,
					const AudioComponentDescription	*	inDescription,
					AUNode *	  						outNode)	AUGRAPH_DEPRECATED(10.5);

/*!
    @function	AUGraphRemoveNode
    @abstract   Remove a node from an AUGraph
    @discussion	Nodes can be removed from any thread context. The output node of
				the AUGraph cannot be removed while the graph is running.
    @param		inGraph			the AUGraph object
    @param		inNode			the node to be removed
*/
extern OSStatus
AUGraphRemoveNode(  AUGraph			inGraph,
					AUNode			inNode)							AUGRAPH_DEPRECATED(10.0);

/*!
    @function	AUGraphGetNodeCount
    @abstract   The number of nodes in an AUGraph
    @discussion	The number of nodes in an AUGraph
    @param		inGraph				the AUGraph object
    @param		outNumberOfNodes	the number of nodes
*/
extern OSStatus
AUGraphGetNodeCount(AUGraph			inGraph,
					UInt32 			*outNumberOfNodes)				AUGRAPH_DEPRECATED(10.0);

/*!
    @function	AUGraphGetIndNode
    @abstract   Returns the node at a given index
    @discussion	By using AUGraphGetNodeCount in conjunction with this call, you can
				iterate through the nodes of an AUGraph.
    @param		inGraph				the AUGraph object
    @param		inIndex				the index of the node to retrieve
	@param		outNode				the node at that index
*/
extern OSStatus
AUGraphGetIndNode(  AUGraph			inGraph,
					UInt32 			inIndex,
					AUNode			*outNode)						AUGRAPH_DEPRECATED(10.0);

/*!
    @function	AUGraphNodeInfo
    @abstract   Returns information about a particular AUNode
    @discussion	You can pass in NULL for any of the out parameters if you're not interested
				in that value.
    @param		inGraph				the AUGraph object
	@param		inNode				the node to query
    @param		outDescription		the component description that would describe the AudioUnit of this node
	@param		outAudioUnit		the AudioUnit of this node
*/
extern OSStatus
AUGraphNodeInfo(	AUGraph									inGraph,
					AUNode									inNode,
					AudioComponentDescription * __nullable	outDescription,
					AudioUnit __nullable * __nullable		outAudioUnit)		AUGRAPH_DEPRECATED(10.5);
			

#if !TARGET_OS_IPHONE
#pragma mark -
#pragma mark Sub Graphs
/*! 
	@functiongroup Sub Graph Nodes
*/
/*!
    @function	AUGraphNewNodeSubGraph
    @abstract   Create a node that will represent a sub graph
	@discussion	This will create a node that represents a contained or member AUGraph.
				The AUGraph can be retrieved through the GetNodeInfoSubGraph call.
				The member AUGraph is owned by the parent graph and will be disposed when
				either:
				(1) The parent graph is disposed
				(2) The node is removed from the parent AUGraph
    @param		inGraph				the AUGraph object
	@param		outNode				the node that is used to refer to the sub-graph
*/
extern OSStatus
AUGraphNewNodeSubGraph( AUGraph				inGraph,
						AUNode				*outNode)			API_DEPRECATED("no longer supported", macos(10.2, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
    @function	AUGraphGetNodeInfoSubGraph
    @abstract   Return an AUGraph represented by this node
	@discussion	This will return the sub graph represented by this AUNode.
    @param		inGraph				the AUGraph object
	@param		inNode				the node to query
	@param		outSubGraph			the sub-graph
*/
extern OSStatus
AUGraphGetNodeInfoSubGraph(	const AUGraph		inGraph,
							AUNode				inNode,
							AUGraph	__nullable * __nonnull outSubGraph)	API_DEPRECATED("no longer supported", macos(10.2, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos);
								
/*!
    @function	AUGraphIsNodeSubGraph
    @abstract   Does the node represent a sub graph
	@discussion	This will return true if the specified node represents a subgraph, false if not.
    @param		inGraph				the AUGraph object
	@param		inNode				the node to query
	@param		outFlag				true if the node is a subgraph, false if not
*/
extern OSStatus
AUGraphIsNodeSubGraph(		const AUGraph		inGraph,
							AUNode				inNode,
							Boolean *			outFlag)		API_DEPRECATED("no longer supported", macos(10.2, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos);

#endif // !TARGET_OS_IPHONE

#pragma mark -
#pragma mark Node Interactions
/*! 
	@functiongroup Node Interactions
*/
/*! 
	@enum
	@abstract	The different types of node interactions
	@discussion We use the term interaction as a general term to describe some interaction 
				of a node. Currently, the interactions of a node that the graph manages are
				described below.
	@constant	kAUNodeInteraction_Connection
				connections between 2 audio units, 
	@constant	kAUNodeInteraction_InputCallback
				input callbacks being registered to a single audio unit's input bus.
*/
CF_ENUM(UInt32) {
	kAUNodeInteraction_Connection		= 1,
	kAUNodeInteraction_InputCallback	= 2
};

/*! 
	@struct		AudioUnitNodeConnection
	@abstract	A connection between two nodes
	@var  		sourceNode
	@var  		sourceOutputNumber
	@var  		destNode
	@var  		destInputNumber
*/
struct AudioUnitNodeConnection
{
	AUNode		sourceNode;
	UInt32		sourceOutputNumber;
	AUNode		destNode;
	UInt32		destInputNumber;
};
typedef struct AudioUnitNodeConnection AudioUnitNodeConnection;
typedef struct AudioUnitNodeConnection AUNodeConnection;

/*! 
	@struct		AUNodeRenderCallback
	@abstract	A callback used to provide input to an audio unit
	@discussion	Used to contain information when a callback is used
				to provide input to the specific node's specified input
	@var  		destNode
	@var  		destInputNumber
	@var  		cback
*/
struct AUNodeRenderCallback 
{
	AUNode					destNode;
	AudioUnitElement		destInputNumber;
	AURenderCallbackStruct	cback;
};
typedef struct AUNodeRenderCallback AUNodeRenderCallback;

/*! 
	@struct		AUNodeInteraction
	@abstract	Used to describe the interaction between/with a node
	@discussion	This structure contains information about the interaction between
				two nodes (in the case of a connection), or the input to a node
				(in the case of a callback). 
				
				The type of the interaction is used to determine how to interpret the contents 
				of the following union.

				There may be other nodal interactions in the future, so NO ASSUMPTIONS should be made
				that these are the only 2 nodal interaction types; you must always check the 
				nodeInteractionType and only act on those types you understand
	
				Arrays of these structs can be returned, the addition of new members to the
				nodeInteraction union will NOT change the size of this structure
				
	@var  		nodeInteractionType		the interaction type
	@var  		nodeInteraction			a union providing information about the specified interaction
*/
struct AUNodeInteraction
{
	UInt32		nodeInteractionType;
	
	union
	{
		AUNodeConnection		connection;		
		AUNodeRenderCallback	inputCallback;

	}			nodeInteraction;
};
typedef struct AUNodeInteraction AUNodeInteraction;

/*! 
	@function	AUGraphConnectNodeInput
	@abstract	connect a node's output to a node's input
*/
extern OSStatus
AUGraphConnectNodeInput(	AUGraph			inGraph,
							AUNode			inSourceNode,
							UInt32			inSourceOutputNumber,
							AUNode			inDestNode,
							UInt32			inDestInputNumber)		AUGRAPH_DEPRECATED(10.0);

/*! 
	@function	AUGraphSetNodeInputCallback
	@abstract	Set a callback for the specified node's specified input.
	@param		inInputCallback		The callback that will provide input data to the node
*/
extern OSStatus
AUGraphSetNodeInputCallback (AUGraph						inGraph,
							AUNode							inDestNode,
							UInt32							inDestInputNumber,
							const AURenderCallbackStruct *	inInputCallback) 
																	AUGRAPH_DEPRECATED(10.5);

/*! 
	@function	AUGraphDisconnectNodeInput
	@abstract	disconnect a node's input
	@discussion	This can be used to disconnect either a connection or callback interaction
				to the specified node input
*/
extern OSStatus
AUGraphDisconnectNodeInput(	AUGraph			inGraph,
							AUNode			inDestNode,
							UInt32			inDestInputNumber)		AUGRAPH_DEPRECATED(10.0);

/*! 
	@function	AUGraphClearConnections
	@abstract	clear all of the interactions in a graph
	@discussion	This will clear all connections and callback interactions of the nodes of a graph
*/
extern OSStatus
AUGraphClearConnections(	AUGraph			inGraph)				AUGRAPH_DEPRECATED(10.0);

/*! 
	@function	AUGraphGetNumberOfInteractions
	@abstract	Retrieve the number of interactions of a graph
	@discussion	The number of node interactions currently being managed by the graph
*/
extern OSStatus
AUGraphGetNumberOfInteractions(	AUGraph				inGraph,
								UInt32 *			outNumInteractions)	AUGRAPH_DEPRECATED(10.5);

/*! 
	@function	AUGraphGetInteractionInfo
	@abstract	Retrieve information about a particular interaction in a graph
	@discussion	Returns information about a particular interaction. 
				inInteractionIndex is based on the outNumInteractions value and is only valid if no 
				edits to the graph's state have been made.
				
				An app can iterate through the interactions (as with the nodes) of a graph by retrieving
				the number of interactions, and then iterating an index from 0 < numInteractions
	@param		outInteraction		the interaction information at the specified index
*/
extern OSStatus
AUGraphGetInteractionInfo(	AUGraph					inGraph,
							UInt32					inInteractionIndex,
							AUNodeInteraction *		outInteraction)		AUGRAPH_DEPRECATED(10.5);

/*! 
	@function	AUGraphCountNodeInteractions
	@abstract	Retrieve the number of interactions of a graph's node
	@discussion	The number of node interactions currently being managed by the graph for the specified node
*/
extern OSStatus
AUGraphCountNodeInteractions(	AUGraph				inGraph,
								AUNode				inNode,
								UInt32 *			outNumInteractions)	AUGRAPH_DEPRECATED(10.5);

/*! 
	@function	AUGraphGetNodeInteractions
	@abstract	Retrieve information about the interactions in a graph for a given node
	@discussion	Retrieve information about the interactions in a graph for a given node 
	@param		ioNumInteractions	
					on input, specifies the number of interactions that can be returned
					on output, specifies the number of interactions returned.
	@param		outInteractions		the interactions the specified node is involved in
*/
extern OSStatus
AUGraphGetNodeInteractions(	AUGraph					inGraph,
							AUNode					inNode,
							UInt32 *				ioNumInteractions,
							AUNodeInteraction *		outInteractions)	AUGRAPH_DEPRECATED(10.5);



#pragma mark -
/*! 
	@functiongroup Updating an AUGraph
*/
/*! 
	@function	AUGraphUpdate
	@abstract	Updates the state of a running AUGraph
	
	@discussion
	Call this after performing a series of "edits" on the AUGraph with calls 
	such as AUGraphConnectNodeInput() to finalize those edits.
	The call will be synchronous if outIsUpdated is NULL, 
	meaning it will block until the changes are incorporated
	into the graph OR an error is returned from the update process
	if outIsUpdated is non-NULL, then AUGraphUpdate() will return 
	immediately and outIsUpdated will equal "true" if the changes 
	were already made (no more changes to make) or "false" if changes are still
	outstanding.

	Calling from the AUGraphRenderNotification callback:
	Connection and Disconnection events can be completely processed
	in the render notification callback of the AUGraph
	Nodes can also be removed (except for the output node or a sub-graph of the AUGraph)
	as well. 

	Getting kAUGraphErr_CannotDoInCurrentContext as a result code:
	If AUGraphUpdate returns this result, then it means it was
	unable to process the update, due to an inability to safely
	alter the state of the graph (because another thread was accessing
	a call that relies on the graph's state having integrity).
	This result code is only a transitory state, which will pass as soon
	as your other thread's call to AUGraph (that has the lock) completes.

	If an error is encountered in the process of an update (say an invalid connection
	is attempted, a disconnection between nodes that are not connected, etc) on a running graph, 	
	then the call will return that error code. It only process events whilst it receives
	no error results. Thus, if an error is encountered, other events will not be
	processed until AUGraphUpdate is called again. This is done, in cases where
	the state of the graph could become inconsistent if further events were processed, so
	this decision is left up to you. The same applies to the "cant do" error - you have
	to explicitly call AUGraphUpdate again to have the processing of the events occur.

	@param		outIsUpdated	if specified returns true if all of the edits were applied to the graph
*/
extern OSStatus
AUGraphUpdate(		AUGraph					inGraph,
					Boolean	 * __nullable	outIsUpdated)			AUGRAPH_DEPRECATED(10.0);

#pragma mark -
#pragma mark State Management
/*! 
	@functiongroup AUGraph state management
*/
/*!
	@function	AUGraphOpen
	@abstract	Open a graph
	@discussion AudioUnits are open but not initialized (no resource allocation occurs here)
*/
extern OSStatus
AUGraphOpen(			AUGraph		inGraph)						AUGRAPH_DEPRECATED(10.0);

/*!
	@function	AUGraphClose
	@abstract	Close a graph
	@discussion all AudioUnits are closed - leaving only its nodal representation
*/
extern OSStatus
AUGraphClose(			AUGraph		inGraph)						AUGRAPH_DEPRECATED(10.0);

/*!
	@function	AUGraphInitialize
	@abstract	Initialise a graph
	@discussion AudioUnitInitialize() is called on each opened node/AudioUnit
				(get ready to render) and SubGraph that are involved in a
				interaction. If the node is not involved, it is initialised
				after it becomes involved in an interaction.
				
				A graph must be opened before it can be initialised.
*/
extern OSStatus
AUGraphInitialize(		AUGraph		inGraph)						AUGRAPH_DEPRECATED(10.0);

/*!
	@function	AUGraphUninitialize
	@abstract	Uninitialise a graph
	@discussion The member of the graph are uninitialised 
*/
extern OSStatus
AUGraphUninitialize(	AUGraph		inGraph)						AUGRAPH_DEPRECATED(10.0);

/*!
	@function	AUGraphStart
	@abstract	Start a graph
	@discussion Start() is called on the "head" node(s) of the AUGraph	(now rendering starts) 
				
				The graph must be initialised before it can be started
*/
extern OSStatus
AUGraphStart(			AUGraph		inGraph)						AUGRAPH_DEPRECATED(10.0);

/*!
	@function	AUGraphStop
	@abstract	Stop a graph
	@discussion Stop() is called on the "head" node(s) of the AUGraph	(rendering is stopped)
*/
extern OSStatus
AUGraphStop(			AUGraph		inGraph)						AUGRAPH_DEPRECATED(10.0);


/*!
	@function	AUGraphIsOpen
	@abstract	Is the graph open
*/
extern OSStatus
AUGraphIsOpen(			AUGraph		inGraph,
						Boolean		*outIsOpen)						AUGRAPH_DEPRECATED(10.0);
							
/*!
	@function	AUGraphIsInitialized
	@abstract	Is the graph initialised
*/
extern OSStatus
AUGraphIsInitialized(	AUGraph		inGraph,
						Boolean		*outIsInitialized)				AUGRAPH_DEPRECATED(10.0);
							
/*!
	@function	AUGraphIsRunning
	@abstract	Is the graph running (has it been started)
*/
extern OSStatus
AUGraphIsRunning(		AUGraph		inGraph,
						Boolean		*outIsRunning)					AUGRAPH_DEPRECATED(10.0);
						
#pragma mark -
#pragma mark Utilities
/*! 
	@functiongroup AUGraph utilities
*/
/*!
	@function	AUGraphGetCPULoad
	@abstract	The CPU load of the graph
	@discussion	Returns a short-term running average of the current CPU load
				of the graph.		
*/
extern OSStatus
AUGraphGetCPULoad(		AUGraph		inGraph,
						Float32		*outAverageCPULoad)				AUGRAPH_DEPRECATED(10.1);

/*!
	@function	AUGraphGetMaxCPULoad
	@abstract	The Maximum CPU load of the graph
	@discussion	Returns the max CPU load of the graph since this call was last made 
				or the graph was last started.
*/
extern OSStatus
AUGraphGetMaxCPULoad(	AUGraph		inGraph,
						Float32		*outMaxLoad)					AUGRAPH_DEPRECATED(10.3);

/*!
	@function	AUGraphAddRenderNotify
	@abstract	Add a notification callback
	@discussion	Add a callback that the graph will call every time the
				graph renders. The callback will be called once before the graph's render
				operation, and once after the render operation is complete.
*/
extern OSStatus
AUGraphAddRenderNotify(			AUGraph					inGraph,
								AURenderCallback 		inCallback,
								void * __nullable		inRefCon)		AUGRAPH_DEPRECATED(10.2);

/*!
	@function	AUGraphRemoveRenderNotify
	@abstract	Remove a notification callback
	@discussion	Remove a previously added callback. You must provide both the callback
				and the refCon that was used previously to add the callback.
*/
extern OSStatus
AUGraphRemoveRenderNotify(		AUGraph					inGraph,
								AURenderCallback 		inCallback,
								void * __nullable		inRefCon)		AUGRAPH_DEPRECATED(10.2);
	
#pragma mark -
#pragma mark Deprecated

#if !TARGET_OS_IPHONE
struct ComponentDescription;
/*!
	@function			AUGraphNewNode
	@discussion		ClassInfo data should not be used with new nodes
	@deprecated	in 10.5, see AUGraphAddNode
*/
extern OSStatus
AUGraphNewNode(	AUGraph								inGraph,
				const struct ComponentDescription	*inDescription,
				UInt32								inClassDataSize,	// reserved: must be zero
				const void							*inClassData,
				AUNode								*outNode)			API_DEPRECATED("no longer supported", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);


/*!
	@function	AUGraphGetNodeInfo
	@discussion		ClassInfo data should not be used with new nodes
	@deprecated	in 10.5, see AUGraphNodeInfo
*/
extern OSStatus
AUGraphGetNodeInfo(	AUGraph						inGraph,
					AUNode						inNode,
					struct ComponentDescription *outDescription,
					UInt32						*outClassDataSize,
					void * __nullable * __nullable outClassData,
					AudioUnit __nullable * __nullable outAudioUnit)		API_DEPRECATED("no longer supported", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
	@function			AUGraphGetNumberOfConnections
	@deprecated	in 10.5, see AUGraphGetNumberOfInteractions
*/
extern OSStatus
AUGraphGetNumberOfConnections(	AUGraph		inGraph,
								UInt32		*outNumConnections)		API_DEPRECATED("no longer supported", macos(10.1, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
	@function			AUGraphGetConnectionInfo
	@deprecated	in 10.5, see AUGraphGetInteractionInfo
*/
extern OSStatus
AUGraphGetConnectionInfo(	AUGraph		inGraph,
							UInt32		inConnectionIndex,
							AUNode		*outSourceNode,
							UInt32		*outSourceOutputNumber,
							AUNode		*outDestNode,
							UInt32		*outDestInputNumber)		API_DEPRECATED("no longer supported", macos(10.1, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
	@function			AUGraphCountNodeConnections
	@deprecated	in 10.5, see AUGraphCountNodeInteractions
*/
extern OSStatus
AUGraphCountNodeConnections(	AUGraph 	inGraph,
								AUNode 		inNode,
								UInt32 		*outNumConnections)		API_DEPRECATED("no longer supported", macos(10.3, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
	@function			AUGraphGetNodeConnections
	@deprecated	in 10.5, see AUGraphGetNodeInteractions
*/
extern OSStatus
AUGraphGetNodeConnections(		AUGraph						inGraph,
								AUNode						inNode,
								AudioUnitNodeConnection		*outConnections,
								UInt32						*ioNumConnections)	
																	API_DEPRECATED("no longer supported", macos(10.3, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);

#endif //!TARGET_OS_IPHONE
	
#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AUGraph_h


// ==========  AudioToolbox.framework/Headers/ExtendedAudioFile.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/ExtendedAudioFile.h>)
/*!
	@file		ExtendedAudioFile.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2004-2015 by Apple, Inc., all rights reserved.
	@abstract	API's to support reading and writing files in encoded audio formats.

	@discussion

				The ExtendedAudioFile provides high-level audio file access, building
				on top of the AudioFile and AudioConverter API sets. It provides a single
				unified interface to reading and writing both encoded and unencoded files.
*/

#ifndef AudioToolbox_ExtendedAudioFile_h
#define AudioToolbox_ExtendedAudioFile_h

#include <Availability.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AudioToolbox/AudioFile.h>

#ifdef __cplusplus
extern "C" {
#endif

CF_ASSUME_NONNULL_BEGIN

//==================================================================================================
//	Types

/*!
	@typedef	ExtAudioFileRef
	@abstract   An extended audio file object.
*/
typedef struct OpaqueExtAudioFile *	ExtAudioFileRef;


//==================================================================================================
//	Properties

typedef UInt32						ExtAudioFilePropertyID;
/*!
    @enum           ExtAudioFilePropertyID
    @constant       kExtAudioFileProperty_FileDataFormat
                        An AudioStreamBasicDescription. Represents the file's actual
						data format. Read-only.
	@constant		kExtAudioFileProperty_FileChannelLayout
						An AudioChannelLayout.

						If writing: the channel layout is written to the file, if the format
						supports the layout. If the format does not support the layout, the channel
						layout is still interpreted as the destination layout when performing
						conversion from the client channel layout, if any.

						If reading: the specified layout overrides the one read from the file, if
						any.

						When setting this, it must be set before the client format or channel
						layout.
	@constant		kExtAudioFileProperty_ClientDataFormat
						An AudioStreamBasicDescription.

						The format must be linear PCM (kAudioFormatLinearPCM).

						You must set this in order to encode or decode a non-PCM file data format.
						You may set this on PCM files to specify the data format used in your calls
						to read/write.
	@constant		kExtAudioFileProperty_ClientChannelLayout
						An AudioChannelLayout. Specifies the channel layout of the
						AudioBufferList's passed to ExtAudioFileRead() and
						ExtAudioFileWrite(). The layout may be different from the file's
						channel layout, in which the ExtAudioFileRef's underlying AudioConverter
						performs the remapping. This must be set after ClientDataFormat, and the
						number of channels in the layout must match.
	@constant		kExtAudioFileProperty_CodecManufacturer
						A UInt32 specifying the manufacturer of the codec to be used. This must be 
						specified before setting kExtAudioFileProperty_ClientDataFormat, which
						triggers the creation of the codec. This can be used on iOS
						to choose between a hardware or software encoder, by specifying 
						kAppleHardwareAudioCodecManufacturer or kAppleSoftwareAudioCodecManufacturer.
						
						Available starting on Mac OS X version 10.7 and iOS version 4.0.
	@constant		kExtAudioFileProperty_AudioConverter
						AudioConverterRef. The underlying AudioConverterRef, if any. Read-only.
						
						Note: If you alter any properties of the AudioConverterRef, for example,
						an encoder's bit rate, you must set the kExtAudioFileProperty_ConverterConfig
						property on the ExtAudioFileRef afterwards. A NULL configuration is 
						sufficient. This will ensure that the output file's data format is consistent
						with the format being produced by the converter.
						
						<pre>
							CFArrayRef config = NULL;
							err = ExtAudioFileSetProperty(myExtAF, kExtAudioFileProperty_ConverterConfig, 
							  sizeof(config), &config);
						</pre>
	@constant		kExtAudioFileProperty_AudioFile
						The underlying AudioFileID. Read-only.
	@constant		kExtAudioFileProperty_FileMaxPacketSize
						UInt32 representing the file data format's maximum packet size in bytes.
						Read-only.
	@constant		kExtAudioFileProperty_ClientMaxPacketSize
						UInt32 representing the client data format's maximum packet size in bytes.
						Read-only.
	@constant		kExtAudioFileProperty_FileLengthFrames
						SInt64 representing the file's length in sample frames. Read-only on 
						non-PCM formats; writable for files in PCM formats.
	@constant		kExtAudioFileProperty_ConverterConfig
						CFArrayRef representing the underlying AudioConverter's configuration, as
						specified by kAudioConverterPropertySettings.
						
						This may be NULL to force resynchronization of the converter's output format
						with the file's data format.
	@constant		kExtAudioFileProperty_IOBufferSizeBytes
						UInt32 representing the size of the buffer through which the converter
						reads/writes the audio file (when there is an AudioConverter).
	@constant		kExtAudioFileProperty_IOBuffer
						void *. This is the memory buffer which the ExtAudioFileRef will use for
						disk I/O when there is a conversion between the client and file data
						formats. A client may be able to share buffers between multiple
						ExtAudioFileRef instances, in which case, it can set this property to point
						to its own buffer. After setting this property, the client must
						subsequently set the kExtAudioFileProperty_IOBufferSizeBytes property. Note
						that a pointer to a pointer should be passed to ExtAudioFileSetProperty.
	@constant		kExtAudioFileProperty_PacketTable
						This AudioFilePacketTableInfo can be used to both override the priming and
						remainder information in an audio file and to retrieve the current priming
						and remainder frames information for a given ExtAudioFile object. If the
						underlying file type does not provide packet table info, the Get call will
						return an error.
						
						If you set this, then you can override the setting for these values in the
						file to ones that you want to use. When setting this, you can use a value of
						-1 for either the priming or remainder frames to use the value that is
						currently stored in the file. If you set this to a non-negative number (or
						zero) then that value will override whatever value is stored in the file
						that you are reading. Retrieving the value of the property will always
						retrieve the value the ExtAudioFile object is using (whether this is derived
						from the file, or from your override). If you want to determine what the
						value is in the file, you should use the AudioFile property:
						kAudioFilePropertyPacketTableInfo

						When the property is set, only the remaining and priming values are used.
						You should set the mNumberValidFrames to zero.

						For example, a file encoded using AAC may have 2112 samples of priming at
						the start of the file and a remainder of 823 samples at the end. When
						ExtAudioFile returns decoded samples to you, it will trim `mPrimingFrames`
						at the start of the file, and `mRemainderFrames` at the end. It will get
						these numbers initially from the file. A common use case for overriding this
						would be to set the priming and remainder samples to 0, so in this example
						you would retrieve an additional 2112 samples of silence from the start of
						the file and 823 samples of silence at the end of the file (silence, because
						the encoders use silence to pad out these priming and remainder samples)
*/
CF_ENUM(ExtAudioFilePropertyID) {
	kExtAudioFileProperty_FileDataFormat		= 'ffmt',   // AudioStreamBasicDescription
	kExtAudioFileProperty_FileChannelLayout		= 'fclo',   // AudioChannelLayout
	kExtAudioFileProperty_ClientDataFormat		= 'cfmt',   // AudioStreamBasicDescription
	kExtAudioFileProperty_ClientChannelLayout	= 'cclo',   // AudioChannelLayout
	kExtAudioFileProperty_CodecManufacturer		= 'cman',	// UInt32
	
	// read-only:
	kExtAudioFileProperty_AudioConverter		= 'acnv',	// AudioConverterRef
	kExtAudioFileProperty_AudioFile				= 'afil',	// AudioFileID
	kExtAudioFileProperty_FileMaxPacketSize		= 'fmps',	// UInt32
	kExtAudioFileProperty_ClientMaxPacketSize	= 'cmps',	// UInt32
	kExtAudioFileProperty_FileLengthFrames		= '#frm',	// SInt64
	
	// writable:
	kExtAudioFileProperty_ConverterConfig		= 'accf',   // CFPropertyListRef
	kExtAudioFileProperty_IOBufferSizeBytes		= 'iobs',	// UInt32
	kExtAudioFileProperty_IOBuffer				= 'iobf',	// void *
	kExtAudioFileProperty_PacketTable			= 'xpti'	// AudioFilePacketTableInfo
};

CF_ENUM(OSStatus) {
	kExtAudioFileError_InvalidProperty			= -66561,
	kExtAudioFileError_InvalidPropertySize		= -66562,
	kExtAudioFileError_NonPCMClientFormat		= -66563,
	kExtAudioFileError_InvalidChannelMap		= -66564,	// number of channels doesn't match format
	kExtAudioFileError_InvalidOperationOrder	= -66565,
	kExtAudioFileError_InvalidDataFormat		= -66566,
	kExtAudioFileError_MaxPacketSizeUnknown		= -66567,
	kExtAudioFileError_InvalidSeek				= -66568,	// writing, or offset out of bounds
	kExtAudioFileError_AsyncWriteTooLarge		= -66569,
	kExtAudioFileError_AsyncWriteBufferOverflow	= -66570	// an async write could not be completed in time
};

#if TARGET_OS_IPHONE
/*!
    @enum           ExtAudioFile errors
    @constant       kExtAudioFileError_CodecUnavailableInputConsumed
						iOS only. Returned when ExtAudioFileWrite was interrupted. You must stop calling
						ExtAudioFileWrite. If the underlying audio converter can resume after an
						interruption (see kAudioConverterPropertyCanResumeFromInterruption), you must
						wait for an EndInterruption notification from AudioSession, and call AudioSessionSetActive(true)
						before resuming. In this situation, the buffer you provided to ExtAudioFileWrite was successfully
						consumed and you may proceed to the next buffer.
    @constant       kExtAudioFileError_CodecUnavailableInputNotConsumed
						iOS only. Returned when ExtAudioFileWrite was interrupted. You must stop calling
						ExtAudioFileWrite. If the underlying audio converter can resume after an
						interruption (see kAudioConverterPropertyCanResumeFromInterruption), you must
						wait for an EndInterruption notification from AudioSession, and call AudioSessionSetActive(true)
						before resuming. In this situation, the buffer you provided to ExtAudioFileWrite was not
						successfully consumed and you must try to write it again.
*/
CF_ENUM(OSStatus) {
	kExtAudioFileError_CodecUnavailableInputConsumed    = -66559,
	kExtAudioFileError_CodecUnavailableInputNotConsumed = -66560,
};
#endif


//==================================================================================================
//	Creation/Destruction
/*!
    @functiongroup  Creation/Destruction
*/

/*!
	@function   ExtAudioFileOpenURL
	
	@abstract   Opens an audio file specified by a CFURLRef.
	@param		inURL
					The audio file to read.
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Allocates a new ExtAudioFileRef, for reading an existing audio file.
*/
extern OSStatus
ExtAudioFileOpenURL(		CFURLRef 					inURL,
							ExtAudioFileRef __nullable * __nonnull outExtAudioFile)	API_AVAILABLE(macos(10.5), ios(2.1), watchos(2.0), tvos(9.0));

/*!
	@function   ExtAudioFileWrapAudioFileID
	
	@abstract   Wrap an AudioFileID in an ExtAudioFileRef.
	@param		inFileID
					The AudioFileID to wrap.
	@param		inForWriting
					True if the AudioFileID is a new file opened for writing.
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Allocates a new ExtAudioFileRef which wraps an existing AudioFileID. The
				client is responsible for keeping the AudioFileID open until the
				ExtAudioFileRef is disposed. Disposing the ExtAudioFileRef will not close
				the AudioFileID when this Wrap API call is used, so the client is also
				responsible for closing the AudioFileID when finished with it.
*/
extern OSStatus
ExtAudioFileWrapAudioFileID(AudioFileID					inFileID,
							Boolean						inForWriting,
							ExtAudioFileRef __nullable * __nonnull outExtAudioFile)
																			API_AVAILABLE(macos(10.4), ios(2.1), watchos(2.0), tvos(9.0));

/*!
	@function   ExtAudioFileCreateWithURL
	
	@abstract   Create a new audio file.
	@param		inURL
					The URL of the new audio file.
	@param		inFileType
					The type of file to create. This is a constant from AudioToolbox/AudioFile.h, e.g.
					kAudioFileAIFFType. Note that this is not an HFSTypeCode.
	@param		inStreamDesc
					The format of the audio data to be written to the file.
	@param		inChannelLayout
					The channel layout of the audio data. If non-null, this must be consistent
					with the number of channels specified by inStreamDesc.
	@param		inFlags
					The same flags as are used with AudioFileCreateWithURL
					Can use these to control whether an existing file is overwritten (or not).
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Creates a new audio file.
				
				If the file to be created is in an encoded format, it is permissible for the
				sample rate in inStreamDesc to be 0, since in all cases, the file's encoding
				AudioConverter may produce audio at a different sample rate than the source. The
				file will be created with the audio format actually produced by the encoder.
*/
extern OSStatus
ExtAudioFileCreateWithURL(	CFURLRef							inURL,
							AudioFileTypeID						inFileType,
							const AudioStreamBasicDescription * inStreamDesc,
							const AudioChannelLayout * __nullable inChannelLayout,
                    		UInt32								inFlags,
							ExtAudioFileRef __nullable * __nonnull outExtAudioFile)
																			API_AVAILABLE(macos(10.5), ios(2.1), watchos(2.0), tvos(9.0));
																			
#if !TARGET_OS_IPHONE
/*!
	@function   ExtAudioFileOpen
	
	@abstract   Opens an audio file specified by an FSRef.
	@param		inFSRef
					The audio file to read.
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Allocates a new ExtAudioFileRef, for reading an existing audio file.
				
				This function is deprecated as of Mac OS 10.6. ExtAudioFileOpenURL is preferred.
*/
extern OSStatus
ExtAudioFileOpen(			const struct FSRef *		inFSRef,
							ExtAudioFileRef __nullable * __nonnull outExtAudioFile)	API_DEPRECATED("no longer supported", macos(10.4, 10.6)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
	@function   ExtAudioFileCreateNew
	
	@abstract   Creates a new audio file.
	@param		inParentDir
					The directory in which to create the new file.
	@param		inFileName
					The name of the new file.
	@param		inFileType
					The type of file to create. This is a constant from AudioToolbox/AudioFile.h, e.g.
					kAudioFileAIFFType. Note that this is not an HFSTypeCode.
	@param		inStreamDesc
					The format of the audio data to be written to the file.
	@param		inChannelLayout
					The channel layout of the audio data. If non-null, this must be consistent
					with the number of channels specified by inStreamDesc.
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				If the file to be created is in an encoded format, it is permissible for the
				sample rate in inStreamDesc to be 0, since in all cases, the file's encoding
				AudioConverter may produce audio at a different sample rate than the source. The
				file will be created with the audio format actually produced by the encoder.

				This function is deprecated as of Mac OS 10.6. ExtAudioFileCreateWithURL is preferred.
*/
extern OSStatus
ExtAudioFileCreateNew(		const struct FSRef *				inParentDir,
							CFStringRef							inFileName,
							AudioFileTypeID						inFileType,
							const AudioStreamBasicDescription * inStreamDesc,
							const AudioChannelLayout * __nullable inChannelLayout,
							ExtAudioFileRef __nullable * __nonnull outExtAudioFile)
																			API_DEPRECATED("no longer supported", macos(10.4, 10.6)) API_UNAVAILABLE(ios, watchos, tvos);
#endif

/*!
	@function   ExtAudioFileDispose
	
	@abstract   Close the file and dispose the object.
	@param		inExtAudioFile
					The extended audio file object.
	@result		An OSStatus error code.
	
	@discussion
				Closes the file and deletes the object.
*/
extern OSStatus
ExtAudioFileDispose(		ExtAudioFileRef				inExtAudioFile)		
																			API_AVAILABLE(macos(10.4), ios(2.1), watchos(2.0), tvos(9.0));


//==================================================================================================
//	I/O
/*!
    @functiongroup  I/O
*/

/*!
	@function   ExtAudioFileRead
	
	@abstract   Perform a synchronous sequential read.
	
	@param		inExtAudioFile
					The extended audio file object.
	@param		ioNumberFrames
					On entry, ioNumberFrames is the number of frames to be read from the file.
					On exit, it is the number of frames actually read. A number of factors may
					cause a fewer number of frames to be read, including the supplied buffers
					not being large enough, and internal optimizations. If 0 frames are
					returned, however, this indicates that end-of-file was reached.
	@param		ioData
					Buffer(s) into which the audio data is read.
	@result		An OSStatus error code.

	@discussion
				If the file has a client data format, then the audio data from the file is
				translated from the file data format to the client format, via the
				ExtAudioFile's internal AudioConverter.
				
				(Note that the use of sequential reads/writes means that an ExtAudioFile must
				not be read on multiple threads; clients wishing to do this should use the
				lower-level AudioFile API set).
*/
extern OSStatus
ExtAudioFileRead(			ExtAudioFileRef			inExtAudioFile,
							UInt32 *				ioNumberFrames,
							AudioBufferList *		ioData)					
																			API_AVAILABLE(macos(10.4), ios(2.1), watchos(2.0), tvos(9.0));

/*!
	@function   ExtAudioFileWrite
	
	@abstract   Perform a synchronous sequential write.

	@param		inExtAudioFile
					The extended audio file object.
	@param		inNumberFrames
					The number of frames to write.
	@param		ioData
					The buffer(s) from which audio data is written to the file.
	@result		An OSStatus error code.
	
	@discussion
				If the file has a client data format, then the audio data in ioData is
				translated from the client format to the file data format, via the
				ExtAudioFile's internal AudioConverter.
*/
extern OSStatus
ExtAudioFileWrite(			ExtAudioFileRef			inExtAudioFile,
							UInt32					inNumberFrames,
							const AudioBufferList * ioData)					
																			API_AVAILABLE(macos(10.4), ios(2.1), watchos(2.0), tvos(9.0));

/*!
	@function   ExtAudioFileWriteAsync
	
	@abstract   Perform an asynchronous sequential write.
	
	@param		inExtAudioFile
					The extended audio file object.
	@param		inNumberFrames
					The number of frames to write.
	@param		ioData
					The buffer(s) from which audio data is written to the file.
	@result		An OSStatus error code.
		
	@discussion
				Writes the provided buffer list to an internal ring buffer and notifies an
				internal thread to perform the write at a later time. The first time this is
				called, allocations may be performed. You can call this with 0 frames and null
				buffer in a non-time-critical context to initialize the asynchronous mechanism.
				Once initialized, subsequent calls are very efficient and do not take locks;
				thus this may be used to write to a file from a realtime thread.

				The client must not mix synchronous and asynchronous writes to the same file.

				Pending writes are not guaranteed to be flushed to disk until
				ExtAudioFileDispose is called.

				N.B. Errors may occur after this call has returned. Such errors may be returned
				from subsequent calls to this function.
*/
extern OSStatus
ExtAudioFileWriteAsync(		ExtAudioFileRef			inExtAudioFile,
							UInt32					inNumberFrames,
							const AudioBufferList * __nullable ioData)
																			API_AVAILABLE(macos(10.4), ios(2.1), watchos(2.0), tvos(9.0));

/*!
	@function   ExtAudioFileSeek

	@abstract   Seek to a specific frame position.

	@param		inExtAudioFile
					The extended audio file object.
	@param		inFrameOffset
					The desired seek position, in sample frames, relative to the beginning of
					the file. This is specified in the sample rate and frame count of the file's format
					(not the client format)
	@result		An OSStatus error code.
	
	@discussion
				Sets the file's read position to the specified sample frame number. The next call
				to ExtAudioFileRead will return samples from precisely this location, even if it
				is located in the middle of a packet.
				
				This function's behavior with files open for writing is currently undefined.
*/
extern OSStatus
ExtAudioFileSeek(			ExtAudioFileRef			inExtAudioFile,
							SInt64					inFrameOffset)			
																			API_AVAILABLE(macos(10.4), ios(2.1), watchos(2.0), tvos(9.0));

/*!
	@function   ExtAudioFileTell
	
	@abstract   Return the file's read/write position.

	@param		inExtAudioFile
					The extended audio file object.
	@param		outFrameOffset
					On exit, the file's current read/write position in sample frames. This is specified in the 
					sample rate and frame count of the file's format (not the client format)
	@result		An OSStatus error code.
*/
extern OSStatus
ExtAudioFileTell(			ExtAudioFileRef			inExtAudioFile,
							SInt64 *				outFrameOffset)			
																			API_AVAILABLE(macos(10.4), ios(2.1), watchos(2.0), tvos(9.0));

//==================================================================================================
//	Property Access
/*!
    @functiongroup  Property Access
*/

/*!
	@function   ExtAudioFileGetPropertyInfo
	@abstract   Get information about a property

	@param		inExtAudioFile
					The extended audio file object.
	@param		inPropertyID
					The property being queried.
	@param		outSize
					If non-null, on exit, this is set to the size of the property's value.
	@param		outWritable
					If non-null, on exit, this indicates whether the property value is settable.
	@result		An OSStatus error code.
*/
extern OSStatus
ExtAudioFileGetPropertyInfo(ExtAudioFileRef			inExtAudioFile,
							ExtAudioFilePropertyID	inPropertyID,
							UInt32 * __nullable		outSize,
							Boolean * __nullable	outWritable)
																			API_AVAILABLE(macos(10.4), ios(2.1), watchos(2.0), tvos(9.0));

/*!
	@function   ExtAudioFileGetProperty
	@abstract   Get a property value.

	@param		inExtAudioFile
					The extended audio file object.
	@param		inPropertyID
					The property being fetched.
	@param		ioPropertyDataSize
					On entry, the size (in bytes) of the memory pointed to by outPropertyData.
					On exit, the actual size of the property data returned.	
	@param		outPropertyData
					The value of the property is copied to the memory this points to.
	@result		An OSStatus error code.
*/
extern OSStatus
ExtAudioFileGetProperty(	ExtAudioFileRef			inExtAudioFile,
							ExtAudioFilePropertyID	inPropertyID,
							UInt32 *				ioPropertyDataSize,
							void *					outPropertyData)
																			API_AVAILABLE(macos(10.4), ios(2.1), watchos(2.0), tvos(9.0));

/*!
	@function   ExtAudioFileSetProperty
	@abstract   Set a property value.

	@param		inExtAudioFile
					The extended audio file object.
	@param		inPropertyID
					The property being set.
	@param		inPropertyDataSize
					The size of the property data, in bytes.
	@param		inPropertyData
					Points to the property's new value.
	@result		An OSStatus error code.
*/
extern OSStatus
ExtAudioFileSetProperty(	ExtAudioFileRef			inExtAudioFile,
							ExtAudioFilePropertyID	inPropertyID,
							UInt32					inPropertyDataSize,
							const void *			inPropertyData)			
																			API_AVAILABLE(macos(10.4), ios(2.1), watchos(2.0), tvos(9.0));

CF_ASSUME_NONNULL_END

#ifdef __cplusplus
}
#endif

#endif // AudioToolbox_ExtendedAudioFile_h
#else
#include <AudioToolboxCore/ExtendedAudioFile.h>
#endif
// ==========  AudioToolbox.framework/Headers/AudioFileStream.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AudioFileStream.h>)
/*!
	@file		AudioFileStream.h
	@framework	AudioToolbox.framework
	@copyright	(c) 1985-2015 by Apple, Inc., all rights reserved.

	@brief		API's to parse streamed audio files into packets of audio data.

	@discussion

	AudioFileStream addresses situations where, in a stream of audio data, only a limited window
	of data may be available at any time.

	This case differs significantly enough from the random access file case to warrant a separate
	API rather than overload the AudioFile API with additional semantics. With a random access file,
	one can always assume that a read request for contiguous data that doesn't include EOF will
	always supply all of the data. This makes parsing straightforward and inexpensive. In the
	streaming case such an assumption cannot be made. A request by the parser for data from the
	stream may only be partially satisfied. Any partially satisfied requests must be remembered and
	retried before any other requests are satisfied, otherwise the streamed data might be lost
	forever in the past. So the parser must be able to suspend work at any point and resume parsing
	where it left off.
	
	The client provides data to the parser using AudioFileStreamParseBytes and the parser calls back
	to the client with properties or packets using the AudioFileStream_PropertyListenerProc and
	AudioFileStream_PacketsProc function pointers.
*/

#ifndef AudioToolbox_AudioFileStream_h
#define AudioToolbox_AudioFileStream_h

//=============================================================================
//	Includes
//=============================================================================

#include <Availability.h>
#include <CoreAudioTypes/CoreAudioTypes.h>
#include <AudioToolbox/AudioFile.h>

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//	AudioFileStream flags
//=============================================================================
#pragma mark flags

/*!
    @enum AudioFileStreamPropertyFlags
    @constant   kAudioFileStreamPropertyFlag_PropertyIsCached 
		This flag is set in a call to AudioFileStream_PropertyListenerProc when the value of the property
		can be obtained at any later time. If this flag is not set, then you should either get the value of 
		the property from within this callback or set the flag kAudioFileStreamPropertyFlag_CacheProperty in order to signal
		to the parser to begin caching the property data. Otherwise the value may not be available in the future.
		
    @constant   kAudioFileStreamPropertyFlag_CacheProperty 
		This flag can be set by a property listener in order to signal to the parser that the client is
		interested in the value of the property and that it should be cached until the full value of the property is available.
*/
typedef CF_OPTIONS(UInt32, AudioFileStreamPropertyFlags) {
	kAudioFileStreamPropertyFlag_PropertyIsCached = 1,
	kAudioFileStreamPropertyFlag_CacheProperty = 2
};

/*!	@enum	AudioFileStreamParseFlags
    @constant   kAudioFileStreamParseFlag_Discontinuity 
		This flag is passed in to AudioFileStreamParseBytes to signal a discontinuity. Any partial packet straddling a buffer
		boundary will be discarded. This is necessary to avoid being called with a corrupt packet. After a discontinuity occurs
		seeking may be approximate in some data formats.
*/
typedef CF_OPTIONS(UInt32, AudioFileStreamParseFlags) {
	kAudioFileStreamParseFlag_Discontinuity = 1
};

/*!	@enum	AudioFileStreamParseFlags
    @constant   kAudioFileStreamSeekFlag_OffsetIsEstimated 
		This flag may be returned from AudioFileStreamSeek if the byte offset is only an estimate, not exact.
*/
typedef CF_OPTIONS(UInt32, AudioFileStreamSeekFlags) {
	kAudioFileStreamSeekFlag_OffsetIsEstimated = 1
};

//=============================================================================
//	AudioFileStream Types
//=============================================================================
#pragma mark types

typedef UInt32 AudioFileStreamPropertyID;
typedef	struct OpaqueAudioFileStreamID	*AudioFileStreamID;

typedef void (*AudioFileStream_PropertyListenerProc)(
											void *							inClientData,
											AudioFileStreamID				inAudioFileStream,
											AudioFileStreamPropertyID		inPropertyID,
											AudioFileStreamPropertyFlags *	ioFlags);

typedef void (*AudioFileStream_PacketsProc)(
											void *							inClientData,
											UInt32							inNumberBytes,
											UInt32							inNumberPackets,
											const void *					inInputData,
											AudioStreamPacketDescription	*inPacketDescriptions);

//=============================================================================
//	AudioFileStream error codes
//=============================================================================
#pragma mark Error codes
/*!
    @enum AudioFileStream error codes

    @abstract   These are the error codes returned from the AudioFile API.

    @constant   kAudioFileStreamError_UnsupportedFileType 
		The file type is not supported.
    @constant   kAudioFileStreamError_UnsupportedDataFormat 
		The data format is not supported by this file type.
    @constant   kAudioFileStreamError_UnsupportedProperty 
		The property is not supported.
    @constant   kAudioFileStreamError_BadPropertySize 
		The size of the property data was not correct.
    @constant   kAudioFileStreamError_NotOptimized 
		It is not possible to produce output packets because the file's packet table or other defining 
		info is either not present or is after the audio data.
    @constant   kAudioFileStreamError_InvalidPacketOffset 
		A packet offset was less than zero, or past the end of the file,
		or a corrupt packet size was read when building the packet table. 
    @constant   kAudioFileStreamError_InvalidFile 
		The file is malformed, or otherwise not a valid instance of an audio file of its type, or 
		is not recognized as an audio file. 
    @constant   kAudioFileStreamError_ValueUnknown 
		The property value is not present in this file before the audio data.
	@constant	kAudioFileStreamError_DataUnavailable
		The amount of data provided to the parser was insufficient to produce any result.
	@constant	kAudioFileStreamError_IllegalOperation
		An illegal operation was attempted.
    @constant   kAudioFileStreamError_UnspecifiedError 
		An unspecified error has occurred.
		
*/

CF_ENUM(OSStatus)
{
	kAudioFileStreamError_UnsupportedFileType		= 'typ?',
	kAudioFileStreamError_UnsupportedDataFormat		= 'fmt?',
	kAudioFileStreamError_UnsupportedProperty		= 'pty?',
	kAudioFileStreamError_BadPropertySize			= '!siz',
	kAudioFileStreamError_NotOptimized				= 'optm',
	kAudioFileStreamError_InvalidPacketOffset		= 'pck?',
	kAudioFileStreamError_InvalidFile				= 'dta?',
	kAudioFileStreamError_ValueUnknown				= 'unk?',
	kAudioFileStreamError_DataUnavailable			= 'more',
	kAudioFileStreamError_IllegalOperation			= 'nope',
	kAudioFileStreamError_UnspecifiedError			= 'wht?',
	kAudioFileStreamError_DiscontinuityCantRecover	= 'dsc!'
};

//=============================================================================
//	AudioFileStream Properties
//=============================================================================
#pragma mark Properties

/*!
    @enum		AudioFileStream Properties
	
    @abstract   constants for AudioFileStream get property calls
    @discussion		There are currently no settable properties.

					
    @constant   kAudioFileStreamProperty_ReadyToProducePackets
					An UInt32 which is zero until the parser has parsed up to the beginning of the audio data. 
					Once it has reached the audio data, the value of this property becomes one. 
					When this value has become one, all properties that can be known about the stream are known.
					
    @constant   kAudioFileStreamProperty_FileFormat 
					An UInt32 four char code that identifies the format of the file
    @constant   kAudioFileStreamProperty_DataFormat 
					An AudioStreamBasicDescription describing the format of the audio data
    @constant   kAudioFileStreamProperty_FormatList 
					In order to support formats such as AAC SBR where an encoded data stream can be decoded to 
					multiple destination formats, this property returns an array of AudioFormatListItems 
					(see AudioFormat.h) of those formats.
					The default behavior is to return the an AudioFormatListItem that has the same 
					AudioStreamBasicDescription that kAudioFileStreamProperty_DataFormat returns.
    @constant   kAudioFileStreamProperty_MagicCookieData 
					A void * pointing to memory set up by the caller.
					Some file types require that a magic cookie be provided before packets can be written
					to the file, so this property should be set before calling 
					AudioFileWriteBytes()/AudioFileWritePackets() if a magic cookie exists.
    @constant   kAudioFileStreamProperty_AudioDataByteCount 
					a UInt64 that indicates the number of bytes of audio data contained in the file
    @constant   kAudioFileStreamProperty_AudioDataPacketCount 
					a UInt64 that indicates the number of packets of audio data contained in the file
    @constant   kAudioFileStreamProperty_MaximumPacketSize 
					a UInt32 that indicates the maximum size of a packet for the data contained in the file
    @constant   kAudioFileStreamProperty_DataOffset 
					a SInt64 that indicates the byte offset in the file of the audio data.
    @constant   kAudioFileStreamProperty_ChannelLayout 
					An AudioChannelLayout struct.
    @constant   kAudioFileStreamProperty_PacketToFrame 
					pass a AudioFramePacketTranslation with mPacket filled out and get mFrame back. 
					mFrameOffsetInPacket is ignored.
    @constant   kAudioFileStreamProperty_FrameToPacket 
					pass a AudioFramePacketTranslation with mFrame filled out and get mPacket and 
					mFrameOffsetInPacket back.
    @constant   kAudioFileStreamProperty_RestrictsRandomAccess
					A UInt32 indicating whether an Audio File contains packets that cannot be used as random
					access points.
					A value of 0 indicates that any packet can be used as a random access point, i.e. that a
					decoder can start decoding with any packet.
					A value of 1 indicates that some packets cannot be used as random access points, i.e.
					that either kAudioFileStreamProperty_PacketToRollDistance or
					kAudioFileStreamProperty_PacketToDependencyInfo must be employed in order to identify an
					appropriate initial packet for decoding.
	@constant	kAudioFileStreamProperty_PacketToRollDistance
					Pass an AudioPacketRollDistanceTranslation with mPacket filled out and get mRollDistance
					back.
					See AudioFile.h for the declaration of AudioPacketRollDistanceTranslation.
					The roll distance indicates the count of packets that must be decoded prior to the
					packet with the specified number in order to achieve full refresh of the decoder at that
					packet.
					For file formats that do not carry comprehensive information regarding independently
					decodable packets, accurate roll distances may be available only for the range of
					packets either currently or most recently provided to your packets proc.
	@constant   kAudioFileStreamProperty_PreviousIndependentPacket
	@constant	kAudioFileStreamProperty_NextIndependentPacket
					Pass an AudioIndependentPacketTranslation with mPacket filled out and get
					mIndependentlyDecodablePacket back. A value of -1 means that no independent packet is
					present in the stream in the direction of interest. Otherwise, for
					kAudioFileStreamProperty_PreviousIndependentPacket, mIndependentlyDecodablePacket will be
					less than mPacket, and for kAudioFileStreamProperty_NextIndependentPacket,
					mIndependentlyDecodablePacket will be greater than mPacket.
					For file formats that do not carry comprehensive information regarding independently
					decodable packets, independent packets may be identifiable only within the range of
					packets either currently or most recently provided to your packets proc.
	@constant	kAudioFileStreamProperty_PacketToDependencyInfo
					Pass an AudioPacketDependencyInfoTranslation with mPacket filled out and get
					mIsIndependentlyDecodable and mPrerollPacketCount back.
					A value of 0 for mIsIndependentlyDecodable indicates that the specified packet is not
					independently decodable.
					A value of 1 for mIsIndependentlyDecodable indicates that the specified packet is
					independently decodable.
					For independently decodable packets, mPrerollPacketCount indicates the count of packets
					that must be decoded after the packet with the specified number in order to refresh the
					decoder.
					For file formats that do not carry comprehensive information regarding packet
					dependencies, accurate dependency info may be available only for the range of
					packets either currently or most recently provided to your packets proc.
	@constant	kAudioFileStreamProperty_PacketToByte
					pass an AudioBytePacketTranslation struct with mPacket filled out and get mByte back.
					mByteOffsetInPacket is ignored. If the mByte value is an estimate then 
					kBytePacketTranslationFlag_IsEstimate will be set in the mFlags field.
	@constant	kAudioFileStreamProperty_ByteToPacket
					pass an AudioBytePacketTranslation struct with mByte filled out and get mPacket and
					mByteOffsetInPacket back. If the mPacket value is an estimate then 
					kBytePacketTranslationFlag_IsEstimate will be set in the mFlags field.
    @constant   kAudioFileStreamProperty_PacketTableInfo 
					Gets the AudioFilePacketTableInfo struct for the file types that support it.
	@constant	kAudioFileStreamProperty_PacketSizeUpperBound
					a UInt32 for the theoretical maximum packet size in the file.
	@constant	kAudioFileStreamProperty_AverageBytesPerPacket
					a Float64 of giving the average bytes per packet seen. 
					For CBR and files with packet tables, this number will be exact. Otherwise, it is a
					running average of packets parsed.
	@constant	kAudioFileStreamProperty_BitRate
					a UInt32 of the bit rate in bits per second.
    @constant	kAudioFileStreamProperty_InfoDictionary
                    a CFDictionary filled with information about the data contained in the stream.
                    See AudioFile.h for InfoDictionary key strings. Caller is responsible for releasing the CFObject.
*/
CF_ENUM(AudioFileStreamPropertyID)
{
	kAudioFileStreamProperty_ReadyToProducePackets			=	'redy',
	kAudioFileStreamProperty_FileFormat						=	'ffmt',
	kAudioFileStreamProperty_DataFormat						=	'dfmt',
	kAudioFileStreamProperty_FormatList						=	'flst',
	kAudioFileStreamProperty_MagicCookieData				=	'mgic',
	kAudioFileStreamProperty_AudioDataByteCount				=	'bcnt',
	kAudioFileStreamProperty_AudioDataPacketCount			=	'pcnt',
	kAudioFileStreamProperty_MaximumPacketSize				=	'psze',
	kAudioFileStreamProperty_DataOffset						=	'doff',
	kAudioFileStreamProperty_ChannelLayout					=	'cmap',
	kAudioFileStreamProperty_PacketToFrame					=	'pkfr',
	kAudioFileStreamProperty_FrameToPacket					=	'frpk',
	kAudioFileStreamProperty_RestrictsRandomAccess          =   'rrap',
	kAudioFileStreamProperty_PacketToRollDistance           =   'pkrl',
	kAudioFileStreamProperty_PreviousIndependentPacket      =   'pind',
	kAudioFileStreamProperty_NextIndependentPacket          =   'nind',
	kAudioFileStreamProperty_PacketToDependencyInfo         =   'pkdp',
	kAudioFileStreamProperty_PacketToByte					=	'pkby',
	kAudioFileStreamProperty_ByteToPacket					=	'bypk',
	kAudioFileStreamProperty_PacketTableInfo				=	'pnfo',
	kAudioFileStreamProperty_PacketSizeUpperBound  			=	'pkub',
	kAudioFileStreamProperty_AverageBytesPerPacket			=	'abpp',
	kAudioFileStreamProperty_BitRate						=	'brat',
	kAudioFileStreamProperty_InfoDictionary                 = 	'info'
};

//=============================================================================
//	AudioFileStream Functions
//=============================================================================
#pragma mark Functions


/*!
	@function		AudioFileStreamOpen

	@discussion		Create a new audio file stream parser.
					The client provides the parser with data and the parser calls
					callbacks when interesting things are found in the data, such as properties and 
					audio packets.

    @param			inClientData					
						a constant that will be passed to your callbacks.
	@param			inPropertyListenerProc
						Whenever the value of a property is parsed in the data, this function will be called.
						You can then get the value of the property from in the callback. In some cases, due to 
						boundaries in the input data, the property may return kAudioFileStreamError_DataUnavailable.
						When unavailable data is requested from within the property listener, the parser will begin 
						caching the property value and will call the property listener again when the property is
						available. For property values for which kAudioFileStreamPropertyFlag_PropertyIsCached is unset, this 
						will be the only opportunity to get the value of the property, since the data will be 
						disposed upon return of the property listener callback. 
	@param			inPacketsProc
						Whenever packets are parsed in the data, a pointer to the packets is passed to the client 
						using this callback. At times only a single packet may be passed due to boundaries in the 
						input data.
    @param 			inFileTypeHint	
						For files whose type cannot be easily or uniquely determined from the data (ADTS,AC3), 
						this hint can be used to indicate the file type. 
						Otherwise if you do not know the file type, you can pass zero. 
	@param			outAudioFileStream 
						A new file stream ID for use in other AudioFileStream API calls.
*/ 
extern OSStatus	
AudioFileStreamOpen (
							void * __nullable						inClientData,
							AudioFileStream_PropertyListenerProc	inPropertyListenerProc,
							AudioFileStream_PacketsProc				inPacketsProc,
                			AudioFileTypeID							inFileTypeHint,
                			AudioFileStreamID __nullable * __nonnull outAudioFileStream)
																		API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));


/*!
	@function		AudioFileStreamParseBytes

	@discussion		This call is the means for streams to supply data to the parser. 
					Data is expected to be passed in sequentially from the beginning of the file, without gaps.
					In the course of parsing, the client's property and/or packets callbacks may be called.
					At the end of the stream, this function must be called once with null data pointer and zero
					data byte size to flush any remaining packets out of the parser.

	@param			inAudioFileStream 
						The file stream ID
	@param			inDataByteSize 
						The number of bytes passed in for parsing. Must be zero when flushing the parser.
	@param			inData 
						The data passed in to be parsed. Must be null when flushing the parser.
	@param			inFlags 
						If there is a data discontinuity, then kAudioFileStreamParseFlag_Discontinuity should be set true. 
*/
extern OSStatus
AudioFileStreamParseBytes(	
								AudioFileStreamID				inAudioFileStream,
								UInt32							inDataByteSize,
								const void * __nullable			inData,
								AudioFileStreamParseFlags		inFlags)
																		API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioFileStreamSeek

	@discussion		This call is used to seek in the data stream. The client passes in a packet 
					offset to seek to and the parser passes back a byte offset from which to
					get the data to satisfy that request. The data passed to the next call to 
					AudioFileParseBytes will be assumed to be from that byte offset.
					For file formats which do not contain packet tables the byte offset may 
					be an estimate. If so, the flag kAudioFileStreamSeekFlag_OffsetIsEstimated will be true.

	@param			inAudioFileStream 
						The file stream ID
	@param			inPacketOffset 
						The offset from the beginning of the file of the packet to which to seek.
	@param			outDataByteOffset 
						The byte offset of the data from the file's data offset returned. 
						You need to add the value of kAudioFileStreamProperty_DataOffset to get an absolute byte offset in the file.
	@param			ioFlags
						If outDataByteOffset is an estimate, then kAudioFileStreamSeekFlag_OffsetIsEstimated will be set on output.
						There are currently no flags defined for passing into this call.
*/
extern OSStatus
AudioFileStreamSeek(	
								AudioFileStreamID				inAudioFileStream,
								SInt64							inPacketOffset,
								SInt64 *						outDataByteOffset,
								AudioFileStreamSeekFlags *		ioFlags)
																		API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioFileStreamGetPropertyInfo
 
	@discussion		Retrieve the info about the given property. The outSize argument
					will return the size in bytes of the current value of the property.
 
	@param			inAudioFileStream 
						The file stream ID
	@param			inPropertyID
						Property ID whose value should be read
	@param			outPropertyDataSize
						Size in bytes of the property
	@param			outWritable
						whether the property is writable
 
	@result			an OSStatus return code
*/
extern OSStatus
AudioFileStreamGetPropertyInfo(	
								AudioFileStreamID				inAudioFileStream,
								AudioFileStreamPropertyID		inPropertyID,
								UInt32 * __nullable				outPropertyDataSize,
								Boolean * __nullable			outWritable)
																		API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));


/*!
	@function		AudioFileStreamGetProperty
 
	@discussion		Retrieve the indicated property data. 
 
	@param			inAudioFileStream 
						The file stream ID
	@param			inPropertyID
						Property ID whose value should be read
	@param			ioPropertyDataSize
						On input, the size of the buffer pointed to by outPropertyData. On output, 
						the number of bytes written.
	@param			outPropertyData
						Pointer to the property data buffer

	@result			an OSStatus return code
*/
extern OSStatus
AudioFileStreamGetProperty(	
							AudioFileStreamID					inAudioFileStream,
							AudioFileStreamPropertyID			inPropertyID,
							UInt32 *							ioPropertyDataSize,
							void *								outPropertyData)		
																		API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioFileStreamSetProperty
 
	@discussion		Set the value of the property. There are currently no settable properties.
 
	@param			inAudioFileStream 
						The file stream ID
	@param			inPropertyID
						Property ID whose value should be set
	@param			inPropertyDataSize
						Size in bytes of the property data
	@param			inPropertyData
						Pointer to the property data buffer

	@result			an OSStatus return code
*/
extern OSStatus
AudioFileStreamSetProperty(	
							AudioFileStreamID					inAudioFileStream,
							AudioFileStreamPropertyID			inPropertyID,
							UInt32								inPropertyDataSize,
							const void *						inPropertyData)		
																		API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioFileStreamClose
 
	@discussion		Close and deallocate the file stream object.

	@param			inAudioFileStream 
						The file stream ID
*/
extern OSStatus
AudioFileStreamClose(			AudioFileStreamID				inAudioFileStream)										
																		API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));


#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioFileStream_h

#else
#include <AudioToolboxCore/AudioFileStream.h>
#endif
// ==========  AudioToolbox.framework/Headers/MusicDevice.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/MusicDevice.h>)
/*!
	@file		MusicDevice.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2000-2015 Apple, Inc. All rights reserved.
	@abstract	Additional Audio Unit API for software musical instruments.

	@discussion

	A music device audio unit, commonly referred to as a music instrument, is used to render notes.
	A note is a sound, usually pitched, that is started and stopped with a note number or pitch
	specifier. A note is played on a group (in MIDI this is called a MIDI Channel) and the various
	state values of a group (such as pitch bend, after-touch, etc) is inherited and controlled by
	every playing note on a given group. A note can be individually stopped (which is the common
	case), or stopped with the "All Notes Off" message that is sent to a specific group.

	A music instrument can be multi-timbral - that is, each group can have a particular patch (or
	sound) associated with it, and different groups can have different patches. This is a common
	case for music instruments that implement the General MIDI specification. In this case, the
	music instrument should return the number of available patches at a given time as the value for
	the _InstrumentCount property.

	It is also common for instruments to be mono-timbral - that is, they are only capable of
	producing notes using a single patch/sound and typically only respond to commands on one group.
	In this case, the music instrument should return 0 as the value for the _InstrumentCount
	property.

	Parameters can be defined in Group Scope, and these parameter IDs within the range of 0 < 1024,
	are equivalent to the standard definitions of control in the MIDI specification (up to the ID
	of). Parameters in group scope above 1024 are audio unit defined.

	Notes can be created/started with one of two methods. To stop a note it must be stopped with the
	same API group as was used to start it (MIDI or the extended Start/Stop note API.

	(1) the MIDI Note on event (MusicDeviceMIDIEvent)
		- notes must be stopped with the MIDI note off event (MusicDeviceMIDIEvent)
		The MIDI Note number is used to turn the note off for the specified channel
		
	(2) the extended Note API (MusicDeviceStartNote). This API returns a note instance ID.
		This is unique and can be used with the kAudioUnitScope_Note.
		It is also used to turn the note off with MusicDeviceStopNote
*/

#ifndef AudioUnit_MusicDevice_h
#define AudioUnit_MusicDevice_h

#include <AudioToolbox/AUComponent.h>

CF_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

//=====================================================================================================================
#pragma mark -
#pragma mark Types

/*!
	@typedef MusicDeviceInstrumentID
	@abstract type for instrument identifiers
*/
typedef UInt32                          MusicDeviceInstrumentID;

/*!
	@typedef MusicDeviceStdNoteParams
	@abstract convenience struct for specifying a note and velocity
	
	@discussion This struct is the common usage for MusicDeviceStartNote, as most synths that implement this functionality 
				will only allow for the specification of a note number and velocity when starting a new note.
	
	@var  			argCount
			Should be set to 2
	@var  			mPitch
			The pitch of the new note, typically specified using a MIDI note number (and a fractional pitch) within the 
					range of 0 < 128. So 60 is middle C, 60.5 is middle C + 50 cents.
	@var  			mVelocity
			The velocity of the new note - this can be a fractional value - specified as MIDI (within the range of 0 < 128)
*/
struct MusicDeviceStdNoteParams
{
	UInt32							argCount;		/* should be 2*/
	Float32							mPitch;
	Float32							mVelocity;
};
typedef struct MusicDeviceStdNoteParams		MusicDeviceStdNoteParams;

/*!
	@typedef NoteParamsControlValue
	@abstract used to describe a control and value
	
	@discussion This struct is used to describe a parameterID (a control in MIDI terminology, though it is not limited to 
					MIDI CC specifications) and the value of this parameter.
	
	@var  			mID
			The parameter ID
	@var  			mValue
			The value of that parameter
*/
struct NoteParamsControlValue
{
	AudioUnitParameterID			mID;
	AudioUnitParameterValue			mValue;
};
typedef struct NoteParamsControlValue		NoteParamsControlValue;

/*!
	@typedef MusicDeviceNoteParams
	@abstract Used to hold the value of the inParams parameter for the MusicDeviceStartNote function.
	
	@discussion The generic version of this structure describes an arg count (which is the number of mControls values 
				+ 1 for mPitch and 1 for mVelocity). So, argCount should at least be two. See MusicDeviceStdNoteParams 
				for the common use case, as many audio unit instruments will not respond to control values provided 
				in the start note function
	
	@var  			argCount
			The number of controls + 2 (for mPitch and mVelocity)
	@var  			mPitch
			The pitch of the new note, typically specified using a MIDI note number (and a fractional pitch) within the 
				range of 0 < 128. So 60 is middle C, 60.5 is middle C + 50 cents.
	@var  			mVelocity
			The velocity of the new note - this can be a fractional value - specified as MIDI (within the range of 0 < 128)
	@var  			mControls
			A variable length array with the number of elements: argCount - 2.
*/
struct MusicDeviceNoteParams
{
	UInt32							argCount;
	Float32							mPitch;
	Float32							mVelocity;
	NoteParamsControlValue			mControls[1];				/* arbitrary length */
};
typedef struct MusicDeviceNoteParams    MusicDeviceNoteParams;

/*!
	@enum	MusicNoteEvent
	@discussion This is used to signify that the patch used to start a note (its sound) is defined by the current 
					selection for the group ID; this is the normal usage in MIDI as any notes started on a given channel 
					(group ID) use the sound (patch) defined for that channel. See MusicDeviceStartNote
	
	@constant	kMusicNoteEvent_UseGroupInstrument
			Use the patch (instrument number) assigned to the new notes group ID
	@constant	kMusicNoteEvent_Unused
			The instrument ID is not specified
	
*/
enum {
	kMusicNoteEvent_UseGroupInstrument  = 0xFFFFFFFF,
	kMusicNoteEvent_Unused				= 0xFFFFFFFF
};

/*!
	@typedef		MusicDeviceGroupID
	@discussion The type used to specify which group (channel number in MIDI) is used with a given command (new note, 
				control or parameter value change)
*/
typedef UInt32                          MusicDeviceGroupID;

/*!
	@typedef		NoteInstanceID
	@discussion The type used to hold an unique identifier returned by MusicDeviceStartNote that is used to then address 
				that note (typically to turn the note off). An ID must be used for notes, because notes can be specified 
				by fractional pitches, and so using the MIDI note number is not sufficient to identify the note to turn 
				it off (or to apply polyphonic after touch). 
*/
typedef UInt32                          NoteInstanceID;

/*!
	@typedef		MusicDeviceComponent
	@discussion	The unique type of a MusicDevice audio unit (which is an AudioComponentInstance)
*/
typedef AudioComponentInstance          MusicDeviceComponent;

//=====================================================================================================================
#pragma mark -
#pragma mark Functions

/*!
	@function	MusicDeviceMIDIEvent
	@abstract	Used to sent MIDI channel messages to an audio unit
	
	@discussion	This is the API used to send MIDI channel messages to an audio unit. The status and data parameters 
				are used exactly as described by the MIDI specification, including the combination of channel and 
				command in the status byte.
	
	@param			inUnit
				The audio unit
	@param			inStatus
				The MIDI status byte
	@param			inData1
				The first MIDI data byte (value is in the range 0 < 128)
	@param			inData2
				The second MIDI data byte (value is in the range 0 < 128). If the MIDI status byte only has one 
					data byte, this should be set to zero.
	@param			inOffsetSampleFrame
				If you are scheduling the MIDI Event from the audio unit's render thread, then you can supply a 
					sample offset that the audio unit may apply when applying that event in its next audio unit render. 
					This allows you to schedule to the sample, the time when a MIDI command is applied and is particularly 
					important when starting new notes. If you are not scheduling in the audio unit's render thread, 
					then you should set this value to 0

	@result			noErr, or an audio unit error code
*/
extern OSStatus
MusicDeviceMIDIEvent(	MusicDeviceComponent	inUnit,
						UInt32					inStatus,
						UInt32					inData1,
						UInt32					inData2,
						UInt32					inOffsetSampleFrame)				API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicDeviceSysEx
	@abstract	used to send any non-channel MIDI event to an audio unit
	
	@discussion	This is used to send any non-channel MIDI event to an audio unit. In practise this is a System Exclusive 
					(SysEx) MIDI message
	
	@param			inUnit
				The audio unit
	@param			inData
				The complete MIDI SysEx message including the F0 and F7 start and termination bytes
	@param			inLength
				The size, in bytes, of the data

	@result			noErr, or an audio unit error code
*/
extern OSStatus
MusicDeviceSysEx(		MusicDeviceComponent	inUnit,
						const UInt8 *			inData,
						UInt32					inLength)							API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));


/*!
	@function	MusicDeviceStartNote
	@abstract	used to start a note
	
	@discussion	This function is used to start a note.  The caller must provide a NoteInstanceID to receive a 
					token that is then used to stop the note. The MusicDeviceStopNote call should be used to stop 
					notes started with this API. The token can also be used to address individual notes on the 
					kAudioUnitScope_Note if the audio unit supports it. The instrumentID is no longer used and the 
					kMusicNoteEvent_Unused constant should be specified (this takes the current patch for the 
					specifed group as the sound to use for the note).
	
			The Audio unit must provide an unique ID for the note instance ID. This ID must be non-zero and not 
					0xFFFFFFFF (any other UInt32 value is valid).
			
			Not all Music Device audio units implement the semantics of this API (though it is strongly recommended 
					that they do). A host application shoudl query the kMusicDeviceProperty_SupportsStartStopNote to 
					check that this is supported.
			
	@param			inUnit
				The audio unit
	@param			inInstrument
				The instrumentID is no longer used and the kMusicNoteEvent_Unused constant should be specified (this takes 
					the current patch for the specifed group as the sound to use for the note)
	@param			inGroupID
				The group ID that this note will be attached too. As with MIDI, all notes sounding on a groupID can be 
					controlled through the various parameters (such as pitch bend, etc) that can be specified on the Group 
					Scope
	@param			outNoteInstanceID
				A pointer to receive the token that is used to identify the note. This parameter must be specified
	@param			inOffsetSampleFrame
				If you are scheduling the MIDI Event from the audio unit's render thread, then you can supply a sample offset 
					that the audio unit may apply when starting the note in its next audio unit render. This allows you to 
					schedule to the sample and is particularly important when starting new notes. If you are not scheduling 
					in the audio unit's render thread, then you should set this value to 0
	@param			inParams
				The parameters to be used when starting the note - pitch and velocity must be specified
	
	@result			noErr, or an audio unit error code
*/
extern OSStatus
MusicDeviceStartNote(	MusicDeviceComponent				inUnit,
						MusicDeviceInstrumentID				inInstrument,
						MusicDeviceGroupID					inGroupID,
						NoteInstanceID *					outNoteInstanceID,
						UInt32								inOffsetSampleFrame,
						const MusicDeviceNoteParams *	 	inParams)				API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));

/*!
	@function	MusicDeviceStopNote
	@abstract	used to stop notes started with the MusicDeviceStartNote call

	@discussion	This call is used to stop notes that have been started with the MusicDeviceStartNote call; both the group ID 
					that the note was started on and the noteInstanceID should be specified.
	
	@param			inUnit
				The audio unit
	@param			inGroupID
				the group ID
	@param			inNoteInstanceID
				the note instance ID
	@param			inOffsetSampleFrame
				the sample offset within the next buffer rendered that the note should be turned off at

	@result			noErr, or an audio unit error code
*/
extern OSStatus
MusicDeviceStopNote(	MusicDeviceComponent	inUnit,
						MusicDeviceGroupID		inGroupID,
						NoteInstanceID			inNoteInstanceID,
						UInt32					inOffsetSampleFrame)				API_AVAILABLE(macos(10.0), ios(5.0), watchos(2.0), tvos(9.0));


/*!
	@enum	Music Device range
	@constant	kMusicDeviceRange
				delineates the start of the selector ranges for music devices
				
	@constant	kMusicDeviceMIDIEventSelect
	@constant	kMusicDeviceSysExSelect
	@constant	kMusicDevicePrepareInstrumentSelect
	@constant	kMusicDeviceReleaseInstrumentSelect
	@constant	kMusicDeviceStartNoteSelect
	@constant	kMusicDeviceStopNoteSelect
*/
enum {
		kMusicDeviceRange						= 0x0100,
		kMusicDeviceMIDIEventSelect				= 0x0101,
		kMusicDeviceSysExSelect					= 0x0102,
		kMusicDevicePrepareInstrumentSelect		= 0x0103,
		kMusicDeviceReleaseInstrumentSelect		= 0x0104,
		kMusicDeviceStartNoteSelect				= 0x0105,
		kMusicDeviceStopNoteSelect				= 0x0106
};

//=====================================================================================================================
#pragma mark -
#pragma mark Fast-dispatch function prototypes

/*!
	@typedef		MusicDeviceMIDIEventProc
	@discussion		This proc can be exported through the FastDispatch property or is used as the prototype for
					an audio component dispatch for this selector. 
					
					The arguments are the same as are provided to the corresponding API call
	
	@param			self
					For a component manager component, this is the component instance storage pointer

	@result			noErr, or an audio unit error code
*/
typedef OSStatus
(*MusicDeviceMIDIEventProc)(	void *					self,
								UInt32					inStatus,
								UInt32					inData1,
								UInt32					inData2,
								UInt32					inOffsetSampleFrame);

/*!
	@typedef		MusicDeviceSysExProc
	@discussion		This proc can be exported through the FastDispatch property or is used as the prototype for
					an audio component dispatch for this selector. 
					
					The arguments are the same as are provided to the corresponding API call
	
	@param			self
					For a component manager component, this is the component instance storage pointer

	@result			noErr, or an audio unit error code
*/
typedef OSStatus
(*MusicDeviceSysExProc)(	void *						self,
							const UInt8 *				inData,
							UInt32						inLength);

/*!
	@typedef		MusicDeviceStartNoteProc
	@discussion		This proc can be exported through the FastDispatch property or is used as the prototype for
					an audio component dispatch for this selector. 
					
					The arguments are the same as are provided to the corresponding API call
	
	@param			self
					For a component manager component, this is the component instance storage pointer
	
	@result			noErr, or an audio unit error code
*/
typedef OSStatus
(*MusicDeviceStartNoteProc)(	void *					self,
						MusicDeviceInstrumentID			inInstrument,
						MusicDeviceGroupID				inGroupID,
						NoteInstanceID *				outNoteInstanceID,
						UInt32							inOffsetSampleFrame,
						const MusicDeviceNoteParams *	inParams);

/*!
	@typedef		MusicDeviceStopNoteProc
	@discussion		This proc can be exported through the FastDispatch property or is used as the prototype for
					an audio component dispatch for this selector. 
					
					The arguments are the same as are provided to the corresponding API call
	
	@param			self
					For a component manager component, this is the component instance storage pointer
	
	@result			noErr, or an audio unit error code
*/
typedef OSStatus
(*MusicDeviceStopNoteProc)(	void *						self,
						MusicDeviceGroupID				inGroupID,
						NoteInstanceID					inNoteInstanceID,
						UInt32							inOffsetSampleFrame);


//=====================================================================================================================
#pragma mark -
#pragma mark Deprecated

/*
	The notion of instruments (separate voices assigned to different control groups) is a deprecated concept.
	
	Going forward, multitimbral synths are implemented using Part Scopes.
	
	Thus, the Prepare and Release Instrument API calls are deprecated (see also MusicDeviceStartNote)

*/
extern OSStatus
MusicDevicePrepareInstrument(	MusicDeviceComponent		inUnit,
								MusicDeviceInstrumentID		inInstrument)		
										API_DEPRECATED("no longer supported", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);


extern OSStatus
MusicDeviceReleaseInstrument(	MusicDeviceComponent		inUnit,
								MusicDeviceInstrumentID		inInstrument)		
										API_DEPRECATED("no longer supported", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);

	
#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif /* AudioUnit_MusicDevice_h */

#else
#include <AudioToolboxCore/MusicDevice.h>
#endif
// ==========  AudioToolbox.framework/Headers/AUAudioUnitImplementation.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AUAudioUnitImplementation.h>)
/*!
	@file		AUAudioUnitImplementation.h
 	@framework	AudioToolbox.framework
 	@copyright	(c) 2015 Apple, Inc. All rights reserved.

	@brief		Additional AUAudioUnit interfaces specific to subclass implementations.
*/


/*!
@page AUExtensionPackaging Audio Unit Extension Packaging
@discussion

Audio Unit app extensions are available beginning with Mac OS X 10.11 and iOS 9.0.
For background on app extensions, see "App Extension Programming Guide."

There are two types of audio unit extensions: UI, and non-UI. The principal class of an
extension with UI must be a subclass of AUViewController. This class is declared
in CoreAudioKit/AUViewController.h. The principal class of a non-UI extension can derive from
NSObject.

The principal class of both UI and non-UI extensions must conform to the AUAudioUnitFactory
protocol.

The Info.plist of the .appex bundle describes the type of extension and the principal class.
It also contains an AudioComponents array (see AudioComponent.h), and an optional
AudioComponentBundle entry, for example:

@textblock
	<key>NSExtension</key>
	<dict>
		<key>NSExtensionAttributes</key>
		<dict>
			<key>NSExtensionActivationRule</key>
			<string>TRUEPREDICATE</string>
			<key>NSExtensionServiceRoleType</key>
			<string>NSExtensionServiceRoleTypeEditor</string>
			<key>AudioComponents</key>
			<array>
				<dict>
					<key>factoryFunction</key>
					<string>____</string>
					<key>manufacturer</key>
					<string>____</string>
					<key>name</key>
					<string>____</string>
					<key>sandboxSafe</key>
					<true/>
					<key>subtype</key>
					<string>____</string>
					<key>tags</key>
					<array>
						<string>____</string>
					</array>
					<key>type</key>
					<string>____</string>
					<key>version</key>
					<integer>____</integer>
				</dict>
			</array>
			<key>AudioComponentBundle</key>
			<string>____</string>
		</dict>
		<key>NSExtensionPointIdentifier</key>
		<string>____</string>
		<key>NSExtensionPrincipalClass</key>
		<string>____</string>
	</dict>
@/textblock

NSExtensionPointIdentifier
: `com.apple.AudioUnit` or `com.apple.AudioUnit-UI`.

NSExtensionPrincipalClass
:	The name of the principal class.

AudioComponentBundle
:	Optional. A version 3 audio unit can be loaded into a separate extension process and
	this is the default behavior. To be able to load in-process on macOS (see 
	kAudioComponentInstantiation_LoadInProcess) the audio unit has to be packaged 
	separately. The AudioComponentBundle entry supports loading in-process by designating 
	the identifier of a bundle in the .appex or its enclosing app container in which the 
	factory function and/or principal class are implemented. 

AudioComponents
:	Registration info for each audio component type/subtype/manufacturer
	implemented in the extension. factoryFunction is only necessary
	if the AU is implemented using AUAudioUnitV2Bridge.
	See AudioComponent.h.

Note that as of OS X version 10.12, the system has special support for installing both version 2
(bundle-based) and version 3 (extension) implementations of the same audio unit. When two components
are registered with the same type/subtype/manufacturer and version, normally the first one found
is used. But if one is an audio unit extension and the other is not, then the audio unit extension's
registration "wins", though if an app attempts to open it synchronously, with 
AudioComponentInstanceNew, then the system will fall back to the version 2 implementation.
*/

#ifndef AudioToolbox_AUAudioUnitImplementation_h
#define AudioToolbox_AUAudioUnitImplementation_h
#ifdef __OBJC2__

#import <AudioToolbox/AUAudioUnit.h>

NS_ASSUME_NONNULL_BEGIN

// forward declaration
union AURenderEvent;

// =================================================================================================
// Realtime events - parameters and MIDI

/// Describes the type of a render event.
typedef NS_ENUM(uint8_t, AURenderEventType) {
	AURenderEventParameter		= 1,
	AURenderEventParameterRamp	= 2,
	AURenderEventMIDI			= 8,
	AURenderEventMIDISysEx		= 9
};

#pragma pack(4)
///	Common header for an AURenderEvent.
typedef struct AURenderEventHeader {
	union AURenderEvent *__nullable next;		//!< The next event in a linked list of events.
	AUEventSampleTime		eventSampleTime;	//!< The sample time at which the event is scheduled to occur.
	AURenderEventType		eventType;			//!< The type of the event.
	uint8_t					reserved;			//!< Must be 0.
} AURenderEventHeader;

/// Describes a scheduled parameter change.
typedef struct AUParameterEvent {
	union AURenderEvent *__nullable next;		//!< The next event in a linked list of events.
	AUEventSampleTime		eventSampleTime;	//!< The sample time at which the event is scheduled to occur.
	AURenderEventType		eventType;			//!< AURenderEventParameter or AURenderEventParameterRamp.
	uint8_t					reserved[3];		//!< Must be 0.
	AUAudioFrameCount		rampDurationSampleFrames;
												//!< If greater than 0, the event is a parameter ramp; 
												/// 	 should be 0 for a non-ramped event.
	AUParameterAddress		parameterAddress;	//!< The parameter to change.
	AUValue					value;				//!< If ramped, the parameter value at the
												///	end of the ramp; for a non-ramped event,
												///	the new value.
} AUParameterEvent;

/// Describes a single scheduled MIDI event.
typedef struct AUMIDIEvent {
	union AURenderEvent *__nullable next;		//!< The next event in a linked list of events.
	AUEventSampleTime		eventSampleTime;	//!< The sample time at which the event is scheduled to occur.
	AURenderEventType		eventType;			//!< AURenderEventMIDI or AURenderEventMIDISysEx.
	uint8_t					reserved;			//!< Must be 0.
	uint16_t				length;				//!< The number of valid MIDI bytes in the data field.
												/// 1, 2 or 3 for most MIDI events, but can be longer
												/// for system-exclusive (sys-ex) events.
	uint8_t					cable;				//!< The virtual cable number.
	uint8_t					data[3];			//!< The bytes of the MIDI event. Running status will not be used.
} AUMIDIEvent;

/*!	@brief	A union of the various specific render event types.
	@discussion
		Determine which variant to use via head.eventType. AURenderEventParameter and
		AURenderEventParameterRamp use the parameter variant. AURenderEventMIDI and
		AURenderEventMIDISysEx use the MIDI variant.
*/
typedef union AURenderEvent {
	AURenderEventHeader		head;
	AUParameterEvent		parameter;
	AUMIDIEvent				MIDI;
} AURenderEvent;
#pragma pack()

/*!	@brief	Block to render the audio unit.
	@discussion
		Implemented in subclasses; should not be used by clients.

		The other parameters are identical to those of AURenderBlock.
	@param realtimeEventListHead
		A time-ordered linked list of the AURenderEvents to be rendered during this render cycle.
		Note that a ramp event will only appear in the render cycle during which it starts; the
		audio unit is responsible for maintaining continued ramping state for any further render
		cycles.
*/
typedef AUAudioUnitStatus (^AUInternalRenderBlock)(
	AudioUnitRenderActionFlags *		actionFlags,
	const AudioTimeStamp *				timestamp,
	AUAudioFrameCount					frameCount,
	NSInteger							outputBusNumber,
	AudioBufferList *					outputData,
	const AURenderEvent *__nullable 	realtimeEventListHead,
	AURenderPullInputBlock __nullable	pullInputBlock);

// =================================================================================================

/// Aspects of AUAudioUnit of interest only to subclassers.
@interface AUAudioUnit (AUAudioUnitImplementation)

/*!	@brief	Register an audio unit component implemented as an AUAudioUnit subclass.
	@discussion
		This method dynamically registers the supplied AUAudioUnit subclass with the Audio Component
		system, in the context of the current process (only). After registering the subclass, it can
		be instantiated via AudioComponentInstanceNew, 
		-[AUAudioUnit initWithComponentDescription:options:error:], and via any other API's which
		instantiate audio units via their component descriptions (e.g. <AudioToolbox/AUGraph.h>, or
		<AVFoundation/AVAudioUnitEffect.h>).
*/
+ (void)registerSubclass:(Class)cls asComponentDescription:(AudioComponentDescription)componentDescription name:(NSString *)name version:(UInt32)version;

/// Block which subclassers must provide (via a getter) to implement rendering.
@property (nonatomic, readonly) AUInternalRenderBlock internalRenderBlock;


/// Re-declare the parameterTree as writable from the Audio Unit implementation

/*! @property	parameterTree
	@brief		An audio unit's parameters, organized in a hierarchy.
	@discussion
		See the description in AUAudioUnit.h
 */
@property (NS_NONATOMIC_IOSONLY, readwrite, nullable) AUParameterTree *parameterTree;

/*! @property	MIDIOutputBufferSizeHint
	@brief		Hint to control the size of the allocated buffer for outgoing MIDI events.
	@discussion
        This property allows the plug-in to provide a hint to the framework regarding the size of
        its outgoing MIDI data buffer.

        If the plug-in produces more MIDI output data than the default size of the allocated buffer,
        then the plug-in can provide this property to increase the size of this buffer.

        The value represents the number of 3-byte MIDI 1.0 messages that fit into the buffer.
        This property is set to the default value by the framework.

        In case of kAudioUnitErr_MIDIOutputBufferFull errors caused by producing too much MIDI
        output in one render call, set this property to increase the buffer.

        This only provides a recommendation to the framework.
*/
@property (NS_NONATOMIC_IOSONLY) NSInteger MIDIOutputBufferSizeHint API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!	@method	shouldChangeToFormat:forBus:
    @param format
        An AVAudioFormat which is proposed as the new format.
    @param bus
        The AUAudioUnitBus on which the format will be changed.
	@discussion
        This is called when setting the format on an AUAudioUnitBus.
        The bus has already checked that the format meets the channel constraints of the bus.
        The AU can override this method to check before allowing a new format to be set on the bus.
        If this method returns NO, then the new format will not be set on the bus.
        The default implementation returns NO if the unit has renderResourcesAllocated, otherwise it results YES.
*/
- (BOOL)shouldChangeToFormat:(AVAudioFormat *)format forBus:(AUAudioUnitBus *)bus;

/*!	@method	setRenderResourcesAllocated:
    @param flag
        In the base class implementation of allocateRenderResourcesAndReturnError:, the property renderResourcesAllocated is set to YES.
        If allocateRenderResourcesAndReturnError: should fail in a subclass, subclassers must use this method to set renderResourcesAllocated to NO.
*/
- (void)setRenderResourcesAllocated:(BOOL)flag;

@end

// =================================================================================================

/// Aspects of AUAudioUnitBus of interest only to the implementation of v3 AUs.
@interface AUAudioUnitBus (AUAudioUnitImplementation)

/*!	@method		initWithFormat:error:
	@brief		initialize with a default format.
	@param format	The initial format for the bus.
	@param outError	An error if the format is unsupported for the bus.
*/
- (nullable instancetype)initWithFormat:(AVAudioFormat *)format error:(NSError **)outError;

/*!	@property	supportedChannelCounts
	@brief		An array of numbers giving the supported numbers of channels for this bus.
	@discussion
		If supportedChannelCounts is nil, then any number less than or equal to maximumChannelCount
		is supported. If setting supportedChannelCounts makes the current format unsupported, then
		format will be set to nil. The default value is nil.
*/
@property (nonatomic, retain, nullable) NSArray<NSNumber *> *supportedChannelCounts;

/*!	@property	maximumChannelCount
	@brief		The maximum numbers of channels supported for this bus.
	@discussion
		If supportedChannelCounts is set, then this value is derived from supportedChannelCounts. If
		setting maximumChannelCount makes the current format unsupported, then format will be set to
		nil. The default value is UINT_MAX.
*/
@property (nonatomic) AUAudioChannelCount maximumChannelCount;

@end


// =================================================================================================

/// Aspects of AUAudioUnitBusArray of interest only to subclassers.
@interface AUAudioUnitBusArray (AUAudioUnitBusImplementation)

/// Sets the bus array to be a copy of the supplied array. The base class issues KVO notifications.
- (void)replaceBusses:(NSArray <AUAudioUnitBus *> *)busArray;

@end

// =================================================================================================

/*!	Factory methods for building parameters, parameter groups, and parameter trees.

	@note In non-ARC code, "create" methods return unretained objects (unlike "create" 
	C functions); the caller should generally retain them.
*/
@interface AUParameterTree (Factory)

///	Create an AUParameter.
/// See AUParameter's properties for descriptions of the arguments.
+ (AUParameter *)createParameterWithIdentifier:(NSString *)identifier name:(NSString *)name address:(AUParameterAddress)address min:(AUValue)min max:(AUValue)max unit:(AudioUnitParameterUnit)unit unitName:(NSString * __nullable)unitName flags:(AudioUnitParameterOptions)flags valueStrings:(NSArray<NSString *> *__nullable)valueStrings dependentParameters:(NSArray<NSNumber *> *__nullable)dependentParameters;

/*!	@brief	Create an AUParameterGroup.
	@param identifier	An identifier for the group (non-localized, persistent).
	@param name			The group's human-readable name (localized).
	@param children		The group's child nodes.
*/
+ (AUParameterGroup *)createGroupWithIdentifier:(NSString *)identifier name:(NSString *)name children:(NSArray<AUParameterNode *> *)children;

/*!	@brief		Create a template group which may be used as a prototype for further group instances.

	@discussion
		Template groups provide a way to construct multiple instances of identical parameter
		groups, sharing certain immutable state between the instances.

		Template groups may not appear in trees except at the root.
*/
+ (AUParameterGroup *)createGroupTemplate:(NSArray<AUParameterNode *> *)children;

/*!	@brief	Initialize a group as a copied instance of a template group.
	@param templateGroup	A group to be used as a template and largely copied.
	@param identifier		An identifier for the new group (non-localized, persistent).
	@param name				The new group's human-readable name (localized).
	@param addressOffset	The new group's parameters' addresses will be offset from those in
							the template by this value.
*/
+ (AUParameterGroup *)createGroupFromTemplate:(AUParameterGroup *)templateGroup identifier:(NSString *)identifier name:(NSString *)name addressOffset:(AUParameterAddress)addressOffset;

/*!	@brief	Create an AUParameterTree.
	@param children		The tree's top-level child nodes.
*/
+ (AUParameterTree *)createTreeWithChildren:(NSArray<AUParameterNode *> *)children;

@end

// =================================================================================================

/// A block called to notify the AUAudioUnit implementation of changes to AUParameter values.
typedef void (^AUImplementorValueObserver)(AUParameter *param, AUValue value);

/// A block called to fetch an AUParameter's current value from the AUAudioUnit implementation.
typedef AUValue (^AUImplementorValueProvider)(AUParameter *param);

/// A block called to convert an AUParameter's value to a string.
typedef NSString *__nonnull (^AUImplementorStringFromValueCallback)(AUParameter *param, const AUValue *__nullable value);

/// A block called to convert a string to an AUParameter's value.
typedef AUValue (^AUImplementorValueFromStringCallback)(AUParameter *param, NSString *string);

/// A block called to return a group or parameter's localized display name, abbreviated to the requested length.
typedef NSString *__nonnull (^AUImplementorDisplayNameWithLengthCallback)(AUParameterNode *node, NSInteger desiredLength);

/// Aspects of AUParameterNode of interest only to AUAudioUnit subclassers.
@interface AUParameterNode (AUParameterNodeImplementation)
/*!	@brief		Called when a parameter changes value.
	@discussion
		This block, used only in an audio unit implementation, receives all externally-generated
		changes to parameter values. It should store the new value in its audio signal processing
		state (assuming that that state is separate from the AUParameter object).
*/
@property (NS_NONATOMIC_IOSONLY, copy) AUImplementorValueObserver implementorValueObserver;

/*!	@brief		Called when a value of a parameter in the tree is known to have a stale value
				needing to be refreshed.
	@discussion
		The audio unit should return the current value for this parameter; the AUParameterNode will
		store the value.
*/
@property (NS_NONATOMIC_IOSONLY, copy) AUImplementorValueProvider implementorValueProvider;

///	Called to provide string representations of parameter values.
///	If value is nil, the callback uses the current value of the parameter.
@property (NS_NONATOMIC_IOSONLY, copy) AUImplementorStringFromValueCallback implementorStringFromValueCallback;

/// Called to convert string to numeric representations of parameter values.
@property (NS_NONATOMIC_IOSONLY, copy) AUImplementorValueFromStringCallback implementorValueFromStringCallback;

/// Called to obtain an abbreviated version of a parameter or group name.
@property (NS_NONATOMIC_IOSONLY, copy) AUImplementorDisplayNameWithLengthCallback implementorDisplayNameWithLengthCallback;
@end

// =================================================================================================

/*!	@brief	Wraps a v2 audio unit in an AUAudioUnit subclass.
	@discussion
		Implementors of version 3 audio units may derive their implementations from
		AUAudioUnitV2Bridge. It expects the component description with which it is initialized to
		refer to a registered component with a v2 implementation using an
		AudioComponentFactoryFunction. The bridge will instantiate the v2 audio unit via the factory
		function and communicate it with it using the v2 AudioUnit API's (AudioUnitSetProperty,
		etc.)

		Hosts should not access this class; it will be instantiated when needed when creating an
		AUAudioUnit.
*/
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface AUAudioUnitV2Bridge : AUAudioUnit
@end

// =================================================================================================

/*!	@brief	Protocol to which principal classes of v3 audio units (extensions) must conform.
	@discussion
		The principal class of a non-UI v3 audio unit extension will generally derive from NSObject
		and implement this protocol.
		
		The principal class of a UI v3 audio unit extension must derive from AUViewController and
		implement this protocol.
*/
@protocol AUAudioUnitFactory <NSExtensionRequestHandling>

/*!	@brief	Create an instance of an extension's AUAudioUnit.
	@discussion
		This method should create and return an instance of its audio unit.
		
		This method will be called only once per instance of the factory.
		
		Note that in non-ARC code, "create" methods return unretained objects (unlike "create" 
		C functions); the implementor should return an object with reference count 1 but
		autoreleased.
*/
- (nullable AUAudioUnit *)createAudioUnitWithComponentDescription:(AudioComponentDescription)desc error:(NSError **)error;
@end


NS_ASSUME_NONNULL_END

#endif // __OBJC2__
#endif // AudioToolbox_AUAudioUnitImplementation_h
#else
#include <AudioToolboxCore/AUAudioUnitImplementation.h>
#endif
// ==========  AudioToolbox.framework/Headers/AudioOutputUnit.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AudioOutputUnit.h>)
/*!
	@file		AudioOutputUnit.h
 	@framework	AudioToolbox.framework
 	@copyright	(c) 2000-2015 Apple, Inc. All rights reserved.
	@brief		Additional Audio Unit API for audio input/output units.
*/

#ifndef AudioUnit_AudioOutputUnit_h
#define AudioUnit_AudioOutputUnit_h

#include <Availability.h>
#include <AudioToolbox/AUComponent.h>

CF_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
//	Start/stop methods for output units
//-----------------------------------------------------------------------------
extern OSStatus
AudioOutputUnitStart(	AudioUnit	ci)											API_AVAILABLE(macos(10.0), ios(2.0), watchos(2.0), tvos(9.0));

extern OSStatus
AudioOutputUnitStop(	AudioUnit	ci)											API_AVAILABLE(macos(10.0), ios(2.0), watchos(2.0), tvos(9.0));

//-----------------------------------------------------------------------------
//	Selectors for component and audio plugin calls
//-----------------------------------------------------------------------------
enum {
	kAudioOutputUnitRange						= 0x0200,	// selector range
	kAudioOutputUnitStartSelect					= 0x0201,
	kAudioOutputUnitStopSelect					= 0x0202
};

/*!
*/
typedef OSStatus	(*AudioOutputUnitStartProc) (void *self);

/*!
*/
typedef OSStatus	(*AudioOutputUnitStopProc) (void *self);


#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif /* AudioUnit_AudioOutputUnit_h */
#else
#include <AudioToolboxCore/AudioOutputUnit.h>
#endif
// ==========  AudioToolbox.framework/Headers/AUComponent.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AUComponent.h>)
/*!
	@file		AUComponent.h
 	@framework	AudioUnit.framework
 	@copyright	(c) 2002-2015 Apple, Inc. All rights reserved.
	@brief		C interfaces for working with Audio Units.

	@discussion

	An audio unit is a plugin that can be loaded into an application's process and used to process
	or generate audio. An audio unit is an AudioComponent type and so the AudioComponent APIs are
	used to find specific types of audio units, open and close them.

	Audio units use a general notion of description to specify an unique instance. The Type is the 
	general category of an audio unit. The SubType is an unique identifier specified by the 
	Manufacturer (provider) of the audio unit. The IDs that are used for Type are specified by 
	Apple, the Manufacturer ID should be specified by an unique identifier
	(as registered with apple). See AudioComponentDescription.

	Audio unit types are of the following (see below for more information)

		kAudioUnitType_Output					= 'auou',
		kAudioUnitType_MusicDevice				= 'aumu',
		kAudioUnitType_MusicEffect				= 'aumf',
		kAudioUnitType_FormatConverter			= 'aufc',	
		kAudioUnitType_Effect					= 'aufx',	
		kAudioUnitType_Mixer					= 'aumx',
		kAudioUnitType_Panner					= 'aupn',
		kAudioUnitType_OfflineEffect			= 'auol',
		kAudioUnitType_Generator				= 'augn',

	An audio unit's general operations are:
		- Open an audio unit (AudioComponentInstanceNew)
		- Configure it based on the context (AudioUnitSetProperty)
		- Initialize the audio unit (AudioUnitInitialize)
			- at this point the audio unit is in a state where it can render audio
		- Render audio (AudioUnitRender)
		
	An important part of a render operation for an audio unit is to manipulate the various controls 
	that the unit provides to change the render effects; for instance to change the decay time of 
	a reverb, the cut off frequency of a filter, etc. These are called parameters, and 
	AudioUnitGetParameter and AudioUnitSetParameter are used to interact with these.

	If any reconfiguration of the audio unit is required, then:
		- Uninitialize (AudioUnitUninitialize)
		- Configure it based on the context (AudioUnitSetProperty)
		- Initialize the audio unit (AudioUnitInitialize)

	Once the host is finished with an audio unit, it closes it:
		- Dispose the audio unit (AudioComponentInstanceDispose)

	Audio units can be used programmatically (for instance, mixers can be used to render audio for a
	game, a generator to play audio files, etc), or they can be hosted in Digital Audio Workstation
	(DAW) applications such as Logic, Garage Band, etc. In the DAW case, it is common for an audio
	unit to provide a custom view to allow the user to interact with what can be complex DSP
	operations that the audio unit performs. The view is retrieved from an audio unit through
	AudioUnitGetProperty and then the host instantiates it (see <AudioToolbox/AUCocoaUIView.h>).
*/
#ifndef AudioUnit_AUComponent_h
#define AudioUnit_AUComponent_h

//================================================================================================
#pragma mark Overview

#include <AudioToolbox/AudioComponent.h>

CF_ASSUME_NONNULL_BEGIN

#define AU_SUPPORT_INTERAPP_AUDIO (TARGET_OS_IPHONE && !TARGET_OS_UIKITFORMAC)

#define INTERAPP_AUDIO_DEPRECATED API_DEPRECATED("Inter-App Audio API is deprecated in favor of Audio Units", ios(7.0, 13.0), watchos(2.0, 6.0), tvos(9.0, 13.0))


#ifdef __cplusplus
extern "C" {
#endif

//================================================================================================
#pragma mark -
#pragma mark Audio Unit Types
/*!
	@typedef			AudioUnit
	@discussion			An audio unit is of type AudioComponentInstance as defined in 
						AudioComponent.h
*/
typedef AudioComponentInstance AudioUnit;


/*!
    @enum           Audio Unit Types
    @abstract		different types of audio units
	@discussion		Audio units are classified into different types, where those types perform 
					different roles and functions.
					There are some general categories of functionality that apply across different 
					types of audio units:
					(1) Real-time usage
						The audio unit will complete its operations in less time than is 
						represented by the render buffer. All audio units with the exception of 
						the OfflineEffect should meet this criteria
					(2) Real-time I/O
						Will request the same amount of audio input as it is being asked to 
						produce for output. Effects, Panners, Mixers and MusicDevices are required 
						to adhere to this restriction. FormatConverter's can with some constraints
						be used in this situation (for instance, sample rate conversion, float-int),
						but the host of the audio unit is responsible for insuring this.
					(3) UI versus Programmatic usage
						UI usage covers the case of using an audio unit in a Digital Audio 
						Workstation (DAW) with appropriate UI (for example a filter in Garage Band 
						or Logic). Effects, Panners, MusicDevices are all expected to be usable 
						within this context. 
						Programmatic usage is where an audio unit is used by a host app as part of
						a general signal processing chain.
						For instance, a mixer audio unit can be used to take several different 
						audio sources in a game and mix them together. Mixers, Output units are 
						for programmatic usage. FormatConverter and Generator types are generally
						programmatic audio units, but if they can be used in a UI situation, they 
						specify a custom view. The app can then use that to decide that, with 
						appropriate constraints, the audio unit could be presented in a DAW type 
						application. For instance, the AUConverter audio unit from apple can do 
						sample rate conversion, etc, but has not general utility for a user in a 
						DAW app. Apple's Varispeed or AUTimePitch audio units can be used to change
						the playback rate and pitch and so could be used to good affect by a user 
						in a DAW type environment, as well as just providing this general 
						functionality to any program.
					
	@constant		kAudioUnitType_Output
					An output unit can be used as the head of an AUGraph. Apple provides a number 
					of output units that interface directly with an audio device
					
	@constant		kAudioUnitType_MusicDevice
					Used to describe software musical instruments such as samplers and 
					synthesisers. They respond to MIDI and create notes, which are then controlled
					through parameters or MIDI control messages. See <AudioToolbox/MusicDevice.h>
										
	@constant		kAudioUnitType_MusicEffect
					Is an effect that is also able to respond directly to MIDI control messages, 
					typically through the mapping of these MIDI messages to different parameters 
					of the effect's DSP algorithm.
					
	@constant		kAudioUnitType_FormatConverter
					A format converter is a general category for audio units that can change the 
					format (for instance, sample rate conversion) from an input to an output, as 
					well as other, non-I/O type manipulations (like a deferred render or varispeed 
					type of operation). As such, a format converter can ask for as much or as 
					little audio input to produce a given output. They are still expected to
					complete their rendering within the time represented by the output buffer. 
					For format converters that have some utility as an "audio effect or processor", 
					it is quite common to provide an offline version of this audio unit as well. 
					For instance, Apple ships a format converter (for use in a "real-time" like 
					situation) and an offline version (for processing audio files) of the Time 
					Pitch and Varispeed audio units.
					
	@constant		kAudioUnitType_Effect
					An audio unit that will process some x number of audio input samples to produce 
					x number of audio output samples. The common case for an effect is to have a 
					single input to a single output, though some effects take side-chain inputs as 
					well. Effects can be run in "offline" contexts (such as processing a file), but 
					they are expected to run in real-time. A delay unit or reverb is a good 
					example of this.
					
	@constant		kAudioUnitType_Mixer
					An audio unit that takes some number of inputs, mixing them to provide 1 or 
					more audio outputs. A stere mixer (mono and stereo inputs to produce one 
					stereo output) is an example of this.
					
	@constant		kAudioUnitType_Panner
					A panner is a specialised effect that will pan a single audio input to a single
					output. Panner units are required to support a collection of standardised 
					parameters that specify the panning coordinates (aside from whatever custom 
					parameters the panner may provide). A surround panner is an example of this
					
	@constant		kAudioUnitType_Generator
					A generator will have no audio input, but will just produce audio output. In 
					some ways it is similar to a MusicDevice, except that a generator provides no 
					MIDI input, or notion of "notes". A tone generator is a good example of this.
					
	@constant		kAudioUnitType_OfflineEffect
					An offline effect is used to process data from a file and is also used to 
					publish a capability that cannot be run in real-time. For instance, the process
					of normalisation requires seeing the entire audio input before the scalar to 
					apply in the normalisation process can be estimated. As such, offline effects 
					also have a notion of a priming stage that can be performed before the actual 
					rendering/processing phase is executed.

    @constant		kAudioUnitType_MIDIProcessor
                    Plugins of this type process midi input and produce midi output. They do not produce audio.

*/
CF_ENUM(UInt32) {
	kAudioUnitType_Output					= 'auou',
	kAudioUnitType_MusicDevice				= 'aumu',
	kAudioUnitType_MusicEffect				= 'aumf',
	kAudioUnitType_FormatConverter			= 'aufc',
	kAudioUnitType_Effect					= 'aufx',
	kAudioUnitType_Mixer					= 'aumx',
	kAudioUnitType_Panner					= 'aupn',
	kAudioUnitType_Generator				= 'augn',
	kAudioUnitType_OfflineEffect			= 'auol',
	kAudioUnitType_MIDIProcessor			= 'aumi'
};

#if AU_SUPPORT_INTERAPP_AUDIO
/*!
    @enum           Audio Unit Types (for inter-app audio)
    @abstract		types of inter-app audio units

    @constant       kAudioUnitType_RemoteEffect
    @constant       kAudioUnitType_RemoteGenerator
    @constant       kAudioUnitType_RemoteInstrument
    @constant       kAudioUnitType_RemoteMusicEffect
	
	@discussion
        These Audio Unit types are identical to the corresponding "non-remote" types (e.g.
        kAudioUnitType_Effect, etc.), with the exception that they are the types that must be
        used for AudioUnits defined by applications calling AudioOutputUnitPublish.

		When Audio Components of these types are instantiated via AudioComponentInstanceNew,
		a connection is made to the process which published the component via AudioOutputUnitPublish.

		When using Audio Units which are instances of these components, one must take care to
		initialize the unit only immediately before beginning a series of render operations, and
		uninitialize it immediately afterwards, since while initialized, the Audio Unit's background
		process is being kept awake and is consuming system resources.
		
		When using AudioUnitGetProperty and AudioUnitSetProperty, only Apple-defined properties
		are supported.

		For kAudioUnitProperty_HostCallbacks, hosts can set this property on any remote audio unit.
		This will cause the host callbacks to be called on each render cycle and the results 
		communicated to the remote AU's process. The owner of the published AU ("node") can *get*
		this property on its output units, obtaining the structure of function pointers, and call
		the host callbacks during the render cycle.
*/
CF_ENUM(UInt32) {
    kAudioUnitType_RemoteEffect         = 'aurx',
    kAudioUnitType_RemoteGenerator      = 'aurg',
    kAudioUnitType_RemoteInstrument     = 'auri',
    kAudioUnitType_RemoteMusicEffect    = 'aurm'
};
#endif

//================================================================================================
#pragma mark -
#pragma mark Apple Audio Units
/*!
    @enum           Apple audio unit manufacturer ID.
    @discussion		the unique ID used to identifier audio units provided by Apple, Inc.
*/
CF_ENUM(UInt32) {
	kAudioUnitManufacturer_Apple			= 'appl'
};
	
/*!
	@enum			Apple input/output audio unit sub types
	@discussion		These are the subtypes for the various input/output units that Apple ships. Input/output
					units add an additional notion of Start and Stop.
					see <AudioToolbox/AudioOutputUnit.h>

	@constant		kAudioUnitSubType_GenericOutput
					A generic output unit provides the start/stop API, and provides the basic 
					services to convert Linear PCM formats.

	@constant		kAudioUnitSubType_VoiceProcessingIO
						- Available on OS X and with iOS 3.0 or greater
					This audio unit can do input as well as output. Bus 0 is used for the output 
					side, bus 1 is used to get audio input (thus, on the iPhone, it works in a 
					very similar way to the Remote I/O). This audio unit does signal processing on 
					the incoming audio (taking out any of the audio that is played from the device 
					at a given time from the incoming audio).
*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_GenericOutput			= 'genr',
	kAudioUnitSubType_VoiceProcessingIO		= 'vpio'
};

#if !TARGET_OS_IPHONE
/*!
	@enum			Apple input/output audio unit sub types (OS X)
	@constant		kAudioUnitSubType_HALOutput			
						- desktop only (a.k.a. "AUHAL")
					The audio unit that interfaces to any audio device. The user specifies which 
					audio device to track. The audio unit can do input from the device as well as 
					output to the device. Bus 0 is used for the output side, bus 1 is used
					to get audio input from the device.
					
	@constant		kAudioUnitSubType_DefaultOutput		
						- desktop only
					A specialisation of AUHAL that is used to track the user's selection of the 
					default device as set in the Sound Prefs
					
	@constant		kAudioUnitSubType_SystemOutput		
						- desktop only
					A specialisation of AUHAL that is used to track the user's selection of the 
					device to use for sound effects, alerts
					and other UI sounds.

*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_HALOutput				= 'ahal',
	kAudioUnitSubType_DefaultOutput			= 'def ',
	kAudioUnitSubType_SystemOutput			= 'sys ',
};
#else
/*!
	@enum			Apple input/output audio unit sub types (iOS)
	@constant		kAudioUnitSubType_RemoteIO			
					The audio unit that interfaces to the iOS audio system. The
					audio unit can do input as well as output. Bus 0 is used for the output side, 
					bus 1 is used to get audio input.
*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_RemoteIO				= 'rioc',
};
#endif

/*!
	@enum			Apple music instrument audio unit sub types 

	@constant		kAudioUnitSubType_DLSSynth			
						- desktop only
					A multi-timbral music device that can use sample banks in either DLS or 
					SoundFont formats. It fully supports GM-MIDI and the basic extensions of 
					GS-MIDI.
	@constant		kAudioUnitSubType_Sampler
					A mono-timbral music device which is a sampler synthesizer and supports full 
					interactive editing of all state.
	@constant		kAudioUnitSubType_MIDISynth
					A fully GM-compatible multi-timbral music device which is a sampler synthesizer.
					It can load instruments from sample banks in either DLS or SoundFont formats.
*/
CF_ENUM(UInt32) {
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_DLSSynth				= 'dls ',
#endif
	kAudioUnitSubType_Sampler				= 'samp',
	kAudioUnitSubType_MIDISynth				= 'msyn'
};

/*!
	@enum			Apple converter audio unit sub types 
	@discussion		These are the subtypes for the various converter units that apple ships. 
					Except for AUConverter, which is available on both desktop and iPhone, these 
					audio units are only available on the desktop.

	@constant		kAudioUnitSubType_AUConverter
					An audio unit that uses an AudioConverter to do Linear PCM conversions (sample 
					rate, bit depth, interleaving).

	@constant		kAudioUnitSubType_Varispeed
					An audio unit that can be used to control playback rate (as the rate is faster, 
					the pitch is higher). It provides a generic view, so can be used in both a UI 
					and programmatic context. It also comes in an Offline version so can be used 
					to process audio files.
					
	@constant		kAudioUnitSubType_DeferredRenderer
					An audio unit that is used to get its input from a separate thread than the 
					thread that its render method is called. It thus allows an application to 
					introduce multiple threads into a rendering graph. There is a buffer sized 
					delay introduced between the input and output
					
	@constant		kAudioUnitSubType_Splitter
                    An audio unit that provides 2 output buses and 1 input bus. The audio unit
                    splits (duplicates) the input signal to the two output buses
 
	@constant		kAudioUnitSubType_MultiSplitter
                    An audio unit that sends its input bus to any number of output buses.
                    Every output bus gets all channels of the input bus.
                    This unit's implementation is lighter weight than kAudioUnitSubType_Splitter 
                    even for two output buses, and is recommended over kAudioUnitSubType_Splitter.
 
	@constant		kAudioUnitSubType_Merger
					An audio unit that provides 2 input buses and 2 output bus. The audio unit
					merges the two inputs to the single output

	@constant		kAudioUnitSubType_NewTimePitch
					An audio unit that provides good quality time stretching and pitch shifting 
					while still being very fast.

	@constant		kAudioUnitSubType_AUiPodTimeOther
					An audio unit that provides time domain time stretching.

*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_AUConverter			= 'conv',
	kAudioUnitSubType_Varispeed				= 'vari',
	kAudioUnitSubType_DeferredRenderer		= 'defr',
	kAudioUnitSubType_Splitter				= 'splt',
	kAudioUnitSubType_MultiSplitter			= 'mspl',
	kAudioUnitSubType_Merger				= 'merg',
	kAudioUnitSubType_NewTimePitch			= 'nutp',
	kAudioUnitSubType_AUiPodTimeOther		= 'ipto',
	kAudioUnitSubType_RoundTripAAC			= 'raac',
};

#if !TARGET_OS_IPHONE
/*!
	@enum			Apple converter audio unit sub types (OS X only)
	@constant		kAudioUnitSubType_TimePitch
					An audio unit that can be used to have independent control of both playback
					rate and pitch. It provides a generic view, so can be used in both a UI and 
					programmatic context. It also comes in an Offline version so can be used to 
					process audio files.
					
*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_TimePitch				= 'tmpt'
};
#elif !TARGET_OS_UIKITFORMAC
/*!
	@enum			Apple converter audio unit sub types (iOS only)
	@constant		kAudioUnitSubType_AUiPodTime
					An audio unit that provides simple (and limited) control over playback rate
					and time.
*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_AUiPodTime API_DEPRECATED_WITH_REPLACEMENT("kAudioUnitSubType_NewTimePitch", ios(2.0, 13.0), watchos(2.0, 6.0), tvos(9.0, 13.0)) API_UNAVAILABLE(macos)	= 'iptm'
};
#endif

/*!
	@enum			Apple effect audio unit sub types 
	@discussion		These are the subtypes for the various effect units that apple ships

	@constant		kAudioUnitSubType_Delay					
						- desktop only
					A delay audio unit
					
	@constant		kAudioUnitSubType_LowPassFilter			
					A filter that passes frequencies below a specified cut-off frequency
					
	@constant		kAudioUnitSubType_HighPassFilter		
					A filter that passes frequencies above a specified cut-off frequency
					
	@constant		kAudioUnitSubType_BandPassFilter		
					A filter that passes frequencies between a low and high cut-off frequency.
					
	@constant		kAudioUnitSubType_HighShelfFilter		
					A filter that can be used to implement a "treble" control
					
	@constant		kAudioUnitSubType_LowShelfFilter		
					A filter that can be used to implement a "bass" control

	@constant		kAudioUnitSubType_ParametricEQ			
					A parametric EQ filter
					
	@constant		kAudioUnitSubType_PeakLimiter
					A peak limiter
					
	@constant		kAudioUnitSubType_DynamicsProcessor		
					A dynamics compressor/expander
					
	@constant		kAudioUnitSubType_SampleDelay
						- desktop only
					A delay that is used to delay the input a specified number of samples until 
					the output
					
	@constant		kAudioUnitSubType_Distortion
					A distortion audio unit 
					
	@constant		kAudioUnitSubType_NBandEQ
					A generalized N-band graphic EQ with specifiable filter types per-band

    @constant       kAudioUnitSubType_Reverb2
                    A lite reverb that can be used to simulate various and different spaces

*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_PeakLimiter			= 'lmtr',
	kAudioUnitSubType_DynamicsProcessor		= 'dcmp',
	kAudioUnitSubType_LowPassFilter			= 'lpas',
	kAudioUnitSubType_HighPassFilter		= 'hpas',
	kAudioUnitSubType_BandPassFilter		= 'bpas',
	kAudioUnitSubType_HighShelfFilter		= 'hshf',
	kAudioUnitSubType_LowShelfFilter		= 'lshf',
	kAudioUnitSubType_ParametricEQ			= 'pmeq',
	kAudioUnitSubType_Distortion			= 'dist',
	kAudioUnitSubType_Delay					= 'dely',
	kAudioUnitSubType_SampleDelay			= 'sdly',
	kAudioUnitSubType_NBandEQ				= 'nbeq',
#if !TARGET_OS_UIKITFORMAC
    kAudioUnitSubType_Reverb2               = 'rvb2'
#endif
};

#if !TARGET_OS_IPHONE
/*!
	@enum			Apple effect audio unit sub types (OS X only)
	@constant		kAudioUnitSubType_GraphicEQ				
					A 10 or 31 band Graphic EQ
	@constant		kAudioUnitSubType_MultiBandCompressor	
					A 4 band compressor/expander
	@constant		kAudioUnitSubType_MatrixReverb
					A reverb that can be used to simulate various and different spaces
	@constant		kAudioUnitSubType_Pitch					
					An audio unit used to change the pitch
	@constant		kAudioUnitSubType_AUFilter
					A filter unit that combines 5 different filters (low, 3 mids, high)
	@constant		kAudioUnitSubType_NetSend
					An audio unit that is used in conjunction with _NetReceive to send audio
					across the network (or between different applications)
	@constant		kAudioUnitSubType_RogerBeep				
					An audio unit that can be used to emit a short tone in gaps between speech
					- similar to the tones used in a walkie-talkie
*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_GraphicEQ				= 'greq',
	kAudioUnitSubType_MultiBandCompressor	= 'mcmp',
	kAudioUnitSubType_MatrixReverb			= 'mrev',
	kAudioUnitSubType_Pitch					= 'tmpt',
	kAudioUnitSubType_AUFilter				= 'filt',
	kAudioUnitSubType_NetSend				= 'nsnd',
	kAudioUnitSubType_RogerBeep				= 'rogr'
};
#elif !TARGET_OS_UIKITFORMAC
/*!
	@enum			Apple effect audio unit sub types (iOS only)
	@constant		kAudioUnitSubType_AUiPodEQ
					A simple graphic EQ with common presets
*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_AUiPodEQ API_DEPRECATED_WITH_REPLACEMENT("kAudioUnitSubType_GraphicEQ", ios(2.0, 13.0), watchos(2.0, 6.0), tvos(9.0, 13.0)) API_UNAVAILABLE(macos)	= 'ipeq'
};
#endif



/*!
	@enum			Apple mixer audio unit sub types 
	@discussion		These are the subtypes for the various mixer units that apple ships

	@constant		kAudioUnitSubType_MultiChannelMixer
					Can have any number of inputs, with any number of channels on any input to one 
					output bus with any number of channels.
 
    @constant       kAudioUnitSubType_SpatialMixer
                    Inputs that are mono will be panned around using 3D coordinates and parameters.
                    Stereo inputs are passed directly through to the output.
                    A single output is presented with 2, 4, 5, 6, 7 or 8 channels.
                    There is also a built in reverb.
	
	@constant		kAudioUnitSubType_MatrixMixer
					Any number of input and output buses with any number of channels on any bus. 
					The mix is presented as a matrix of channels that can be controlled through 
					input volume per channel, "cross-point" volume (a given input channel to a 
					given output channel), output volume per channel and a global volume across 
					the whole matrix
 

*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_MultiChannelMixer		= 'mcmx',
	kAudioUnitSubType_MatrixMixer			= 'mxmx',
    kAudioUnitSubType_SpatialMixer          = '3dem',
};

#if !TARGET_OS_IPHONE
/*!
	@enum			Apple mixer audio unit sub types (OS X only)
	@constant		kAudioUnitSubType_StereoMixer
					Inputs can be mono or stereo. Single stereo output
					
    @constant		kAudioUnitSubType_3DMixer
                    (deprecated, use kAudioUnitSubType_SpatialMixer instead)
                    Inputs can be mono, in which case they can be panned around using 3D
                    coordinates and parameters.
                    Stereo inputs are passed directly through to the output.
                    4 channel "ambisonic" inputs will be rendered to the output configuration
                    A single output of 2, 4, 5, 6, 7 or 8 channels.
*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_StereoMixer			= 'smxr',
	kAudioUnitSubType_3DMixer API_DEPRECATED("no longer supported", macos(10.3, 10.10)) API_UNAVAILABLE(ios, watchos, tvos)
											= '3dmx',
											// use kAudioUnitSubType_SpatialMixer instead
};
#else
/*!
	@enum			Apple mixer audio unit sub types (iOS only)
	@constant		kAudioUnitSubType_AU3DMixerEmbedded
						- iPhone only (renamed to kAudioUnitSubType_SpatialMixer)
					A scaled-down version of the AU3DMixer that presents a stereo output, mono or 
					stereo inputs
*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_AU3DMixerEmbedded	__attribute__((deprecated("renamed to kAudioUnitSubType_SpatialMixer")))
											= '3dem' 
};
#endif

/*!
	@enum			Apple panner audio unit sub types 
	@discussion		These are the subtypes for the various panner units that apple ships

	@constant		kAudioUnitSubType_SphericalHeadPanner
						- desktop only
					A panner unit that uses the spherical head model to pan to a stereo output
					
	@constant		kAudioUnitSubType_VectorPanner
						- desktop only
					A panner unit that uses a moving pan between the two closes, adjacent channels 
					in a 3D space to a
					surround output
					
	@constant		kAudioUnitSubType_SoundFieldPanner
						- desktop only
					A panner unit that uses a sound-field notion to pan to a surround output
					
	@constant		kAudioUnitSubType_HRTFPanner
						- desktop only
					A panner unit that uses a generic "HRTF" model to pan to a stereo output
*/
#if !TARGET_OS_IPHONE
CF_ENUM(UInt32) {
	kAudioUnitSubType_SphericalHeadPanner	= 'sphr',
	kAudioUnitSubType_VectorPanner			= 'vbas',
	kAudioUnitSubType_SoundFieldPanner		= 'ambi',
	kAudioUnitSubType_HRTFPanner			= 'hrtf'
};
#endif

/*!
	@enum			Apple generator audio unit sub types 
	@discussion		These are the subtypes for the various generator units that apple ships

	@constant		kAudioUnitSubType_ScheduledSoundPlayer
					A generator unit that can be used to schedule slices of audio to be played at 
					a specified time. The audio is scheduled using the time stamps for the render 
					operation, and can be scheduled from any thread.
					
	@constant		kAudioUnitSubType_AudioFilePlayer
					A generator unit that is used to play a file. It presents a custom UI so can 
					be used in a UI context as well
					
	@constant		kAudioUnitSubType_NetReceive
						- desktop only
					A generator unit that is paired with _NetSend to receive the audio that unit 
					sends. It presents a custom UI so can be used in a UI context as well
*/
CF_ENUM(UInt32) {
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_NetReceive			= 'nrcv',
#endif
	kAudioUnitSubType_ScheduledSoundPlayer	= 'sspl',
	kAudioUnitSubType_AudioFilePlayer		= 'afpl'
};


//================================================================================================
#pragma mark -
#pragma mark Audio Unit Constants and typedefs
/*!
	@enum			AudioUnitRenderActionFlags
	@discussion		These flags can be set in a callback from an audio unit during an audio unit 
					render operation from either the RenderNotify Proc or the render input 
					callback.

	@constant		kAudioUnitRenderAction_PreRender
					Called on a render notification Proc - which is called either before or after 
					the render operation of the audio unit. If this flag is set, the proc is being 
					called before the render operation is performed.
					
	@constant		kAudioUnitRenderAction_PostRender
					Called on a render notification Proc - which is called either before or after 
					the render operation of the audio unit. If this flag is set, the proc is being 
					called after the render operation is completed.

	@constant		kAudioUnitRenderAction_OutputIsSilence
					The originator of a buffer, in a render input callback, or in an audio unit's
					render operation, may use this flag to indicate that the buffer contains
					only silence.

					The receiver of the buffer can then use the flag as a hint as to whether the
					buffer needs to be processed or not.

					Note that because the flag is only a hint, when setting the silence flag,
					the originator of a buffer must also ensure that it contains silence (zeroes).
					
	@constant		kAudioOfflineUnitRenderAction_Preflight
					This is used with offline audio units (of type 'auol'). It is used when an 
					offline unit is being preflighted, which is performed prior to the actual 
					offline rendering actions are performed. It is used for those cases where the 
					offline process needs it (for example, with an offline unit that normalises an 
					audio file, it needs to see all of the audio data first before it can perform 
					its normalisation)
					
	@constant		kAudioOfflineUnitRenderAction_Render
					Once an offline unit has been successfully preflighted, it is then put into 
					its render mode. So this flag is set to indicate to the audio unit that it is 
					now in that state and that it should perform its processing on the input data.
					
	@constant		kAudioOfflineUnitRenderAction_Complete
					This flag is set when an offline unit has completed either its preflight or 
					performed render operations
					
	@constant		kAudioUnitRenderAction_PostRenderError
					If this flag is set on the post-render call an error was returned by the 
					AUs render operation. In this case, the error can be retrieved through the 
					lastRenderError property and the audio data in ioData handed to the post-render 
					notification will be invalid.
	@constant		kAudioUnitRenderAction_DoNotCheckRenderArgs
					If this flag is set, then checks that are done on the arguments provided to render 
					are not performed. This can be useful to use to save computation time in
					situations where you are sure you are providing the correct arguments
					and structures to the various render calls
*/
typedef CF_OPTIONS(UInt32, AudioUnitRenderActionFlags)
{
	kAudioUnitRenderAction_PreRender			= (1UL << 2),
	kAudioUnitRenderAction_PostRender			= (1UL << 3),
	kAudioUnitRenderAction_OutputIsSilence		= (1UL << 4),
	kAudioOfflineUnitRenderAction_Preflight		= (1UL << 5),
	kAudioOfflineUnitRenderAction_Render		= (1UL << 6),
	kAudioOfflineUnitRenderAction_Complete		= (1UL << 7),
	kAudioUnitRenderAction_PostRenderError		= (1UL << 8),
	kAudioUnitRenderAction_DoNotCheckRenderArgs	= (1UL << 9)
};

/*!
	@enum			Audio unit errors
	@discussion		These are the various errors that can be returned by AudioUnit... API calls

	@constant		kAudioUnitErr_InvalidProperty
					The property is not supported
	@constant		kAudioUnitErr_InvalidParameter
					The parameter is not supported
	@constant		kAudioUnitErr_InvalidElement
					The specified element is not valid
	@constant		kAudioUnitErr_NoConnection
					There is no connection (generally an audio unit is asked to render but it has 
					not input from which to gather data)
	@constant		kAudioUnitErr_FailedInitialization
					The audio unit is unable to be initialized
	@constant		kAudioUnitErr_TooManyFramesToProcess
					When an audio unit is initialized it has a value which specifies the max 
					number of frames it will be asked to render at any given time. If an audio 
					unit is asked to render more than this, this error is returned.
	@constant		kAudioUnitErr_InvalidFile
					If an audio unit uses external files as a data source, this error is returned 
					if a file is invalid (Apple's DLS synth returns this error)
	@constant		kAudioUnitErr_UnknownFileType
					If an audio unit uses external files as a data source, this error is returned
					if a file is invalid (Apple's DLS synth returns this error)
	@constant		kAudioUnitErr_FileNotSpecified
					If an audio unit uses external files as a data source, this error is returned
					if a file hasn't been set on it 
					(Apple's DLS synth returns this error)
	@constant		kAudioUnitErr_FormatNotSupported
					Returned if an input or output format is not supported
	@constant		kAudioUnitErr_Uninitialized
					Returned if an operation requires an audio unit to be initialized and it is 
					not.
	@constant		kAudioUnitErr_InvalidScope
					The specified scope is invalid
	@constant		kAudioUnitErr_PropertyNotWritable
					The property cannot be written
	@constant		kAudioUnitErr_CannotDoInCurrentContext
					Returned when an audio unit is in a state where it can't perform the requested 
					action now - but it could later. Its usually used to guard a render operation 
					when a reconfiguration of its internal state is being performed.
	@constant		kAudioUnitErr_InvalidPropertyValue
					The property is valid, but the value of the property being provided is not
	@constant		kAudioUnitErr_PropertyNotInUse
					Returned when a property is valid, but it hasn't been set to a valid value at 
					this time.	
	@constant		kAudioUnitErr_Initialized
					Indicates the operation cannot be performed because the audio unit is 
					initialized.
	@constant		kAudioUnitErr_InvalidOfflineRender
					Used to indicate that the offline render operation is invalid. For instance,
					when the audio unit needs to be pre-flighted, 
					but it hasn't been.
	@constant		kAudioUnitErr_Unauthorized
					Returned by either Open or Initialize, this error is used to indicate that the 
					audio unit is not authorised, that it cannot be used. A host can then present 
					a UI to notify the user the audio unit is not able to be used in its current 
					state.
	@constant		kAudioUnitErr_MIDIOutputBufferFull
					Returned during the render call, if the audio unit produces more MIDI output,
					than the default allocated buffer. The audio unit can provide a size hint, in
					case it needs a larger buffer. See the documentation for AUAudioUnit's
					MIDIOutputBufferSizeHint property.
	@constant		kAudioComponentErr_InstanceInvalidated
					The component instance's implementation is not available, most likely because the process
					that published it is no longer running.
	@constant		kAudioUnitErr_RenderTimeout
					The audio unit did not satisfy the render request in time.
	@constant 		kAudioUnitErr_ExtensionNotFound
					The specified identifier did not match any Audio Unit Extensions.
	@constant		kAudioUnitErr_InvalidParameterValue
					The parameter value is not supported, e.g. the value specified is NaN or
					infinite.
 	@constant 		kAudioUnitErr_InvalidFilePath
 					The file path that was passed is not supported. It is either too long or contains
 					invalid characters.
 	@constant		kAudioUnitErr_MissingKey
 					A required key is missing from a dictionary object.
*/
CF_ENUM(OSStatus) {
	kAudioUnitErr_InvalidProperty			= -10879,
	kAudioUnitErr_InvalidParameter			= -10878,
	kAudioUnitErr_InvalidElement			= -10877,
	kAudioUnitErr_NoConnection				= -10876,
	kAudioUnitErr_FailedInitialization		= -10875,
	kAudioUnitErr_TooManyFramesToProcess	= -10874,
	kAudioUnitErr_InvalidFile				= -10871,
	kAudioUnitErr_UnknownFileType			= -10870,
	kAudioUnitErr_FileNotSpecified			= -10869,
	kAudioUnitErr_FormatNotSupported		= -10868,
	kAudioUnitErr_Uninitialized				= -10867,
	kAudioUnitErr_InvalidScope				= -10866,
	kAudioUnitErr_PropertyNotWritable		= -10865,
	kAudioUnitErr_CannotDoInCurrentContext	= -10863,
	kAudioUnitErr_InvalidPropertyValue		= -10851,
	kAudioUnitErr_PropertyNotInUse			= -10850,
	kAudioUnitErr_Initialized				= -10849,
	kAudioUnitErr_InvalidOfflineRender		= -10848,
	kAudioUnitErr_Unauthorized				= -10847,
	kAudioUnitErr_MIDIOutputBufferFull		= -66753,
	kAudioComponentErr_InstanceTimedOut		= -66754,
	kAudioComponentErr_InstanceInvalidated	= -66749,
	kAudioUnitErr_RenderTimeout				= -66745,
	kAudioUnitErr_ExtensionNotFound			= -66744,
	kAudioUnitErr_InvalidParameterValue		= -66743,
	kAudioUnitErr_InvalidFilePath			= -66742,
	kAudioUnitErr_MissingKey				= -66741
};


#if AU_SUPPORT_INTERAPP_AUDIO
/*!
    @enum       AudioComponent errors for inter-app audio
    
    @constant   kAudioComponentErr_DuplicateDescription
        a non-unique component description was provided to AudioOutputUnitPublish
    @constant   kAudioComponentErr_UnsupportedType
        an unsupported component type was provided to AudioOutputUnitPublish
    @constant   kAudioComponentErr_TooManyInstances
        components published via AudioOutputUnitPublish may only have one instance
    @constant   kAudioComponentErr_NotPermitted
		app needs "inter-app-audio" entitlement or host app needs "audio" in its UIBackgroundModes.
		Or app is trying to register a component not declared in its Info.plist.
    @constant   kAudioComponentErr_InitializationTimedOut
        host did not render in a timely manner; must uninitialize and reinitialize.
	@constant	kAudioComponentErr_InvalidFormat
		inter-app AU element formats must have sample rates matching the hardware.
*/
CF_ENUM(OSStatus) {
    kAudioComponentErr_DuplicateDescription     = -66752,
    kAudioComponentErr_UnsupportedType          = -66751,
    kAudioComponentErr_TooManyInstances         = -66750,
    kAudioComponentErr_NotPermitted             = -66748,
	kAudioComponentErr_InitializationTimedOut	= -66747,
	kAudioComponentErr_InvalidFormat			= -66746
};
#endif

/*!
	@typedef			AudioUnitPropertyID
	@discussion			Type used for audio unit properties. 
						Properties are used to describe the state of an audio unit (for instance, 
						the input or output audio format)
*/
typedef UInt32							AudioUnitPropertyID;
/*!
	@typedef			AudioUnitScope
	@discussion			Type used for audio unit scopes. Apple reserves the 0 < 1024 range for 
						audio unit scope identifiers.  
						Scopes are used to delineate a major attribute of an audio unit 
						(for instance, global, input, output)
*/
typedef UInt32							AudioUnitScope;
/*!
	@typedef			AudioUnitElement
	@discussion			Type used for audio unit elements.
						Scopes can have one or more member, and a member of a scope is 
						addressed / described by its element
						For instance, input bus 1 is input scope, element 1
*/
typedef UInt32							AudioUnitElement;
/*!
	@typedef			AudioUnitParameterID
	@discussion			Type used for audio unit parameters. 
						Parameters are typically used to control and set render state 
						(for instance, filter cut-off frequency)
*/
typedef UInt32							AudioUnitParameterID;
/*!
	@typedef			AudioUnitParameterValue
	@discussion			Type used for audio unit parameter values. 
						The value of a given parameter is specified using this type 
						(typically a Float32)
*/
typedef	Float32							AudioUnitParameterValue;


/*!
	@enum			AUParameterEventType
	@discussion		The type of a parameter event (see AudioUnitScheduleParameter)

	@constant		kParameterEvent_Immediate
					The parameter event describes an immediate change to the parameter value to 
					the new value
	@constant		kParameterEvent_Ramped
					The parameter event describes a change to the parameter value that should
					be applied over the specified period of time
*/
typedef CF_ENUM(UInt32, AUParameterEventType)
{
	kParameterEvent_Immediate	= 1,
	kParameterEvent_Ramped		= 2
};

/*!
	@struct			AudioUnitParameterEvent
	@discussion		A parameter event describes a change to a parameter's value, where the type of 
					the event describes how that change is to be applied (see AUParameterEventType). 
					A parameter is uniquely defined through the triplet of scope, element and 
					parameterID.
					
					See AudioUnitScheduleParameters

	@var  			scope	
					The scope for the parameter
	@var  			element
					The element for the parameter
	@var  			parameter
					The parameterID for the parameter
	
	@var  			eventType
					The event type. This field further defines how the union described by 
					eventValues is to be interpreted.
	
	@var  			eventValues
					If the parameter event type is _Immediate, then the immediate struct of this 
					union should be used.
					If the parameter event type is _Ramped, then the ramp struct of this union 
					should be used.
					
*/
struct AudioUnitParameterEvent
{
	AudioUnitScope			scope;
	AudioUnitElement		element;
	AudioUnitParameterID	parameter;
	
	AUParameterEventType	eventType;
	
	union
	{
		struct
		{
			SInt32						startBufferOffset;
			UInt32						durationInFrames;
			AudioUnitParameterValue		startValue;
			AudioUnitParameterValue		endValue;
		}					ramp;
		
		struct
		{
			UInt32						bufferOffset;
			AudioUnitParameterValue		value;
		}					immediate;		

	}						eventValues;
};
typedef struct AudioUnitParameterEvent	AudioUnitParameterEvent;

/*!
	@struct			AudioUnitParameter
	@discussion		An audio unit parameter is defined by the triplet of audio unit scope, element 
					and parameterID. This struct is used with the functions in AudioUnitUtilities.h 
					to deal with audio unit parameters, but is included in this header file for 
					completeness.

	@var  			mAudioUnit
					The audio unit instance to which the specified parameter applies.
	@var  			mParameterID
					The parameterID for the parameter
	@var  			mScope	
					The scope for the parameter
	@var  			mElement
					The element for the parameter
*/
struct AudioUnitParameter
{
	AudioUnit				mAudioUnit;
	AudioUnitParameterID	mParameterID;
	AudioUnitScope			mScope;
	AudioUnitElement		mElement;
};
typedef struct AudioUnitParameter	AudioUnitParameter;

/*!
	@struct			AudioUnitProperty
	@discussion		An audio unit property is defined by the triplet of audio unit scope, element
					and propertyID. This struct is used with the functions in AudioUnitUtilities.h 
					to deal with audio unit properties, but is included in this header file for 
					completeness.

	@var  			mAudioUnit
					The audio unit instance which the specified property applies too
	@var  			mPropertyID
					The propertyID for the property
	@var  			mScope	
					The scope for the property
	@var  			mElement
					The element for the property
*/
struct AudioUnitProperty
{
	AudioUnit				mAudioUnit;
	AudioUnitPropertyID		mPropertyID;
	AudioUnitScope			mScope;
	AudioUnitElement		mElement;
};
typedef struct AudioUnitProperty	AudioUnitProperty;


/*!
	@typedef		AURenderCallback
	@discussion		This is the prototype for a function callback Proc that is used both with the 
					AudioUnit render notification API and the render input callback. See 
					kAudioUnitProperty_SetRenderCallback property or AudioUnitAddRenderNotify.
					This callback is part of the process of a call to AudioUnitRender. As a 
					notification it is called either before or after the audio unit's render 
					operations. As a render input callback, it is called to provide input data for
					the particular input bus the callback is attached too.
	
	@param			inRefCon
					The client data that is provided either with the AURenderCallbackStruct or as 
					specified with the Add API call
	@param			ioActionFlags
					Flags used to describe more about the context of this call (pre or post in the 
					notify case for instance) 
	@param			inTimeStamp
					The times stamp associated with this call of audio unit render
	@param			inBusNumber
					The bus number associated with this call of audio unit render
	@param			inNumberFrames
					The number of sample frames that will be represented in the audio data in the 
					provided ioData parameter
	@param			ioData
					The AudioBufferList that will be used to contain the rendered or provided 
					audio data. These buffers will be aligned to 16 byte boundaries (which is 
					normally what malloc will return). Can be null in the notification that
					input is available.
*/
typedef OSStatus
(*AURenderCallback)(	void *							inRefCon,
						AudioUnitRenderActionFlags *	ioActionFlags,
						const AudioTimeStamp *			inTimeStamp,
						UInt32							inBusNumber,
						UInt32							inNumberFrames,
						AudioBufferList * __nullable	ioData);

/*!
	@typedef		AudioUnitPropertyListenerProc
	@discussion		This is the prototype for a function callback Proc that is registered with an 
					audio unit to notify the caller of any changes to a value of an audio unit 
					property. See AudioUnitAddPropertyListener
	
	@param			inRefCon
					The client data that is provided with the add property listener registration
	@param			inUnit
					The audio unit upon which the specified property value has changed
	@param			inID
					The property whose value has changed
	@param			inScope
					The scope of the property whose value has changed
	@param			inElement
					The element ID on the scope of the property whose value has changed
*/
typedef void
(*AudioUnitPropertyListenerProc)(	void *				inRefCon,
									AudioUnit			inUnit,
									AudioUnitPropertyID	inID,
									AudioUnitScope		inScope,
									AudioUnitElement	inElement);

/*!
	@typedef		AUInputSamplesInOutputCallback
	@discussion		This is the prototype for a function callback Proc that is registered with an 
					audio unit to notify the caller of for the user of a varispeed or AUTimePitch 
					audio unit where it is not clear what input sample is represented in the 
					rendered output samples.
	
	@param			inRefCon
					The client data that is provided with the add property listener registration
	@param			inOutputTimeStamp
					The time stamp that corresponds to the first sample of audio data produced in 
					AudioUnitRender (its output data)
	@param			inInputSample
					The sample number of the input that is represented in the first sample of that 
					output time stamp
	@param			inNumberInputSamples
					The number of input samples that are represented in an output buffer
*/
typedef void
(*AUInputSamplesInOutputCallback)(	void *						inRefCon,
									const AudioTimeStamp *		inOutputTimeStamp,
									Float64						inInputSample,
									Float64						inNumberInputSamples);

/*!
	@constant kAudioComponentRegistrationsChangedNotification
	@abstract Notification generated when the set of available AudioComponents changes.
	@discussion
		Register for this notification name with [NSNotificationCenter defaultCenter] or
		CFNotificationCenterGetLocalCenter(), using an object of NULL.
*/
extern const CFStringRef kAudioComponentRegistrationsChangedNotification
												API_AVAILABLE(macos(10.11), ios(7.0), watchos(2.0), tvos(9.0));

/*!
	@constant kAudioComponentInstanceInvalidationNotification
	@abstract Notification generated when an audio unit extension process exits abnormally.
	@discussion
		Register for this notification name with [NSNotificationCenter defaultCenter] or
		CFNotificationCenterGetLocalCenter(). The "object" refers to an AUAudioUnit instance to
		be observed, or can be nil to observe all instances. The notification's userInfo
		dictionary contains a key, "audioUnit", an NSValue whose pointerValue is the
		AudioUnit or AudioComponentInstance which is wrapping the AUAudioUnit communicating with the
		extension process. (This may be null if there is no such component instance.) For example:

	[[NSNotificationCenter defaultCenter] addObserverForName:(NSString *)kAudioComponentInstanceInvalidationNotification object:nil queue:nil usingBlock:^(NSNotification *note) {
		AUAudioUnit *auAudioUnit = (AUAudioUnit *)note.object;
		NSValue *val = note.userInfo[@"audioUnit"];
		AudioUnit audioUnit = (AudioUnit)val.pointerValue;
		NSLog(@"Received kAudioComponentInstanceInvalidationNotification: auAudioUnit %@, audioUnit %p", auAudioUnit, audioUnit);
	}];
*/
extern const CFStringRef kAudioComponentInstanceInvalidationNotification
												API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));


//================================================================================================
#pragma mark -
#pragma mark Functions

/*!
	@function		AudioUnitInitialize
	@abstract		initialize an audio unit
	@discussion		Upon success, the audio unit has been successfully initialized. This means 
					that the formats for input and output are valid and can be supported and it 
					has based its allocations on the max number of frames that it is able to 
					render at any given time. Once initialized, it is in a state where it can be 
					asked to render.
					
					In common practice, major state of an audio unit (such as its I/O formats,
					memory allocations) cannot be changed while an audio unit is initialized.
	
	@param			inUnit
					The audio unit to initialize
	@result			noErr, or an error representing the reasons why the audio unit was not able 
					to be initialized successfully
*/
extern OSStatus
AudioUnitInitialize(				AudioUnit				inUnit)						
												API_AVAILABLE(macos(10.0), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioUnitUninitialize
	@abstract		uninitialize an audio unit
	@discussion		Once an audio unit has been initialized, to change its state in response to 
					some kind of environmental change, the audio unit should be uninitialized. 
					This will have the effect of the audio unit de-allocating its resources.
					The caller can then reconfigure the audio unit to match the new environment 
					(for instance, the sample rate to process audio is different than it was) and 
					then re-initialize the audio unit when those changes have been applied.
	
	@param			inUnit
					The audio unit to uninitialize
	@result			noErr, or an error representing the reasons why the audio unit was not able 
					to be initialized successfully. Typically this call won't return an error 
					unless the audio unit in question is no longer valid.
*/
extern OSStatus
AudioUnitUninitialize(				AudioUnit				inUnit)						
												API_AVAILABLE(macos(10.0), ios(2.0), watchos(2.0), tvos(9.0));


/*!
	@function		AudioUnitGetPropertyInfo
	@abstract		retrieves information about a specified property
	@discussion		The API can be used to retrieve both the size of the property, and whether it 
					is writable or not. In order to get a general answer on the capability of an 
					audio unit, this function should be called before the audio unit
					is initialized (as some properties are writable when the audio unit is 
					initialized, and others not)

	@param			inUnit
					the audio unit
	@param			inID
					the property identifier
	@param			inScope
					the scope of the property
	@param			inElement
					the element of the scope
	@param			outDataSize
					if not null, then will retrieve the maximum size for the property. if null, 
					then it is ignored
	@param			outWritable	
					if not null, then will retrieve whether the property can be written or not. 
					if null, then it is ignored
	
	@result			noErr, or various audio unit errors related to properties
*/
extern OSStatus
AudioUnitGetPropertyInfo(			AudioUnit				inUnit,
									AudioUnitPropertyID 	inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									UInt32 * __nullable		outDataSize,
									Boolean * __nullable	outWritable)			
												API_AVAILABLE(macos(10.0), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioUnitGetProperty
	@abstract		retrieves the value of a specified property
	@discussion		The API can is used to retrieve the value of the property. Property values for 
					audio units are always passed by reference
					
	@param			inUnit
					the audio unit
	@param			inID
					the property identifier
	@param			inScope
					the scope of the property
	@param			inElement
					the element of the scope
	@param			outData
					used to retrieve the value of the property. It should point to memory at least 
					as large as the value described by ioDataSize
	@param			ioDataSize	
					on input contains the size of the data pointed to by outData, on output, the 
					size of the data that was returned.

	@result			noErr, or various audio unit errors related to properties
*/
extern OSStatus
AudioUnitGetProperty(				AudioUnit				inUnit,
									AudioUnitPropertyID		inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									void *					outData,
									UInt32 *				ioDataSize)				
												API_AVAILABLE(macos(10.0), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioUnitSetProperty
	@abstract		sets the value of a specified property
	@discussion		The API can is used to set the value of the property. Property values for 
					audio units are always passed by reference
					
	@param			inUnit
					the audio unit
	@param			inID
					the property identifier
	@param			inScope
					the scope of the property
	@param			inElement
					the element of the scope
	@param			inData
					if not null, then is the new value for the property that will be set. If null, 
					then inDataSize should be zero, and the call is then used to remove a 
					previously set value for a property. This removal is only valid for
					some properties, as most properties will always have a default value if not 
					set.
	@param			inDataSize	
					the size of the data being provided in inData

	@result			noErr, or various audio unit errors related to properties
*/
extern OSStatus
AudioUnitSetProperty(				AudioUnit				inUnit,
									AudioUnitPropertyID		inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									const void * __nullable	inData,
									UInt32					inDataSize)				
												API_AVAILABLE(macos(10.0), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioUnitAddPropertyListener
	@abstract		registration call to receive notifications for when a property changes
	@discussion		When an audio unit property value changes, a notification callback can be 
					called by the audio unit to  inform interested parties that this event has 
					occurred. The notification is defined by the tuple of inProc and 
					inProcUserData as paired to the specified property ID, so the previously 
					defined AudioUnitRemovePropertyListener is deprecated because it didn't allow 
					for the provision of the inProcUserData to remove a given listener (so, 
					you should use AudioUnitRemovePropertyListenerWithUserData).
					
	@param			inUnit
					the audio unit
	@param			inID
					the property identifier
	@param			inProc
					the procedure to call when the property changes (on any scope or element)
	@param			inProcUserData
					the user data to provide with the callback

	@result			noErr, or various audio unit errors related to properties
*/
extern OSStatus
AudioUnitAddPropertyListener(		AudioUnit						inUnit,
									AudioUnitPropertyID				inID,
									AudioUnitPropertyListenerProc	inProc,
									void * __nullable				inProcUserData)
												API_AVAILABLE(macos(10.0), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioUnitRemovePropertyListenerWithUserData
	@abstract		remove a previously registered property listener
	@discussion		Removes a previously registered property listener as specified by the inProc 
					and inProcUser data as paired to the property identifier
					
	@param			inUnit
					the audio unit
	@param			inID
					the property identifier
	@param			inProc
					the procedure previously registered
	@param			inProcUserData
					the user data paired with the provided inProc

	@result			noErr, or various audio unit errors related to properties
*/
extern OSStatus
AudioUnitRemovePropertyListenerWithUserData(
									AudioUnit						inUnit,
									AudioUnitPropertyID				inID,
									AudioUnitPropertyListenerProc	inProc,
									void * __nullable				inProcUserData)
												API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioUnitAddRenderNotify
	@abstract		a notification callback to call when an audio unit is asked to render
	@discussion		allows an application to register a callback with an audio unit for whenever 
					the audio unit is asked to render. The callback is called both before the 
					audio unit performs its render operations (the render flag's pre-render bit 
					is set) and after the audio unit has completed its render operations (the 
					render flag's post-render bit is set). On post-render, the audio buffer list 
					(ioData) will contain valid audio data that was rendered by the audio unit.
					
					The inProc and inProcUserData are treated as a tuple entity, so when wanting 
					to remove one, both the inProc and its inProcUserData must be specified
					
	@param			inUnit
					the audio unit
	@param			inProc
					an AURenderCallback proc
	@param			inProcUserData
					the user data that will be provided with the proc when it is called

	@result			noErr, or an audio unit error code
*/
extern OSStatus
AudioUnitAddRenderNotify(			AudioUnit				inUnit,
									AURenderCallback		inProc,
									void * __nullable		inProcUserData)
												API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioUnitRemoveRenderNotify
	@abstract		remove a previously registered render notification proc
	
	@param			inUnit
					the audio unit
	@param			inProc
					an AURenderCallback proc
	@param			inProcUserData
					the user data that was provided with the proc when it was previously 
					registered

	@result			noErr, or an audio unit error code
*/
extern OSStatus
AudioUnitRemoveRenderNotify(		AudioUnit				inUnit,
									AURenderCallback		inProc,
									void * __nullable		inProcUserData)
												API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioUnitGetParameter
	@abstract		Get the value of a parameter
	@discussion		Get the value of a parameter as specified by its ID, scope and element. 
	
	@param			inUnit
					the audio unit
	@param			inID
					the parameter ID
	@param			inScope
					the scope for the parameter
	@param			inElement
					the element on the scope for the parameter
	@param			outValue
					Must be non-null, and upon success will contain the current value for the 
					specified parameter
	
	@result			noErr, or an audio unit error code (such as InvalidParameter)
*/
extern OSStatus
AudioUnitGetParameter(				AudioUnit					inUnit,
									AudioUnitParameterID		inID,
									AudioUnitScope				inScope,
									AudioUnitElement			inElement,
									AudioUnitParameterValue *	outValue)			
												API_AVAILABLE(macos(10.0), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioUnitSetParameter
	@abstract		Set the value of a parameter
	@discussion		Set the value of a parameter as specified by its ID, scope and element. 
					Parameter IDs are consistent across all of the elements in a scope - so for a 
					mixer, the "input volume" parameter can be applied on any input, and the 
					particular input is specified by the elementID.
	
	@param			inUnit
					the audio unit
	@param			inID
					the parameter ID
	@param			inScope
					the scope for the parameter
	@param			inElement
					the element on the scope for the parameter
	@param			inValue
					the new value for the parameter.
	@param			inBufferOffsetInFrames
					generally should be set to zero - see AudioUnitScheduleParameters
	
	@result			noErr, or an audio unit error code (such as InvalidParameter)
*/
extern OSStatus
AudioUnitSetParameter(				AudioUnit					inUnit,
									AudioUnitParameterID		inID,
									AudioUnitScope				inScope,
									AudioUnitElement			inElement,
									AudioUnitParameterValue		inValue,
									UInt32						inBufferOffsetInFrames) 
												API_AVAILABLE(macos(10.0), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioUnitScheduleParameters
	@abstract		Schedule changes to the value of a parameter
	@discussion		This API is used to schedule intra-buffer changes to the value of a parameter 
					(immediate) or to ramp a parameter from a start value to an end value for a 
					specified number of samples (ramp)
					
					The API allows for the scheduling of multiple parameter events with the one 
					call. All of the parameter events must apply to the current (and only apply to 
					the current) audio unit render call, so the events are scheduled as a part of 
					the pre-render notification callback.
					
					When scheduling an immediate parameter event, the new value at the specified 
					sample buffer offset is provided
					
					When scheduling a ramped parameter, the ramp is scheduled each audio unit 
					render for the duration of the ramp. Each schedule of the the new audio unit 
					render specifies the progress of the ramp.
					
					Parameters that can have events scheduled to them will indicate this through 
					their parameter info struct
					
	@param			inUnit
					the audio unit
	@param			inParameterEvent
					a pointer to an array of parameter event structs
	@param			inNumParamEvents
					the number of parameter event structs pointed to by inParameterEvent
	
	@result			noErr, or an audio unit error code (such as InvalidParameter)
*/
extern OSStatus
AudioUnitScheduleParameters(		AudioUnit						inUnit,
									const AudioUnitParameterEvent *	inParameterEvent,
									UInt32							inNumParamEvents) 
												API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/*!
	@function		AudioUnitRender
	@abstract		the render operation where ioData will contain the results of the audio unit's
					render operations
	@discussion		an audio unit will render the amount of audio data described by 
					inNumberOfFrames and the results of that render will be contained within 
					ioData. The caller should provide audio time stamps where at least the sample 
					time is valid and it is incrementing sequentially from its previous call 
					(so, the next time stamp will be the current time stamp + inNumberFrames) 
					If the sample time is not incrementing sequentially, the audio unit will infer
					that there is some discontinuity with the timeline it is rendering for
	
					The caller must provide a valid ioData AudioBufferList that matches the 
					expected topology for the current audio format for the given bus. The buffer 
					list can be of two variants:
					(1) If the mData pointers are non-null then the audio unit will render its 
					output into those buffers. These buffers should be aligned to 16 byte 
					boundaries (which is normally what malloc will return).
					(2) If the mData pointers are null, then the audio unit can provide pointers 
					to its own buffers. In this case the audio unit is required to keep those
					buffers valid for the duration of the calling thread's I/O cycle
					 
	@param			inUnit
					the audio unit
	@param			ioActionFlags
					any appropriate action flags for the render operation
	@param			inTimeStamp
					the time stamp that applies to this particular render operation. when 
					rendering for multiple output buses the time stamp will generally be the same 
					for each output bus, so the audio unit is able to determine without doubt that 
					this the same render operation
	@param			inOutputBusNumber
					the output bus to render for
	@param			inNumberFrames
					the number of sample frames to render
	@param			ioData
					the audio buffer list that the audio unit is to render into.
	
	@result			noErr, or an audio unit render error
*/
extern OSStatus
AudioUnitRender(					AudioUnit						inUnit,
									AudioUnitRenderActionFlags * __nullable ioActionFlags,
									const AudioTimeStamp *			inTimeStamp,
									UInt32							inOutputBusNumber,
									UInt32							inNumberFrames,
									AudioBufferList *				ioData)			
												API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

extern OSStatus
AudioUnitProcess (					AudioUnit						inUnit, 
									AudioUnitRenderActionFlags * __nullable	ioActionFlags, 
									const AudioTimeStamp *			inTimeStamp, 
									UInt32							inNumberFrames, 
									AudioBufferList *				ioData)
												API_AVAILABLE(macos(10.7), ios(6.0), watchos(2.0), tvos(9.0));

extern OSStatus
AudioUnitProcessMultiple(			AudioUnit						inUnit, 
									AudioUnitRenderActionFlags * __nullable ioActionFlags, 
									const AudioTimeStamp *			inTimeStamp, 
									UInt32							inNumberFrames,
									UInt32							inNumberInputBufferLists,
									const AudioBufferList * __nonnull * __nonnull inInputBufferLists,
									UInt32							inNumberOutputBufferLists,
									AudioBufferList * __nonnull * __nonnull ioOutputBufferLists)
												API_AVAILABLE(macos(10.7), ios(6.0), watchos(2.0), tvos(9.0));
	
/*!
	@function		AudioUnitReset
	@abstract		reset an audio unit's render state
	@discussion		This call will clear any render state of an audio unit. For instance, with a 
					delay or reverb type of audio unit reset will clear any of the delay lines 
					maintained within the audio unit. Typically, this call is made when an
					audio unit was previously rendering, and was taken out of the render chain 
					(say, the track it is in was muted) and is being added back in (unmuted). 
					The host should reset the audio unit before adding it back so that it doesn't 
					produce audio from its delay lines that is no longer valid.
					
					The call should only clear memory, it should NOT allocate or free memory 
					resources (this is done in the Initialize calls).
	
	@param			inUnit
					the audio unit
	@param			inScope
					the scope - typically this is set to GlobalScope
	@param			inElement
					the element - typically this is set to 0
	
	@result			noErr, or an audio unit error
*/
extern OSStatus
AudioUnitReset(						AudioUnit			inUnit,
									AudioUnitScope		inScope,
									AudioUnitElement	inElement)					
												API_AVAILABLE(macos(10.0), ios(2.0), watchos(2.0), tvos(9.0));

#if AU_SUPPORT_INTERAPP_AUDIO
/*!
    @function       AudioOutputUnitPublish

    @abstract       Register an audio output unit as available to be used as an audio unit by
                    other applications.

    @param          inOutputUnit
                        The audio output unit to be published.
    @param          inDesc
                        The AudioComponentDescription under which to register the application.
    @param          inName  
                        The application or component name.
    @result         An OSStatus result code.
    
    @discussion
        This allows a publishing application to register its audio (input/)output unit as being able
        to be redirected and repurposed as an audio unit effect, generator, music device or music
        effect by another host application.
*/
extern OSStatus
AudioOutputUnitPublish(         const AudioComponentDescription *   inDesc,
                                CFStringRef                         inName,
                                UInt32                              inVersion,
								AudioUnit                           inOutputUnit)
                                                API_UNAVAILABLE(macos) INTERAPP_AUDIO_DEPRECATED;


#if defined(__OBJC__)
@class UIImage;

extern UIImage * __nullable
AudioOutputUnitGetHostIcon(AudioUnit au, float desiredPointSize)
                                                API_UNAVAILABLE(macos) INTERAPP_AUDIO_DEPRECATED;
extern UIImage * __nullable
AudioComponentGetIcon(AudioComponent comp, float desiredPointSize)
                                                API_UNAVAILABLE(macos) INTERAPP_AUDIO_DEPRECATED;

#endif // __OBJC__


/*!
    @function       AudioComponentGetLastActiveTime
    @abstract       Fetches the time at which the application publishing the component was last active.
	@discussion
		Inter-app audio hosts can use this to sort the list of available nodes by how recently
		the user interacted with them.
	
    @param          comp
                        The AudioComponent being queried.
    @result         The CFAbsoluteTime at which the node was last active (0 if never).
*/
extern CFAbsoluteTime
AudioComponentGetLastActiveTime(AudioComponent comp)
                                                API_UNAVAILABLE(macos) INTERAPP_AUDIO_DEPRECATED;
#endif // AU_SUPPORT_INTERAPP_AUDIO

#if defined(__LP64__) || TARGET_OS_IPHONE
/*!
	@function		AudioUnitExtensionSetComponentList
	@abstract		Allows the implementor of an audio unit extension to dynamically modify the
					list of component registrations for the extension.
	@param			extensionIdentifier
						The bundle ID of the audio unit extension.
	@param			audioComponentInfo
						An array of dictionaries, one for each component, in the same format as
						described in AudioComponent.h for the Info.plist key "AudioComponents".
    @result         An OSStatus result code.
	@discussion
					Note that the bundle ID of the process calling this API must prefix (or match)
					the provided extension identifier.
*/
extern OSStatus
AudioUnitExtensionSetComponentList(CFStringRef extensionIdentifier, __nullable CFArrayRef audioComponentInfo)
								API_AVAILABLE(macos(10.13), ios(11.0))
								__TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
	@function		AudioUnitExtensionCopyComponentList
	@abstract		Returns the component registrations for a given audio unit extension.
	@param			extensionIdentifier
						The bundle ID of the audio unit extension.
	@result			An array of dictionaries, one for each component, in the same format as
					described in AudioComponent.h for the Info.plist key "AudioComponents".
					The caller should release this value when done with it.
*/
extern __nullable CFArrayRef
AudioUnitExtensionCopyComponentList(CFStringRef extensionIdentifier)
								API_AVAILABLE(macos(10.13), ios(11.0))
								__TVOS_PROHIBITED __WATCHOS_PROHIBITED;
#endif


/*!
	@enum			AudioUnitRange
	@discussion		the range of selectors that are used to dispatch through to the various audio 
					unit API

	@constant		kAudioUnitRange
	@constant		kAudioUnitInitializeSelect
	@constant		kAudioUnitUninitializeSelect
	@constant		kAudioUnitGetPropertyInfoSelect
	@constant		kAudioUnitGetPropertySelect
	@constant		kAudioUnitSetPropertySelect
	@constant		kAudioUnitAddPropertyListenerSelect
	@constant		kAudioUnitRemovePropertyListenerSelect
	@constant		kAudioUnitRemovePropertyListenerWithUserDataSelect
	@constant		kAudioUnitAddRenderNotifySelect
	@constant		kAudioUnitRemoveRenderNotifySelect
	@constant		kAudioUnitGetParameterSelect
	@constant		kAudioUnitSetParameterSelect
	@constant		kAudioUnitScheduleParametersSelect
	@constant		kAudioUnitRenderSelect
	@constant		kAudioUnitResetSelect
	@constant		kAudioUnitComplexRenderSelect
	@constant		kAudioUnitProcessSelect
	@constant		kAudioUnitProcessMultipleSelect
*/
enum {
	kAudioUnitRange							= 0x0000,	// range of selectors for audio units
	kAudioUnitInitializeSelect				= 0x0001,
	kAudioUnitUninitializeSelect			= 0x0002,
	kAudioUnitGetPropertyInfoSelect			= 0x0003,
	kAudioUnitGetPropertySelect				= 0x0004,
	kAudioUnitSetPropertySelect				= 0x0005,
	kAudioUnitAddPropertyListenerSelect		= 0x000A,
	kAudioUnitRemovePropertyListenerSelect	= 0x000B,
	kAudioUnitRemovePropertyListenerWithUserDataSelect = 0x0012,
	kAudioUnitAddRenderNotifySelect			= 0x000F,
	kAudioUnitRemoveRenderNotifySelect		= 0x0010,
	kAudioUnitGetParameterSelect			= 0x0006,
	kAudioUnitSetParameterSelect			= 0x0007,
	kAudioUnitScheduleParametersSelect		= 0x0011,
	kAudioUnitRenderSelect					= 0x000E,
	kAudioUnitResetSelect					= 0x0009,
	kAudioUnitComplexRenderSelect			= 0x0013,
	kAudioUnitProcessSelect					= 0x0014,
	kAudioUnitProcessMultipleSelect			= 0x0015
};

//================================================================================================
#pragma mark -
#pragma mark Dispatch function prototypes

typedef OSStatus	
(*AudioUnitInitializeProc) (void *self);

typedef OSStatus	
(*AudioUnitUninitializeProc) (void *self);

typedef OSStatus	
(*AudioUnitGetPropertyInfoProc) (void *self, AudioUnitPropertyID prop, AudioUnitScope scope, 
									AudioUnitElement elem, UInt32 * __nullable outDataSize, Boolean * __nullable outWritable);

typedef OSStatus	
(*AudioUnitGetPropertyProc) (void *self, AudioUnitPropertyID inID, AudioUnitScope inScope, 
									AudioUnitElement inElement, void *outData, UInt32 *ioDataSize);

typedef OSStatus	
(*AudioUnitSetPropertyProc) (void *self, AudioUnitPropertyID inID, AudioUnitScope inScope, 
									AudioUnitElement inElement, const void *inData, UInt32 inDataSize);

typedef OSStatus	
(*AudioUnitAddPropertyListenerProc) (void *self, AudioUnitPropertyID prop, 
									AudioUnitPropertyListenerProc proc, void *userData);

typedef OSStatus	
(*AudioUnitRemovePropertyListenerProc) (void *self, AudioUnitPropertyID prop, 
									AudioUnitPropertyListenerProc proc);

typedef OSStatus	
(*AudioUnitRemovePropertyListenerWithUserDataProc) (void *self, AudioUnitPropertyID prop, 
									AudioUnitPropertyListenerProc proc, void * __nullable userData);

typedef OSStatus	
(*AudioUnitAddRenderNotifyProc) (void *self, AURenderCallback proc, void * __nullable userData);

typedef OSStatus	
(*AudioUnitRemoveRenderNotifyProc) (void *self, AURenderCallback proc, void * __nullable userData);

typedef OSStatus	
(*AudioUnitScheduleParametersProc) (void *self, const AudioUnitParameterEvent *events, UInt32 numEvents);

typedef OSStatus	
(*AudioUnitResetProc) (void *self, AudioUnitScope		inScope, AudioUnitElement	inElement);

typedef OSStatus	
(*AudioUnitComplexRenderProc) (void *self, AudioUnitRenderActionFlags * __nullable ioActionFlags, const AudioTimeStamp *inTimeStamp, 
									UInt32 inOutputBusNumber, UInt32 inNumberOfPackets, UInt32 *outNumberOfPackets, 
									AudioStreamPacketDescription *outPacketDescriptions, AudioBufferList *ioData, 
									void *outMetadata, UInt32 *outMetadataByteSize);

typedef OSStatus	
(*AudioUnitProcessProc) (void *self, AudioUnitRenderActionFlags * __nullable ioActionFlags, const AudioTimeStamp *inTimeStamp, 
									UInt32 inNumberFrames, AudioBufferList *ioData);

typedef OSStatus	
(*AudioUnitProcessMultipleProc) (void *self, AudioUnitRenderActionFlags * __nullable ioActionFlags, const AudioTimeStamp *inTimeStamp, 
									UInt32 inNumberFrames, UInt32 inNumberInputBufferLists, const AudioBufferList * __nonnull * __nonnull inInputBufferLists,
									UInt32 inNumberOutputBufferLists, AudioBufferList * __nonnull * __nonnull ioOutputBufferLists);


/*!
	@typedef		AudioUnitGetParameterProc
	@discussion		This proc can be exported through the FastDispatch property or is used as the prototype for
					an audio component dispatch for this selector. 
					
					The arguments are the same as are provided to the corresponding API call
	
	@param			inComponentStorage
					For a component manager component, this is the component instance storage 
					pointer
*/
typedef OSStatus
(*AudioUnitGetParameterProc)(	void *						inComponentStorage,
								AudioUnitParameterID		inID,
								AudioUnitScope				inScope,
								AudioUnitElement			inElement,
								AudioUnitParameterValue *	outValue);
								
/*!
	@typedef		AudioUnitSetParameterProc
	@discussion		This proc can be exported through the FastDispatch property or is used as the prototype for
					an audio component dispatch for this selector. 
					
					The arguments are the same as are provided to the corresponding API call
	
	@param			inComponentStorage
					For a component manager component, this is the component instance storage 
					pointer
*/
typedef OSStatus
(*AudioUnitSetParameterProc)(	void *						inComponentStorage,
								AudioUnitParameterID		inID,
								AudioUnitScope				inScope,
								AudioUnitElement			inElement,
								AudioUnitParameterValue		inValue,
								UInt32						inBufferOffsetInFrames);
								
/*!
	@typedef		AudioUnitRenderProc
	@discussion		This proc can be exported through the FastDispatch property or is used as the prototype for
					an audio component dispatch for this selector. 
					
					The arguments are the same as are provided to the corresponding API call
	
	@param			inComponentStorage
					For a component manager component, this is the component instance storage 
					pointer
*/
typedef OSStatus
(*AudioUnitRenderProc)(			void *							inComponentStorage,
								AudioUnitRenderActionFlags * __nullable ioActionFlags,
								const AudioTimeStamp *			inTimeStamp,
								UInt32							inOutputBusNumber,
								UInt32							inNumberFrames,
								AudioBufferList *				ioData);


//================================================================================================
#pragma mark -
#pragma mark Deprecated
/*!
	@enum			deprecated - Audio unit errors
	@discussion		These are the various errors that can be returned by AudioUnit... API calls

	@constant		kAudioUnitErr_IllegalInstrument
					Apple's DLS synth returns this error if information about a particular 
					instrument patch is requested, but is not valid.
	@constant		kAudioUnitErr_InstrumentTypeNotFound
					Apple's DLS synth returns this error if information about a particular 
					instrument patch is requested, but is not valid.
*/
CF_ENUM(OSStatus) {
	kAudioUnitErr_IllegalInstrument			= -10873,
	kAudioUnitErr_InstrumentTypeNotFound	= -10872,
} __attribute__((deprecated));

#if !TARGET_RT_64_BIT && !TARGET_OS_IPHONE
// this call is deprecated and replaced by AudioUnitRemovePropertyListenerWithUserData
// this allows apps to use the same function pointer more than once
// you provide the same function ptr and user data as provided when you add a property listener
extern OSStatus
AudioUnitRemovePropertyListener(	AudioUnit						inUnit,
									AudioUnitPropertyID				inID,
									AudioUnitPropertyListenerProc	inProc)			
				API_DEPRECATED("no longer supported", macos(10.0, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
#endif

#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif /* AudioUnit_AUComponent_h */
#else
#include <AudioToolboxCore/AUComponent.h>
#endif
// ==========  AudioToolbox.framework/Headers/AUAudioUnit.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AUAudioUnit.h>)
/*!
	@file		AUAudioUnit.h
 	@framework	AudioToolbox.framework
 	@copyright	(c) 2015 Apple, Inc. All rights reserved.

	@brief		Objective-C interfaces for hosting and implementing Audio Units.
*/

#ifndef AudioToolbox_AUAudioUnit_h
#define AudioToolbox_AUAudioUnit_h
#ifdef __OBJC2__

#import <AudioToolbox/AUParameters.h>
#import <Foundation/NSExtensionRequestHandling.h>

#if !TARGET_OS_IPHONE
typedef UInt32 AUAudioObjectID; // AudioObjectID
#endif

NS_ASSUME_NONNULL_BEGIN

// forward declarations
@class AVAudioFormat;
@class AUAudioUnitBusArray;
@class AUAudioUnitBus;
@class AUAudioUnitPreset;
@class MIDICIProfile;
@class MIDICIProfileState;
typedef uint8_t MIDIChannelNumber;

@protocol AUAudioUnitFactory;

// =================================================================================================

/*!	@typedef	AUAudioUnitStatus
	@brief		A result code returned from an audio unit's render function.
*/
typedef OSStatus AUAudioUnitStatus;

/*!	@typedef	AUEventSampleTime
	@brief		Expresses time as a sample count.
	@discussion
		Sample times are normally positive, but hosts can propagate HAL sample times through audio
		units, and HAL sample times can be small negative numbers.
*/
typedef int64_t AUEventSampleTime;

/*!	@var		AUEventSampleTimeImmediate
	@brief		A special value of AUEventSampleTime indicating "immediately."
	@discussion
		Callers of AUScheduleParameterBlock and AUScheduleMIDIEventBlock can pass
		AUEventSampleTimeImmediate to indicate that the event should be rendered as soon as
		possible, in the next cycle. A caller may also add a small (less than 4096) sample frame
		offset to this constant. The base AUAudioUnit implementation translates this constant to a
		true AUEventSampleTime; subclasses will not see it.
*/
enum : AUEventSampleTime {
	AUEventSampleTimeImmediate = (AUEventSampleTime)0xffffffff00000000LL
};

/*!	@typedef	AUAudioFrameCount
	@brief		A number of audio sample frames.
	@discussion
		This is `uint32_t` for impedence-matching with the pervasive use of `UInt32` in AudioToolbox
		and C AudioUnit API's, as well as `AVAudioFrameCount`.
*/
typedef uint32_t AUAudioFrameCount;

/*!	@typedef	AUAudioChannelCount
	@brief		A number of audio channels.
	@discussion
		This is `uint32_t` for impedence-matching with the pervasive use of `UInt32` in AudioToolbox
		and C AudioUnit API's, as well as `AVAudioChannelCount`.
*/
typedef uint32_t AUAudioChannelCount;

// =================================================================================================

/*!	@enum		AUAudioUnitBusType
	@brief		Describes whether a bus array is for input or output.
*/
typedef NS_ENUM(NSInteger, AUAudioUnitBusType) {
	AUAudioUnitBusTypeInput		= 1,
	AUAudioUnitBusTypeOutput	= 2
};

// =================================================================================================

/*!	@typedef	AURenderPullInputBlock
	@brief		Block to supply audio input to AURenderBlock.
	@param actionFlags
		Pointer to action flags.
	@param timestamp
		The HAL time at which the input data will be rendered. If there is a sample rate conversion
		or time compression/expansion downstream, the sample time will not be valid.
	@param frameCount
		The number of sample frames of input requested.
	@param inputBusNumber
		The index of the input bus being pulled.
	@param inputData
		The input audio data.

		The caller must supply valid buffers in inputData's mBuffers' mData and mDataByteSize.
		mDataByteSize must be consistent with frameCount. This block may provide input in those
		specified buffers, or it may replace the mData pointers with pointers to memory which it
		owns and guarantees will remain valid until the next render cycle.
	@return
		An AUAudioUnitStatus result code. If an error is returned, the input data should be assumed 
		to be invalid.
*/
typedef AUAudioUnitStatus (^AURenderPullInputBlock)(AudioUnitRenderActionFlags *actionFlags, const AudioTimeStamp *timestamp, AUAudioFrameCount frameCount, NSInteger inputBusNumber, AudioBufferList *inputData);

/*!	@typedef	AURenderBlock
	@brief		Block to render the audio unit.
	@discussion
		All realtime operations are implemented using blocks to avoid ObjC method dispatching and
		the possibility of blocking.
	@param actionFlags
		Pointer to action flags.
	@param timestamp
		The HAL time at which the output data will be rendered. If there is a sample rate conversion
		or time compression/expansion downstream, the sample time will not have a defined
		correlation with the AudioDevice sample time.
	@param frameCount
		The number of sample frames to render.
	@param outputBusNumber
		The index of the output bus to render.
	@param outputData
		The output bus's render buffers and flags.

		The buffer pointers (outputData->mBuffers[x].mData) may be null on entry, in which case the
		block will render into memory it owns and modify the mData pointers to point to that memory.
		The block is responsible for preserving the validity of that memory until it is next called
		to render, or deallocateRenderResources is called.

		If, on entry, the mData pointers are non-null, the block will render into those buffers.
	@param pullInputBlock
		A block which the AU will call in order to pull for input data. May be nil for instrument
		and generator audio units (which do not have input busses).
	@return
		An `AUAudioUnitStatus` result code. If an error is returned, the output data should be assumed
		to be invalid.
*/
typedef AUAudioUnitStatus (^AURenderBlock)(AudioUnitRenderActionFlags *actionFlags, const AudioTimeStamp *timestamp, AUAudioFrameCount frameCount, NSInteger outputBusNumber, AudioBufferList *outputData, AURenderPullInputBlock __nullable pullInputBlock);

/*!	@typedef	AURenderObserver
	@brief		Block called when an audio unit renders.
	@discussion
		This block is called by the base class's AURenderBlock before and after each render cycle.
		The observer can distinguish between before and after using the PreRender and PostRender
		flags.
		
		The parameters are identical to those of AURenderBlock.
*/
typedef void (^AURenderObserver)(AudioUnitRenderActionFlags actionFlags, const AudioTimeStamp *timestamp, AUAudioFrameCount frameCount, NSInteger outputBusNumber);

/*!	@typedef	AUScheduleParameterBlock
	@brief		Block to schedule parameter changes.
	@discussion
		Not all parameters are rampable; check the parameter's flags.
	@param eventSampleTime
		The sample time (timestamp->mSampleTime) at which the parameter is to begin changing. When
		scheduling parameters during the render cycle (e.g. via a render observer) this time can be
		AUEventSampleTimeImmediate plus an optional buffer offset, in which case the event is
		scheduled at that position in the current render cycle.
	@param rampDurationSampleFrames
		The number of sample frames over which the parameter's value is to ramp, or 0 if the 
		parameter change should take effect immediately.
	@param parameterAddress
		The parameter's address.
	@param value
		The parameter's new value if the ramp duration is 0; otherwise, the value at the end
		of the scheduled ramp.
*/
typedef void (^AUScheduleParameterBlock)(AUEventSampleTime eventSampleTime, AUAudioFrameCount rampDurationSampleFrames, AUParameterAddress parameterAddress, AUValue value);

/*!	@typedef	AUScheduleMIDIEventBlock
	@brief		Block to schedule MIDI events.
	@param eventSampleTime
		The sample time (timestamp->mSampleTime) at which the MIDI event is to occur. When
		scheduling events during the render cycle (e.g. via a render observer) this time can be
		AUEventSampleTimeImmediate plus an optional buffer offset, in which case the event is
		scheduled at that position in the current render cycle.
	@param cable
		The virtual cable number.
	@param length
		The number of bytes of MIDI data in the provided event(s).
	@param midiBytes
		One or more valid MIDI 1.0 events, except sysex which must always be sent as the only event
		in the chunk. Also, running status is not allowed.
*/
typedef void (^AUScheduleMIDIEventBlock)(AUEventSampleTime eventSampleTime, uint8_t cable, NSInteger length, const uint8_t *midiBytes);

/*!	@typedef	AUMIDIOutputEventBlock
	@brief		Block to provide MIDI output events to the host.
	@param eventSampleTime
		The timestamp associated with the MIDI data in this chunk.
	@param cable
		The virtual cable number associated with this MIDI data.
	@param length
		The number of bytes of MIDI data in the provided event(s).
	@param midiBytes
		One or more valid MIDI 1.0 events, except sysex which must always be sent as the only event
		in the chunk.
*/
typedef OSStatus (^AUMIDIOutputEventBlock)(AUEventSampleTime eventSampleTime, uint8_t cable, NSInteger length, const uint8_t *midiBytes);

/*!	@typedef	AUHostMusicalContextBlock
	@brief		Block by which hosts provide musical tempo, time signature, and beat position.
	@param	currentTempo
		The current tempo in beats per minute.
	@param	timeSignatureNumerator
		The numerator of the current time signature.
	@param	timeSignatureDenominator
		The denominator of the current time signature.
	@param	currentBeatPosition
		The precise beat position of the beginning of the current buffer being rendered.
	@param	sampleOffsetToNextBeat
		The number of samples between the beginning of the buffer being rendered and the next beat
		(can be 0).
	@param	currentMeasureDownbeatPosition
		The beat position corresponding to the beginning of the current measure.
	@return
		YES for success.
	@discussion
		If the host app provides this block to an AUAudioUnit (as its musicalContextBlock), then
		the block may be called at the beginning of each render cycle to obtain information about
		the current render cycle's musical context.
		
		Any of the provided parameters may be null to indicate that the audio unit is not interested
		in that particular piece of information.
*/
typedef BOOL (^AUHostMusicalContextBlock)(double * __nullable currentTempo, double * __nullable timeSignatureNumerator, NSInteger * __nullable timeSignatureDenominator, double * __nullable currentBeatPosition, NSInteger * __nullable sampleOffsetToNextBeat, double * __nullable currentMeasureDownbeatPosition);

/*!	@typedef	AUMIDICIProfileChangedBlock
	@brief		Block by which hosts are informed of an audio unit having enabled or disabled a
				MIDI-CI profile.
	@param cable
		The virtual MIDI cable on which the event occured.
	@param channel
		The MIDI channel on which the profile was enabled or disabled.
	@param profile
		The MIDI-CI profile.
	@param enabled
		YES if the profile was enabled, NO if the profile was disabled.
*/
typedef void (^AUMIDICIProfileChangedBlock)(uint8_t cable, MIDIChannelNumber channel, MIDICIProfile *profile, BOOL enabled);

/*!	@enum		AUHostTransportState
	@brief		Flags describing the host's transport state.
	@constant	AUHostTransportStateChanged
		True if, since the callback was last called, there was a change to the state of, or
		discontinuities in, the host's transport. Can indicate such state changes as
		start/stop, or seeking to another position in the timeline.
	@constant	AUHostTransportStateMoving
		True if the transport is moving.
	@constant	AUHostTransportStateRecording
		True if the host is recording, or prepared to record. Can be true with or without the
		transport moving.
	@constant	AUHostTransportStateCycling
		True if the host is cycling or looping.
*/
typedef NS_OPTIONS(NSUInteger, AUHostTransportStateFlags) {
	AUHostTransportStateChanged			= 1,
	AUHostTransportStateMoving			= 2,
	AUHostTransportStateRecording		= 4,
	AUHostTransportStateCycling			= 8
};

/*!	@typedef	AUHostTransportStateBlock
	@brief		Block by which hosts provide information about their transport state.
	@param	transportStateFlags
		The current state of the transport.
	@param	currentSamplePosition
		The current position in the host's timeline, in samples at the audio unit's output sample
		rate.
	@param	cycleStartBeatPosition
		If cycling, the starting beat position of the cycle.
	@param	cycleEndBeatPosition
		If cycling, the ending beat position of the cycle.
	@discussion
		If the host app provides this block to an AUAudioUnit (as its transportStateBlock), then
		the block may be called at the beginning of each render cycle to obtain information about
		the current transport state.
		
		Any of the provided parameters may be null to indicate that the audio unit is not interested
		in that particular piece of information.
*/
typedef BOOL (^AUHostTransportStateBlock)(AUHostTransportStateFlags * __nullable transportStateFlags, double * __nullable currentSamplePosition, double * __nullable cycleStartBeatPosition, double * __nullable cycleEndBeatPosition);

// =================================================================================================

/*!	@class		AUAudioUnit
	@brief		An audio unit instance.
	@discussion
		AUAudioUnit is a host interface to an audio unit. Hosts can instantiate either version 2 or
		version 3 units with this class, and to some extent control whether an audio unit is
		instantiated in-process or in a separate extension process.
		
		Implementors of version 3 audio units can and should subclass AUAudioUnit. To port an
		existing version 2 audio unit easily, AUAudioUnitV2Bridge can be subclassed.
		
		These are the ways in which audio unit components can be registered:
		
		- (v2) Packaged into a component bundle containing an AudioComponents Info.plist entry,
		referring to an AudioComponentFactoryFunction. See AudioComponent.h.
		
		- (v2) AudioComponentRegister. Associates a component description with an
		AudioComponentFactoryFunction. See AudioComponent.h.
		
		- (v3) Packaged into an app extension containing an AudioComponents Info.plist entry.
		The principal class must conform to the AUAudioUnitFactory protocol, which will typically
		instantiate an AUAudioUnit subclass.

		- (v3) `+[AUAudioUnit registerSubclass:asComponentDescription:name:version:]`. Associates
		a component description with an AUAudioUnit subclass.
		
		A host need not be aware of the concrete subclass of AUAudioUnit that is being instantiated.
		`initWithComponentDescription:options:error:` ensures that the proper subclass is used.
		
		When using AUAudioUnit with a v2 audio unit, or the C AudioComponent and AudioUnit API's
		with a v3 audio unit, all major pieces of functionality are bridged between the
		two API's. This header describes, for each v3 method or property, the v2 equivalent.
*/
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface AUAudioUnit : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!	@method		initWithComponentDescription:options:error:
	@brief		Designated initializer.
	@param componentDescription
		A single AUAudioUnit subclass may implement multiple audio units, for example, an effect
		that can also function as a generator, or a cluster of related effects. The component
		description specifies the component which was instantiated.
	@param options
		Options for loading the unit in-process or out-of-process.
	@param outError
		Returned in the event of failure.
*/
- (nullable instancetype)initWithComponentDescription:(AudioComponentDescription)componentDescription options:(AudioComponentInstantiationOptions)options error:(NSError **)outError NS_DESIGNATED_INITIALIZER;

/*!	@method		initWithComponentDescription:error:
	@brief		Convenience initializer (omits options).
*/
- (nullable instancetype)initWithComponentDescription:(AudioComponentDescription)componentDescription error:(NSError **)outError;

/*!	@method	instantiateWithComponentDescription:options:completionHandler:
	@brief	Asynchronously create an AUAudioUnit instance.
	@param componentDescription
		The AudioComponentDescription of the audio unit to instantiate.
	@param options
		See the discussion of AudioComponentInstantiationOptions in AudioToolbox/AudioComponent.h.
	@param completionHandler
		Called in a thread/dispatch queue context internal to the implementation. The client should
		retain the supplied AUAudioUnit.
	@discussion
		Certain types of AUAudioUnits must be instantiated asynchronously -- see 
		the discussion of kAudioComponentFlag_RequiresAsyncInstantiation in
		AudioToolbox/AudioComponent.h.

		Note: Do not block the main thread while waiting for the completion handler to be called;
		this can deadlock.
*/
+ (void)instantiateWithComponentDescription:(AudioComponentDescription)componentDescription options:(AudioComponentInstantiationOptions)options completionHandler:(void (^)(AUAudioUnit * __nullable audioUnit, NSError * __nullable error))completionHandler;

/*!	@property	componentDescription
	@brief		The AudioComponentDescription with which the audio unit was created.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AudioComponentDescription componentDescription;

/*!	@property	component
	@brief		The AudioComponent which was found based on componentDescription when the
				audio unit was created.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AudioComponent component;

/*!	@property	componentName
	@brief		The unit's component's name.
	@discussion
		By convention, an audio unit's component name is its manufacturer's name, plus ": ",
		plus the audio unit's name. The audioUnitName and manufacturerName properties are derived
		from the component name.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSString *componentName;

/*!	@property	audioUnitName
	@brief		The audio unit's name.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSString *audioUnitName;

/*!	@property	manufacturerName
	@brief		The manufacturer's name.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSString *manufacturerName;

/*!	@property	audioUnitShortName
	@brief		A short name for the audio unit.
	@discussion
		Audio unit host applications can display this name in situations where the audioUnitName 
		might be too long. The recommended length is up to 16 characters. Host applications may 
		truncate it.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSString *audioUnitShortName API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!	@property	componentVersion
	@brief		The unit's component's version.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) uint32_t componentVersion;

/*!	@method		allocateRenderResourcesAndReturnError:
	@brief		Allocate resources required to render.
	@discussion
		Hosts must call this before beginning to render. Subclassers should call the superclass
		implementation.
		
		Bridged to the v2 API AudioUnitInitialize().
*/
- (BOOL)allocateRenderResourcesAndReturnError:(NSError **)outError;

/*!	@method		deallocateRenderResources
	@brief		Deallocate resources allocated by allocateRenderResourcesAndReturnError:
	@discussion
		Hosts should call this after finishing rendering. Subclassers should call the superclass
		implementation.
		
		Bridged to the v2 API AudioUnitUninitialize().
*/
- (void)deallocateRenderResources;

/*!	@property	renderResourcesAllocated
	@brief		returns YES if the unit has render resources allocated.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL renderResourcesAllocated;

/*!	@method		reset
	@brief		Reset transitory rendering state to its initial state.
	@discussion
		Hosts should call this at the point of a discontinuity in the input stream being provided to
		an audio unit, for example, when seeking forward or backward within a track. In response,
		implementations should clear delay lines, filters, etc. Subclassers should call the
		superclass implementation.
		
		Bridged to the v2 API AudioUnitReset(), in the global scope.
*/
- (void)reset;

/*!	@property	inputBusses
	@brief		An audio unit's audio input connection points.
	@discussion
		Subclassers must override this property's getter. The implementation should return the same
		object every time it is asked for it, since clients can install KVO observers on it.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AUAudioUnitBusArray *inputBusses;

/*!	@property	outputBusses
	@brief		An audio unit's audio output connection points.
	@discussion
		Subclassers must override this property's getter. The implementation should return the same
		object every time it is asked for it, since clients can install KVO observers on it.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AUAudioUnitBusArray *outputBusses;

/*!	@property	renderBlock
	@brief		Block which hosts use to ask the unit to render.
	@discussion
		Before invoking an audio unit's rendering functionality, a host should fetch this block and
		cache the result. The block can then be called from a realtime context without the
		possibility of blocking and causing an overload at the Core Audio HAL level.
		
		This block will call a subclass' internalRenderBlock, providing all realtime events
		scheduled for the current render time interval, bracketed by calls to any render observers.

		Subclassers should override internalRenderBlock, not this property.
		
		Bridged to the v2 API AudioUnitRender().
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AURenderBlock renderBlock;

/*!	@property	scheduleParameterBlock
	@brief		Block which hosts use to schedule parameters.
	@discussion
		As with renderBlock, a host should fetch and cache this block before beginning to render,
		if it intends to schedule parameters.
				
		The block is safe to call from any thread context, including realtime audio render
		threads.
		
		Subclassers should not override this; it is implemented in the base class and will schedule
		the events to be provided to the internalRenderBlock.
		
		Bridged to the v2 API AudioUnitScheduleParameters().
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AUScheduleParameterBlock scheduleParameterBlock;

/*!	@method		tokenByAddingRenderObserver:
	@brief		Add a block to be called on each render cycle.
	@discussion
		The supplied block is called at the beginning and ending of each render cycle. It should
		not make any blocking calls.
		
		This method is implemented in the base class AUAudioUnit, and should not be overridden.
		
		Bridged to the v2 API AudioUnitAddRenderNotify().
	@param observer
		The block to call.
	@return
		A token to be used when removing the observer.
*/
- (NSInteger)tokenByAddingRenderObserver:(AURenderObserver)observer;

/*!	@method		removeRenderObserver:
	@brief		Remove an observer block added via tokenByAddingRenderObserver:
	@param token
		The token previously returned by tokenByAddingRenderObserver:

		Bridged to the v2 API AudioUnitRemoveRenderNotify().
*/
- (void)removeRenderObserver:(NSInteger)token;

/*!	@property	maximumFramesToRender
	@brief		The maximum number of frames which the audio unit can render at once.
	@discussion
		This must be set by the host before render resources are allocated. It cannot be changed
		while render resources are allocated.
		
		Bridged to the v2 property kAudioUnitProperty_MaximumFramesPerSlice.
*/
@property (NS_NONATOMIC_IOSONLY) AUAudioFrameCount maximumFramesToRender;

/*!	@property	parameterTree
	@brief		An audio unit's parameters, organized in a hierarchy.
	@return
		A parameter tree object, or nil if the unit has no parameters.
	@discussion
		Audio unit hosts can fetch this property to discover a unit's parameters. KVO notifications
		are issued on this member to notify the host of changes to the set of available parameters.
		
		AUAudioUnit has an additional pseudo-property, "allParameterValues", on which KVO
		notifications are issued in response to certain events where potentially all parameter
		values are invalidated. This includes changes to currentPreset, fullState, and
		fullStateForDocument.
 
		Subclassers should implement the parameterTree getter to expose parameters to hosts. They
		should cache as much as possible and send KVO notifications on "parameterTree" when altering
		the structure of the tree or the static information (ranges, etc) of parameters.
		
		This is similar to the v2 properties kAudioUnitProperty_ParameterList and
		kAudioUnitProperty_ParameterInfo.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, nullable) AUParameterTree *parameterTree;

/*!	@method		parametersForOverviewWithCount:
	@brief		Returns the audio unit's `count` most important parameters.
	@discussion
		This property allows a host to query an audio unit for some small number of parameters which
		are its "most important", to be displayed in a compact generic view.

		An audio unit subclass should return an array of NSNumbers representing the addresses
		of the `count` most important parameters.

		The base class returns an empty array regardless of count.
		
		Partially bridged to kAudioUnitProperty_ParametersForOverview (v2 hosts can use that
		property to access this v3 method of an audio unit).
*/
- (NSArray<NSNumber *> *)parametersForOverviewWithCount:(NSInteger)count;

@property (NS_NONATOMIC_IOSONLY, readonly) BOOL allParameterValues;	/// special pseudo-property for KVO

/*!	@property	musicDeviceOrEffect
	@brief		Specifies whether an audio unit responds to MIDI events.
	@discussion
		This is implemented in the base class and returns YES if the component type is music
		device or music effect.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, getter=isMusicDeviceOrEffect) BOOL musicDeviceOrEffect;

/*!	@property	virtualMIDICableCount
	@brief		The number of virtual MIDI cables implemented by a music device or effect.
	@discussion
		A music device or MIDI effect can support up to 256 virtual MIDI cables of input; this
		property expresses the number of cables supported by the audio unit.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) NSInteger virtualMIDICableCount;

/*!	@property	scheduleMIDIEventBlock
	@brief		Block used to schedule MIDI events.
	@discussion
		As with renderBlock, a host should fetch and cache this block before beginning to render,
		if it intends to schedule MIDI events.

		This is implemented in the base class. It is nil when musicDeviceOrEffect is NO.

		Subclassers should not override. When hosts schedule events via this block, they are
		delivered to the audio unit via the list of AURenderEvents delivered to
		internalRenderBlock.
		
		This bridged to the v2 API MusicDeviceMIDIEvent.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, nullable) AUScheduleMIDIEventBlock scheduleMIDIEventBlock;

/*!	@property	MIDIOutputNames
	@brief		Count, and names of, a plug-in's MIDI outputs.
	@discussion
		A plug-in may override this method to inform hosts about its MIDI outputs. The size of the
		array is the number of outputs the audio unit supports. Each item in the array is the name
		of the MIDI output at that index.

		This is bridged to the v2 API property kAudioUnitProperty_MIDIOutputCallbackInfo.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<NSString *> *MIDIOutputNames API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!	@property	providesUserInterface
	@brief		Specifies whether an audio unit provides UI (normally in the form of a view controller).
	@discussion
		Implemented in the framework and should not be overridden by implementators. The
		framework detects whether any subclass has implemented
		`requestViewControllerWithCompletionHandler:` or is implemented by an AU extension whose
		extension point identifier is `com.apple.AudioUnit-UI`. See also
		`requestViewControllerWithCompletionHandler:` in <CoreAudioKit/AUViewController.h>
*/
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL providesUserInterface API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

// ------------------------
// These properties and methods are generally optional.

/*!	@property	MIDIOutputEventBlock
	@brief		Block used by the host to access the MIDI output generated by an audio unit.
	@discussion
 		The host can set this block and the plug-in can call it in its renderBlock to provide to the
 		host the MIDI data associated with the current render cycle.

 		This is bridged to the v2 API property kAudioUnitProperty_MIDIOutputCallback.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) AUMIDIOutputEventBlock MIDIOutputEventBlock API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!	@property	fullState
	@brief		A persistable snapshot of the audio unit's properties and parameters, suitable for
				saving as a user preset.
	@discussion
		Hosts may use this property to save and restore the state of an audio unit being used in a
		user preset or document. The audio unit should not persist transitory properties such as
		stream formats, but should save and restore all parameters and custom properties.
		
		The base class implementation of this property saves the values of all parameters 
		currently in the parameter tree. A subclass which dynamically produces multiple variants
		of the parameter tree needs to be aware that the serialization method does a depth-first
		preorder traversal of the tree.
		
		Bridged to the v2 property kAudioUnitProperty_ClassInfo.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSDictionary<NSString *, id> *fullState;

/*!	@property	fullStateForDocument
	@brief		A persistable snapshot of the audio unit's properties and parameters, suitable for
				saving in a user's document.
	@discussion
		This property is distinct from fullState in that some state is suitable for saving in user
		presets, while other state is not. For example, a synthesizer's master tuning setting could
		be considered global state, inappropriate for storing in reusable presets, but desirable
		for storing in a document for a specific live performance.
		
		Hosts saving documents should use this property. If the audio unit does not implement it,
		the base class simply sets/gets fullState.

		Bridged to the v2 property kAudioUnitProperty_ClassInfoFromDocument.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSDictionary<NSString *, id> *fullStateForDocument;

/*!	@property	factoryPresets
	@brief		A collection of presets provided by the audio unit's developer.
	@discussion
		A preset provides users of an audio unit with an easily-selectable, fine-tuned set of
		parameters provided by the developer. This property returns all of the available factory presets.

		Bridged to the v2 property kAudioUnitProperty_FactoryPresets.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSArray<AUAudioUnitPreset *> *factoryPresets;

/*!	@property	userPresets
	@brief		A collection of presets saved by the user
	@discussion
		In addition to factory presets, provided by the audio unit vendor, users have the ability to
		save the values of the parameters of an audio unit into a user preset. These users presets
		can be accessed using this property.

		The default implementation of this method will load the user presets from an internal
		location that might not be directly accessible to the audio unit host application or to the
		audio unit. Instead of accessing this path directly, the audio unit should rely on the
		superclass implementation of this method to retrieve the presets.

		Audio Units are free to override this method to load their user presets via different means
		(e.g. from their iCloud container).
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<AUAudioUnitPreset *> *userPresets API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/*!	@method		saveUserPreset:userPreset:error
	@brief		Persistently save the current state of the audio unit into a userPreset
	@discussion
		The new preset will be added to userPresets and will become selectable by assigning it
		to the currentPreset property.
		If a preset with the provided name already exists then it will be overwritten.

		For user presets, the preset number is required to be negative.
		If a positive number is passed, the sign will be changed to negative.
		If zero is passed, the number will be set to -1.
		These changes will be reflected on the userPreset argument.

		The default implementation of this method will save the user preset to an internal
		location.

		Audio Units are free to override this method to operate on a different location (e.g. their
		iCloud container).
	@param	userPreset
		The preset under which the current state will be saved.
	@param outError
		In the event of a failure, the method will return NO and outError will be set to an 
		NSError, describing the problem. 
		Some possible errors: 
				- domain: NSOSStatusErrorDomain code: kAudioUnitErr_NoConnection
				- domain: NSOSStatusErrorDomain	code: kAudioUnitErr_InvalidFilePath
				- domain: NSOSStatusErrorDomain	code: kAudioUnitErr_MissingKey
	@return
		YES for success. NO in the event of a failure, in which case the error is returned in
		outError.
 */
- (BOOL)saveUserPreset:(AUAudioUnitPreset *)userPreset error:(NSError **) outError API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/*!	@method		deleteUserPreset:userPreset:error
	@brief		Remove a user preset.
	@discussion
		The user preset will be removed from userPresets and will be permanently deleted.

		The default implementation of this method will delete the user preset from an internal
		location.

		Audio Units are free to override this method to operate on a different location (e.g. their
		iCloud container).
	@param	userPreset
		The preset to be deleted.
	@param	outError
		In the event of a failure, the method will return NO and outError will be set to an 
		NSError, describing the problem. 
		Some possible errors: 
				- domain: NSOSStatusErrorDomain code: kAudioUnitErr_NoConnection
				- domain: NSPOSIXErrorDomain	code: ENOENT
				- domain: NSOSStatusErrorDomain	code: kAudioUnitErr_InvalidFilePath
	@return
		YES for success. NO in the event of a failure, in which case the error is returned in
		outError.
*/
- (BOOL)deleteUserPreset:(AUAudioUnitPreset *)userPreset error:(NSError **) outError API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/*! @method		presetStateFor:userPreset:error
	@brief		Retrieve the state stored in a user preset
 	@discussion
		This method allows access to the contents of a preset without having to set that preset as
		current. The returned dictionary is assignable to the audio unit's fullState and/or
		fullStateForDocument properties.
 
		Audio units can override this method in order to vend user presets from a different location
		(e.g. their iCloud container).

		In order to restore the state from a user preset, the audio unit should override the setter
		for the currentPreset property and check the preset number to determine the type of preset.
		If the preset number is >= 0 then the preset is a factory preset.
		If the preset number is < 0 then it is a user preset.

		This method can then be called to retrieve the state stored in a user preset and the audio
		unit can assign this to fullState or fullStateForDocument.

	@param	userPreset
		The preset to be selected.
	@param	outError
		In the event of a failure, the method will return nil and outError will be set to an 
		NSError, describing the problem. 
		Some possible errors: 
				- domain: NSOSStatusErrorDomain code: kAudioUnitErr_NoConnection
				- domain: NSPOSIXErrorDomain	code: ENOENT
				- domain: NSCocoaErrorDomain	code: NSCoderReadCorruptError
	@return
		Returns nil if there was an error, otherwise returns a dictionary containing the full state
		of the audio unit saved in the preset.
		For details on the possible keys present in the full state dictionary, please see the
		documentation for kAudioUnitProperty_ClassInfo.
 		The minimal set of keys and their type is:	@kAUPresetTypeKey : NSNumber,
													@kAUPresetSubtypeKey : NSNumber,
 													@kAUPresetManufacturerKey : NSNumber,
 											   		@kAUPresetVersionKey : NSNumber,
 													@kAUPresetNameKey : NSString,
 													@kAUPresetNumberKey: NSNumber,
													@kAUPresetDataKey : NSData
*/
- (nullable NSDictionary<NSString *, id> *)presetStateFor:(AUAudioUnitPreset *)userPreset error:(NSError **) outError API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/*!	@property	supportsUserPresets
	@brief		Specifies whether an audio unit supports loading and saving user presets
	@discussion
		The audio unit should set this property to YES if a user preset can be assigned to
		currentPreset.

		Audio unit host applications should query this property to determine whether the audio unit
		supports user presets.

		Assigning a user preset to the currentPreset property of an audio unit that does not support
		restoring state from user presets may result in incorrect behavior.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL supportsUserPresets API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0));

/*!	@property	isLoadedInProcess
	@brief		Set to YES when an AUAudioUnit is loaded in-process
	@discussion
		If the AUAudioUnit is instantiated with kAudioComponentInstantiation_LoadInProcess, but the
		audio unit is not packaged properly to support loading in-process, the system will silently
		fall back to loading the audio unit out-of-process.

		This property can be used to determine whether the instantiation succeeded as intended and
		the audio unit is running in-process.

		The presence of an extension process is not sufficient indication that the audio unit failed
		to load in-process, since the framework might launch the audio unit extension process to
		fulfill auxiliary functionality. If the audio unit is loaded in-process then rendering is
		done in the host process. Other operations that are not essential to rendering audio, might
		be done in the audio unit's extension process.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL isLoadedInProcess API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos);

/*!	@property	currentPreset
	@brief		The audio unit's last-selected preset.
	@discussion
		Hosts can let the user select a preset by setting this property. Note that when getting
		this property, it does not reflect whether parameters may have been modified since the
		preset was selected.

		Bridged to the v2 property kAudioUnitProperty_PresentPreset.
*/
@property (NS_NONATOMIC_IOSONLY, retain, nullable) AUAudioUnitPreset *currentPreset;

/*!	@property	latency
	@brief		The audio unit's processing latency, in seconds.
	@discussion
		This property reflects the delay between when an impulse in the unit's audio unit stream
		arrives in the input vs. output streams. This should reflect the delay due
		to signal processing (e.g. filters, FFT's, etc.), not delay or reverberation which is
		being applied as an effect.
		
		Note that a latency that varies with parameter settings, including bypass, is generally not
		useful to hosts. A host is usually only prepared to add delays before starting to render and
		those delays need to be fixed. A variable delay would introduce artifacts even if the host
		could track it. If an algorithm has a variable latency it should be adjusted upwards to some
		fixed latency within the audio unit. If for some reason this is not possible, then latency
		could be regarded as an unavoidable consequence of the algorithm and left unreported (i.e.
		with a value of 0).

		Bridged to the v2 property kAudioUnitProperty_Latency.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) NSTimeInterval latency;

/*!	@property	tailTime
	@brief		The audio unit's tail time, in seconds.
	@discussion
		This property reflects the time interval between when the input stream ends or otherwise
		transitions to silence, and when the output stream becomes silent. Unlike latency, this
		should reflect the duration of a delay or reverb effect.
		
		Bridged to the v2 property kAudioUnitProperty_TailTime.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) NSTimeInterval tailTime;

/*!	@property	renderQuality
	@brief		Provides a trade-off between rendering quality and CPU load.
	@discussion
		The range of valid values is 0-127.
		
		Bridged to the v2 property kAudioUnitProperty_RenderQuality.
*/
@property (NS_NONATOMIC_IOSONLY) NSInteger renderQuality;

/*!	@property	shouldBypassEffect
	@brief		Directs an effect to route input directly to output, without any processing.
	@discussion
		Bridged to the v2 property kAudioUnitProperty_BypassEffect.
*/
@property (NS_NONATOMIC_IOSONLY) BOOL shouldBypassEffect;

/*!	@property	canProcessInPlace
	@brief		Expresses whether an audio unit can process in place.
	@discussion
		In-place processing is the ability for an audio unit to transform an input signal to an
		output signal in-place in the input buffer, without requiring a separate output buffer.
		
		A host can express its desire to process in place by using null mData pointers in the output
		buffer list. The audio unit may process in-place in the input buffers. See the discussion of
		renderBlock.
		
		Partially bridged to the v2 property kAudioUnitProperty_InPlaceProcessing; in v3 it is not
		settable.
		
		Defaults to NO. Subclassers can override to return YES.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL canProcessInPlace;

/*!	@property	renderingOffline
	@brief		Communicates to an audio unit that it is rendering offline.
	@discussion
		A host should set this property when using an audio unit in a context where there are no
		realtime deadlines, before asking the unit to allocate render resources. An audio unit may
		respond by using a more expensive signal processing algorithm, or allowing itself to block
		at render time if data being generated on secondary work threads is not ready in time.
		(Normally, in a realtime thread, this data would have to be dropped).

		Bridged to the v2 property kAudioUnitProperty_OfflineRender.
*/
@property (NS_NONATOMIC_IOSONLY, getter=isRenderingOffline) BOOL renderingOffline;

/*!	@property	channelCapabilities
	@brief		Expresses valid combinations of input and output channel counts.
	@discussion
		Elements are NSNumber containing integers; [0]=input count, [1]=output count, [2]=2nd input
		count, [3]=2nd output count, etc.

		An input, output count of (2, 2) signifies that the audio unit can process 2 input channels
		to 2 output channels.
		
		Negative numbers (-1, -2) indicate *any* number of channels. (-1, -1) means any number
		of channels on input and output as long as they are the same. (-1, -2) means any number of
		channels on input or output, without the requirement that the counts are the same.
		
		A negative number less than -2 is used to indicate a total number of channels across every
		bus in that scope, regardless of how many channels are set on any particular bus. For
		example, (-16, 2) indicates that a unit can accept up to 16 channels of input across its
		input busses, but will only produce 2 channels of output.
		
		Zero on either side (though typically input) means "not applicable", because there are no
		elements on that side.

		Bridged to the v2 property kAudioUnitProperty_SupportedNumChannels.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSArray<NSNumber *> *channelCapabilities;

/*!	@property	musicalContextBlock
	@brief		A callback for the AU to call the host for musical context information.
	@discussion
		Note that an audio unit implementation accessing this property should cache it in
		realtime-safe storage before beginning to render.
		
		Bridged to the HostCallback_GetBeatAndTempo and HostCallback_GetMusicalTimeLocation
		callback members in kAudioUnitProperty_HostCallbacks.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) AUHostMusicalContextBlock musicalContextBlock;

/*!	@property	transportStateBlock
	@brief		A callback for the AU to call the host for transport state information.
	@discussion
		Note that an audio unit implementation accessing this property should cache it in
		realtime-safe storage before beginning to render.
		
		Bridged to the HostCallback_GetTransportState and HostCallback_GetTransportState2
		callback members in kAudioUnitProperty_HostCallbacks.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) AUHostTransportStateBlock transportStateBlock;

/*!	@property	contextName
	@brief		Information about the host context in which the audio unit is connected, for display
				in the audio unit's view.
	@discussion
		For example, a host could set "track 3" as the context, so that the audio unit's view could
		then display to the user "My audio unit on track 3".

		Bridged to the v2 property kAudioUnitProperty_ContextName.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSString *contextName;

/*!	@property	supportsMPE
	@brief		Specifies whether an audio unit supports Multi-dimensional Polyphonic Expression.
	@discussion
		Bridged to the v2 property kAudioUnitProperty_SupportsMPE.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL supportsMPE API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!	@property	channelMap
	@brief		Specify a mapping of input channels to output channels.
	@discussion
		Converter and input/output audio units may support re-ordering or splitting of input
		channels to output channels. The number of channels in the channel map is the number of
		channels of the destination (output format). The channel map entries contain a channel
		number of the source channel that should be mapped to that destination channel. If -1 is
		specified, then that destination channel will not contain any channel from the source (so it
		will be silent).
		
		If the property value is nil, then the audio unit does not support this property.
 
		Bridged to the v2 property kAudioOutputUnitProperty_ChannelMap.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSArray<NSNumber *> *channelMap API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!	@method		profileStateForCable:channel:
	@brief		Given a MIDI cable and channel number, return the supported MIDI-CI Profiles.
	@param cable
		The virtual MIDI cable for which the profiles are requested.
	@param channel
		The MIDI channel for which the profiles are requested.
	@return
		A MIDICIProfileState object containing all the supported MIDI-CI profiles for this channel
		on this cable.
*/
- (MIDICIProfileState *)profileStateForCable:(uint8_t)cable channel:(MIDIChannelNumber)channel API_AVAILABLE(macos(10.14), ios(12.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;

/*!	@method		enableProfile:profile:cable:onChannel:error
	@brief		Enable a MIDI-CI Profile on the specified cable/channel.
	@param	profile
		The MIDI-CI profile to be enabled.
	@param cable
		The virtual MIDI cable.
	@param channel
		The MIDI channel.
	@param outError
		Returned in the event of failure.
	@return
		YES for success. NO in the event of a failure, in which case the error is returned
		in outError.
*/
- (BOOL)enableProfile:(MIDICIProfile *)profile
                cable:(uint8_t)cable
            onChannel:(MIDIChannelNumber)channel
                error:(NSError **)outError API_AVAILABLE(macos(10.14), ios(12.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;

/*!	@method		disableProfile:profile:cable:onChannel:error
	@brief		Disable a MIDI-CI Profile on the specified cable/channel.
	@param	profile
		The MIDI-CI profile to be disabled.
	@param cable
		The virtual MIDI cable.
	@param channel
		The MIDI channel.
	@param outError
		Returned in the event of failure.
	@return
		YES for success. NO in the event of a failure, in which case the error is returned
		in outError.
*/
- (BOOL)disableProfile:(MIDICIProfile *)profile
                 cable:(uint8_t)cable
             onChannel:(MIDIChannelNumber)channel
                 error:(NSError **)outError API_AVAILABLE(macos(10.14), ios(12.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;

/*!	@property	profileChangedBlock
	@brief		A block called when a device notifies that a MIDI-CI profile has been enabled or 
				disabled.
	@discussion
		Since enabling / disabling MIDI-CI profiles is an asynchronous operation, the host can set 
		this block and the audio unit is expected to call it every time the state of a MIDI-CI 
		profile has changed.
*/
@property (nonatomic, nullable) AUMIDICIProfileChangedBlock profileChangedBlock API_AVAILABLE(macos(10.14), ios(12.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;

@end

// =================================================================================================

/*!	@typedef	AUInputHandler
	@brief		Block to notify the client of an I/O unit that input is available.
	@param actionFlags
		Pointer to action flags.
	@param timestamp
		The HAL time at which the input data was captured. If there is a sample rate conversion
		or time compression/expansion downstream, the sample time will not be valid.
	@param frameCount
		The number of sample frames of input available.
	@param inputBusNumber
		The index of the input bus from which input is available.
	@discussion	The input data is obtained by calling the render block of the audio unit.
				The AUAudioUnit is not provided since it is not safe to message an Objective C 
				object in a real time context.
*/
typedef void (^AUInputHandler)(AudioUnitRenderActionFlags *actionFlags, const AudioTimeStamp *timestamp, AUAudioFrameCount frameCount, NSInteger inputBusNumber);

/*!	@brief		Additional methods for audio units which can do input/output.
	@discussion	These methods will fail if the audio unit is not an input/output audio unit.
*/
@interface AUAudioUnit (AUAudioInputOutputUnit)

/*!	@property	canPerformInput
	@brief		Whether the I/O device can perform input.
*/
@property (nonatomic, readonly) BOOL canPerformInput;

/*!	@property	canPerformOutput
	@brief		Whether the I/O device can perform output.
*/
@property (nonatomic, readonly) BOOL canPerformOutput;

/*!	@property	inputEnabled
	@brief		Flag enabling audio input from the unit.
	@discussion	Input is disabled by default. This must be set to YES if input audio is desired. 
				Setting to YES will have no effect if canPerformInput is false.
*/
@property (nonatomic, getter=isInputEnabled) BOOL inputEnabled;

/*!	@property	outputEnabled
	@brief		Flag enabling audio output from the unit.
	@discussion	Output is enabled by default.
				Setting to YES will have no effect if canPerformOutput is false.
*/
@property (nonatomic, getter=isOutputEnabled) BOOL outputEnabled;

/*!	@property	outputProvider
	@brief		The block that the output unit will call to get audio to send to the output.
	@discussion	This block must be set if output is enabled.
*/
@property (nonatomic, copy, nullable) AURenderPullInputBlock outputProvider;

/*!	@property	inputHandler
	@brief		The block that the output unit will call to notify when input is available.
	@discussion	See discussion for AUInputHandler.
*/
@property (nonatomic, copy, nullable) AUInputHandler inputHandler;

#if !TARGET_OS_IPHONE
/*!	@property	device
	@brief		Get the I/O hardware device.
*/
@property (nonatomic, readonly) AUAudioObjectID deviceID;

/*!	@method		setDeviceID:error:
	@brief		Set the I/O hardware device.
	@param deviceID
		The device to select.
	@param outError
		Returned in the event of failure.
*/
- (BOOL)setDeviceID:(AUAudioObjectID)deviceID error:(NSError **)outError;

/*!	@property	deviceInputLatency
	@brief		The audio device's input latency, in seconds.
	@discussion
		Bridged to the HAL property kAudioDevicePropertyLatency, which is implemented 
		by v2 input/output units.
*/
@property (nonatomic, readonly) NSTimeInterval deviceInputLatency API_AVAILABLE(macos(10.13));

/*!	@property	deviceOutputLatency
	@brief		The audio device's output latency, in seconds.
	@discussion
		Bridged to the HAL property kAudioDevicePropertyLatency, which is implemented
		by v2 input/output units.
*/
@property (nonatomic, readonly) NSTimeInterval deviceOutputLatency API_AVAILABLE(macos(10.13));
#endif // TARGET_OS_IPHONE

/*!	@property	running
	@brief		The audio device's running state.
*/
@property (nonatomic, readonly, getter=isRunning) BOOL running API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!	@method		startHardwareAndReturnError:
	@brief		Starts the audio hardware.
	@param outError
		Returned in the event of failure.
*/
- (BOOL)startHardwareAndReturnError:(NSError **)outError;

/*!	@method		stopHardware
	@brief		Stops the audio hardware.
*/
- (void)stopHardware;

@end

// =================================================================================================

/*!	@class	AUAudioUnitBusArray
	@brief	Container for an audio unit's input or output busses.
	@discussion
		Hosts can observe a bus property across all busses by using KVO on this object, without
		having to observe it on each individual bus. (One could add listeners to individual busses,
		but that means one has to observe bus count changes and add/remove listeners in response.
		Also, NSArray's addObserver:toObjectsAtIndexes:forKeyPath:options:context: is problematic;
		it does not let the individual objects override the observation request, and so a bus which
		is proxying a bus in an extension process does not get the message.)

		Some audio units (e.g. mixers) support variable numbers of busses, via subclassing. When the
		bus count changes, a KVO notification is sent on "inputBusses" or "outputBusses," as
		appropriate.

		Subclassers should see also the AUAudioUnitBusImplementation category.
		
		The bus array is bridged to the v2 property kAudioUnitProperty_ElementCount.
*/
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface AUAudioUnitBusArray : NSObject <NSFastEnumeration>

- (instancetype)init NS_UNAVAILABLE;

/*!	@method		initWithAudioUnit:busType:busses:
	@brief		Initializes by making a copy of the supplied bus array.
*/
- (instancetype)initWithAudioUnit:(AUAudioUnit *)owner busType:(AUAudioUnitBusType)busType busses:(NSArray <AUAudioUnitBus *> *)busArray NS_DESIGNATED_INITIALIZER;

/*!	@method		initWithAudioUnit:busType:
	@brief		Initializes an empty bus array.
*/
- (instancetype)initWithAudioUnit:(AUAudioUnit *)owner busType:(AUAudioUnitBusType)busType;

/*!	@property	count
*/
@property (NS_NONATOMIC_IOSONLY, readonly) NSUInteger count;

/*!	@method		objectAtIndexedSubscript:
*/
- (AUAudioUnitBus *)objectAtIndexedSubscript:(NSUInteger)index;

/*!	@property	countChangeable
	@brief		Whether the array can have a variable number of busses.
	@discussion
		The base implementation returns false.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, getter=isCountChangeable) BOOL countChangeable;

/*!	@property	setBusCount:error:
	@brief		Change the number of busses in the array.
*/
- (BOOL)setBusCount:(NSUInteger)count error:(NSError **)outError;

/*!	@method		addObserverToAllBusses:forKeyPath:options:context:
	@brief		Add a KVO observer for a property on all busses in the array.
*/
- (void)addObserverToAllBusses:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(void * __nullable)context;

/*!	@method		removeObserverFromAllBusses:forKeyPath:context:
	@brief		Remove a KVO observer for a property on all busses in the array.
*/
- (void)removeObserverFromAllBusses:(NSObject *)observer forKeyPath:(NSString *)keyPath context:(void * __nullable)context;

/// The audio unit that owns the bus.
@property (NS_NONATOMIC_IOSONLY, readonly, assign) AUAudioUnit *ownerAudioUnit;

/// Which bus array this is (input or output).
@property (NS_NONATOMIC_IOSONLY, readonly) AUAudioUnitBusType busType;

@end

// =================================================================================================

/*!	@class	AUAudioUnitBus
	@brief	An input or output connection point on an audio unit.
*/
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface AUAudioUnitBus : NSObject

/*!	@property	format
	@brief		The audio format and channel layout of audio being transferred on the bus.
	@discussion
		Bridged to the v2 property kAudioUnitProperty_StreamFormat.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AVAudioFormat *format;

/*!	@property	setFormat:error:
	@brief		Sets the bus's audio format.
	@discussion
		Audio units can generally be expected to support AVAudioFormat's standard format
		(deinterleaved 32-bit float), at any sample rate. Channel counts can be more complex;
		see AUAudioUnit.channelCapabilities.
*/
- (BOOL)setFormat:(AVAudioFormat *)format error:(NSError **)outError;

/*! @property	shouldAllocateBuffer
    @brief		Controls the audio unit's allocation strategy for a bus.
    @discussion
        Hosts can set this flag to communicate whether an audio unit should allocate its own buffer.
        By default this flag is set to true.

        On the output side, shouldAllocateBuffer=false means the AU can assume that it will be
        called with non-null output buffers. If shouldAllocateBuffer=true (the default), the AU must
        be prepared to be called with null pointers and replace them with pointers to its internally
        allocated buffer.

        On the input side, shouldAllocateBuffer=false means the AU can pull for input using a buffer
        list with null buffer pointers, and assume that the pull input block will provide pointers.
        If shouldAllocateBuffer=true (the default), the AU must pull with non-null pointers while
        still being prepared for the source to replace them with pointers of its own.

        Bridged to the v2 property kAudioUnitProperty_ShouldAllocateBuffer.
*/
@property (NS_NONATOMIC_IOSONLY) BOOL shouldAllocateBuffer API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/*!	@property	enabled
	@brief		Whether the bus is active.
	@discussion
		Hosts must enable input busses before using them. The reason for this is to allow a unit
		such as a mixer to be prepared to render a large number of inputs, but avoid the work
		of preparing to pull inputs which are not in use.
		
		Bridged to the v2 properties kAudioUnitProperty_MakeConnection and
		kAudioUnitProperty_SetRenderCallback.
*/
@property (NS_NONATOMIC_IOSONLY, getter=isEnabled) BOOL enabled;

/*!	@property	name
	@brief		A name for the bus. Can be set by host.
*/
@property (NS_NONATOMIC_IOSONLY, copy, nullable) NSString *name;

/*! @property   index
    @brief      The index of this bus in the containing array.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) NSUInteger index;

/*! @property   busType
    @brief      The AUAudioUnitBusType.
*/
@property (NS_NONATOMIC_IOSONLY, readonly) AUAudioUnitBusType busType;

/*! @property   ownerAudioUnit
 @brief         The audio unit that owns the bus.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, assign) AUAudioUnit *ownerAudioUnit;

/*!	@property	supportedChannelLayoutTags
	@discussion
		This is an array of NSNumbers representing AudioChannelLayoutTag.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSArray<NSNumber *> *supportedChannelLayoutTags;

/*!	@property	contextPresentationLatency
	@brief		Information about latency in the audio unit's processing context.
	@discussion
		This should not be confused with the audio unit's latency property, where the audio unit
		describes to the host any processing latency it introduces between its input and its output.
		
		A host may set this property to describe to the audio unit the presentation latency of its
		input and/or output audio data. Latency is described in seconds. A value of zero means
		either no latency or an unknown latency.
		
		A host should set this property on each active bus, since, for example, the audio routing
		path to each of multiple output busses may differ.
		
		For input busses:
			Describes how long ago the audio arriving on this bus was acquired. For instance, when
			reading from a file to the first audio unit in a chain, the input presentation latency
			is zero. For audio input from a device, this initial input latency is the presentation
			latency of the device itself, i.e. the device's safety offset and latency.
			
			A second chained audio unit's input presentation latency will be the input presentation
			latency of the first unit, plus the processing latency of the first unit.
			
		For output busses:
			Describes how long it will be before the output audio of an audio unit is presented. For
			instance, when writing to a file, the output presentation latency of the last audio unit
			in a chain is zero. When the audio from that audio unit is to be played to a device,
			then that initial presentation latency will be the presentation latency of the device
			itself, which is the I/O buffer size, plus the device's safety offset and latency
			
			A previous chained audio unit's output presentation latency is the last unit's
			presentation latency plus its processing latency.
			
		So, for a given audio unit anywhere within a mixing graph, the input and output presentation 
		latencies describe to that unit how long from the moment of generation it has taken for its 
		input to arrive, and how long it will take for its output to be presented.
		
		Bridged to the v2 property kAudioUnitProperty_PresentationLatency.
*/
@property (NS_NONATOMIC_IOSONLY) NSTimeInterval contextPresentationLatency;

@end

// =================================================================================================

/*!	@class	AUAudioUnitPreset
	@brief	A collection of parameter settings provided by the audio unit implementor, producing a
			useful sound or starting point.
*/
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface AUAudioUnitPreset : NSObject <NSSecureCoding>

/*!	@property	number
	@brief		The preset's unique numeric identifier.
*/
@property (NS_NONATOMIC_IOSONLY) NSInteger number;

/*!	@property	name
	@brief		The preset's name.
*/
@property (NS_NONATOMIC_IOSONLY, copy) NSString *name;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
#endif // AudioToolbox_AUAudioUnit_h
#else
#include <AudioToolboxCore/AUAudioUnit.h>
#endif
// ==========  AudioToolbox.framework/Headers/AudioUnitProperties.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AudioUnitProperties.h>)
/*!
	@file		AudioUnitProperties.h
 	@framework	AudioToolbox.framework
 	@copyright	(c) 2000-2018 Apple, Inc. All rights reserved.
	@abstract	Property ID's and accompanying structs used by Apple audio units.

	@discussion

	Properties form the basis of much of the audio unit API. You use them with
	these AudioUnit.framework API functions declared in AUComponent.h:
	
		AudioUnitGetPropertyInfo
		AudioUnitGetProperty
		AudioUnitSetProperty

	This file first lists generic audio unit properties (those that are potentially applicable to 
	any audio unit), followed by properties specific to Apple audio units.

	Apple reserves property IDs from 0 -> 63999. Developers are free to use property IDs above this 
	range.

	All property values are passed by reference. When a property's value type is listed below,
	that value type is always passed by reference. For example, CFStringRef is passed as 
	&myCFString.

	Properties are described below using a general form:
		Scope:				The audio unit scope that the property applies to. For example, Global, 
							Input, Output, etc. For an explanation of audio unit scopes, see the 
							Audio Unit Programming Guide in the ADC Reference Library.
		Value Type:			The data type used to hold the value associated with the property. For 
							example, CFStringRef or UInt32
		Access:				How a host application can access the property in a hosted audio unit: 
							read only, write only, or read/write.
		Description:		A description of the property's role.

	The descriptions in this file apply to typical or recommended usage. Audio unit developers can
	vary the way each property is used. For example, a property may be described as applying to both
	input and output scopes, but a given audio unit may implement the property on the input scope
	only. As another example, a property may be described here as having read/write access, but an
	audio unit may implement the property as read only.

	The properties are divided into two primary sections:
		(1) Core/Embedded Implementation
			- these properties are available on all platforms where audio units are available
		
		(2) OS X 
			- these properties are available on only available on OS X
*/

#ifndef AudioToolbox_AudioUnitProperties_h
#define AudioToolbox_AudioUnitProperties_h

#include <AudioToolbox/AUComponent.h>

CF_ASSUME_NONNULL_BEGIN

//=====================================================================================================================
#pragma mark Overview

#pragma mark -
#pragma mark Core Implementation
#pragma mark -

/*!
    @enum           Audio Unit scope types
    @abstract       The scope IDs for audio units define basic roles and contexts for an audio unit's state.
    @discussion		Each scope is a discrete context. Apple reserves scope IDs from 0 through 1024.

	@constant		kAudioUnitScope_Global	The context for audio unit characteristics that apply to the audio unit as a 
											whole
	@constant		kAudioUnitScope_Input	The context for audio data coming into an audio unit
	@constant		kAudioUnitScope_Output	The context for audio data leaving an audio unit
	@constant		kAudioUnitScope_Group	A context specific to the control scope of parameters (for instance, 
											MIDI Channels is an example of this scope)
	@constant		kAudioUnitScope_Part	A distinct rendering context. For instance a single timbre in a multi-timbral 
											instrument, a single loop in a multi looping capable looper unit, etc.
	@constant		kAudioUnitScope_Note	A scope that can be used to apply changes to an individual note. The 
											elementID used with this scope is the unique note ID returned from
											a started note (see MusicDeviceStartNote)
	@constant		kAudioUnitScope_Layer	A context which functions as a layer within a part and allows
											grouped control of LayerItem-scope parameters.
											An example is the percussive attack layer for an electric organ instrument
	@constant		kAudioUnitScope_LayerItem	A scope which represents an individual element within a particular Layer scope.
											The individual sample zones, envelope generators, and filters within a synth are
											examples of this.
*/
CF_ENUM(AudioUnitScope) {
	kAudioUnitScope_Global		= 0,
	kAudioUnitScope_Input		= 1,
	kAudioUnitScope_Output		= 2,
	kAudioUnitScope_Group		= 3,
	kAudioUnitScope_Part		= 4,
	kAudioUnitScope_Note		= 5,
	kAudioUnitScope_Layer		= 6,
	kAudioUnitScope_LayerItem	= 7
};


//=====================================================================================================================
#pragma mark Audio Unit Properties

/*!
    @enum           Generic Property IDs
    @abstract       Properties that can apply to any audio unit.
	
	@constant		kAudioUnitProperty_ClassInfo
						Scope:			Global (or Part for a part scope preset)
						Value Type:		CFDictionaryRef
						Access:			Read / Write
						
						The complete state of an audio unit if on global scope. An audio unit that supports part scope, may also support presets on the part scope
						that apply to individual parts.
						
						After a host sets this property it needs to notify the parameter listeners that the values of the parameters of an AU may have changed (so
						views, etc, can update their state). Something like the following code should be used:
						
						<code>
						#include <AudioToolbox/AudioUnitUtilities.h>
						
						AudioUnitParameter changedUnit;
						changedUnit.mAudioUnit = theChangedAU;
						changedUnit.mParameterID = kAUParameterListener_AnyParameter;
						AUParameterListenerNotify (NULL, NULL, &changedUnit);
						</code>

						
	@constant		kAudioUnitProperty_MakeConnection
						Scope:			Input
						Value Type:		AudioUnitConnection
						Access:			Write
	
	@constant		kAudioUnitProperty_SampleRate
						Scope:			Input / Output
						Value Type:		Float64
						Access:			Read / Write
						
	@constant		kAudioUnitProperty_ParameterList
						Scope:			Any
						Value Type:		AudioUnitParameterID
						Access:			Read
						
						The list of parameter IDs on the specified scope
						
	@constant		kAudioUnitProperty_ParameterInfo
						Scope:			Any
						Element:		AudioUnitParameterID of the parameter being queried
						Value Type:		AudioUnitParameterInfo
						Access:			Read
						
						The info struct describes the general characteristics of an individual parameterID
						
	@constant		kAudioUnitProperty_FastDispatch
						Scope:			Global
						Value Type:		void* (function pointer)
						Access:			Read
						
						The caller provides the selector for a given audio unit API, and retrieves a function pointer for that selector. For instance,
						this enables the caller to retrieve the function pointer for the AudioUnitRender call, so that call can be made directly
						through to the audio unit to avoid the overhead of the ComponentMgr's dispatch.
	
	@constant		kAudioUnitProperty_CPULoad
						Scope:			Global
						Value Type:		Float64
						Access:			Read
						
						Can be used to retrieve the duty cycle (as a value from 0 to 1) of the render time that an audio unit is spending in its render call.
	
	@constant		kAudioUnitProperty_StreamFormat
						Scope:			Input / Output
						Value Type:		AudioStreamBasicDescription
						Access:			Read / Write
						
						An AudioStreamBasicDescription is used to specify the basic format for an audio data path. For instance, 2 channels, 44.1KHz, Float32 linear pcm.
						The value can be both set and retrieve from an I/O element (bus)
	
	@constant		kAudioUnitProperty_ElementCount
						Scope:			Any (though Global scope will always have an element count of 1)
						Value Type:		UInt32
						Access:			Read / Write
						
						Most audio units will only implement the read version of this call, thus they would have a fixed bus topology (number of input and output elements/buses).
						Some audio units possess the capability to add or remove elements, so in that case this property will be writable.
						
	@constant		kAudioUnitProperty_Latency
						Scope:			Global
						Value Type:		Float64
						Access:			Read
						
						The processing latency (the time it takes an audio unit to represent an input in its audio output) specified in seconds
						
	@constant		kAudioUnitProperty_SupportedNumChannels
						Scope:			Global
						Value Type:		AUChannelInfo array
						Access:			Read
						
						The size of this property will represent the number of AUChannelInfo structs that an audio unit provides. Each entry describes a particular number of 
						channels on any input, matched to a particular number of channels on any output. Thus an entry {2, 2} says the audio unit will support a channel configuration
						of 2 channels on an input and 2 channels on an output.
						
						Negative numbers (-1, -2) are used to indicate *any* number of channels. So {-1, -1} means any number of channels on input and output as long as they are the same.
						{-1, -2} means any number of channels on input or output buses
						
						A negative number less than -2 is used to indicate a total number of channels across every bus on that scope, regardless of how many channels are set on any
						particular bus.
						
						Zero on any side (typically only input) means that the audio unit doesn't have any input elements, and is expressing the capability of configuring its output channels.
						
	@constant		kAudioUnitProperty_MaximumFramesPerSlice
						Scope:			Global
						Value Type:		UInt32
						Access:			Read / Write
						
						This property is used to describe to an audio unit the maximum number of samples it will be asked to produce on any single given call to audio unit render. 
						
						If an audio unit can require more or less input data than its output request, then it should limit any given request for input to this number of frames (that is,
						it should "break up" its input pulls).
	
	@constant		kAudioUnitProperty_SetExternalBuffer
						Scope:			Global
						Value Type:		AudioUnitExternalBuffer
						Access:			Write
						
						This is used to provide to an audio unit a buffer that it can use with its input render callback's audio buffer list
	
	@constant		kAudioUnitProperty_ParameterValueStrings
						Scope:			Any
						Element:		AudioUnitParameterID of the parameter being queried 
						Value Type:		CFArrayRef
						Access:			Read
						
						Some audio unit parameters that are of an index type, can also provide names for each value of the parameter. This property returns an array containing CFStrings, where
						each element in the array is the name that should be used for that parameter value. The size of the array should be the same as the range between the parameters min and max values.
						The array's strings can then be used to build a menu for that parameter.
	
	@constant		kAudioUnitProperty_GetUIComponentList
						Scope:			Any
						Value Type:		AudioComponentDescription array
						Access:			Read
						
						Presents an array of AudioComponentDescription that are of type 'auvw' (AudioUnitCarbonView). These are the carbon based custom views for that audio unit. 
	
	@constant		kAudioUnitProperty_AudioChannelLayout
						Scope:			Input/Output
						Value Type:		struct AudioChannelLayout
						Access:			read/write

						Description:
						Describes for a given scope/element the order of channels within a given stream. 
						The number of channels it describes must match the number of channels set for that 
						scope/element. Each input and output bus in an audio unit can have one instance of 
						this property. 
						
						Some audio units require this property. For example, the 3DMixer unit must 
						implement this property on its output bus. If a host application attempts to 
						clear the value of this property on a bus that requires a valid value, the
						audio unit will return a kAudioUnitErr_InvalidPropertyValue error.
						
						Input and output buses can be in one of three states in regard to Audio 
						channel layout:
						
						1. implemented and set
						2. implemented but not set 
						3. unimplemented 
						
						Requesting the value of this property when it is implemented but not set
						results in a kAudioUnitErr_PropertyNotInUse error.
						
						Use the kAudioUnitProperty_AudioChannelLayout property whenever channel
						layout is relevant. By comparison, the kAudioUnitProperty_StreamFormat 
						property cannot specify channel layout or purpose.
						
						See also: kAudioUnitProperty_SupportedChannelLayoutTags, 
						kAudioUnitProperty_StreamFormat.
	 
	@constant		kAudioUnitProperty_TailTime
						Scope:			Global
						Value Type:		Float64
						Access:			Read
						
						The time in seconds that will remain after the last valid input of any audio unit has been processed before the output is silent. For example, this could be the total
						decay time of a reverb or a delay. In general this will be a conservative estimate.
	
	@constant		kAudioUnitProperty_BypassEffect
						Scope:			Global
						Value Type:		UInt32
						Access:			Read / Write
						
						A boolean value that can be used to bypass the processing in an effect unit, so that the input is passed unchanged through to the output
	
	@constant		kAudioUnitProperty_LastRenderError
						Scope:			Global
						Value Type:		OSStatus
						Access:			Read
						
						This property is set if there is an error in AudioUnitRender. The AU will then fire a property changed notification to any listeners on this property and 
						those listeners can then use this property ID to retrieve that error.
	
	@constant		kAudioUnitProperty_SetRenderCallback
						Scope:			Input
						Value Type:		AURenderCallbackStruct
						Access:			Write
						
						This is used to provide the audio unit with input on the specified element (input bus) with audio data from the provided callback. The callback is delivered a buffer list
						which it must fill in with audio data. If no data is available, it should set the audio data to 0 (silence). In the normal case, f an error is returned, the audio is not processed 
						and the audio unit will return an error from AudioUnitRender.

	@constant		kAudioUnitProperty_FactoryPresets
						Scope:			Global
						Value Type:		CFArray of AUPreset structures
						Access:			Read
						
						An array of preset structures that provide a name and number for each preset. A factory preset is then chosen using the PresentPreset property. 
	
	@constant		kAudioUnitProperty_ContextName
						Scope:			Global
						Value Type:		CFString
						Access:			Read / Write
						
						The host can set this as information to the audio unit to describe something about the context within which the audio unit is instantiated. For instance, "track 3" could
						be set as the context, so that the audio unit's view could then display "My audio unit on track 3" as information to the user of the particular context for any audio unit.
						
	@constant		kAudioUnitProperty_RenderQuality
						Scope:			Global
						Value Type:		UInt32
						Access:			Read / Write
						
						A value (0 - 127) that can be used to control the quality (complexity) of the rendering operation. A typical usage is to set render quality to maximum for best quality, but
						if CPU usage is a concern a lesser quality can be set to trade off render quality.
	
	@constant		kAudioUnitProperty_HostCallbacks
						Scope:			Global
						Value Type:		HostCallbackInfo
 						Access:			Write
						
						The audio unit should only call the host callbacks while it is in its render function. The audio unit must provide the client info when calling the callbacks as provided
						by the host. They are provided as a means for an audio unit to gain information from the host about parameters that may affect its rendering operation. 
						For example, what is the current beat of the host, is the transport running, and so forth.
						
						Any of the parameters of the callback function, when called by the audio unit, can be NULL. This indicates that the unit doesn't want to know that particular information. 
						The exception is that the unit must always specify the HostUserData which was be supplied to the unit when the property was set.

						If the host is unable to provide the requested information then it can return the kAudioUnitErr_CannotDoInCurrentContext error code

	@constant		kAudioUnitProperty_InPlaceProcessing
						Scope:			Global
						Value Type:		UInt32
						Access:			Read / Write
						
						A property that can be used to determine if the audio unit can process input data on the same data as is provided to it, and if so this can be turned off if the host
						has a particular buffer management strategy and such an operation would defeat that.
	
	@constant		kAudioUnitProperty_ElementName
						Scope:				any
						Value Type:			CFStringRef
						Access:				read/write
						Description:
						The name of the specified element. The Host owns a reference to this property value 
						(as with all other CF properties), and should release the string retrieved or used when setting.
	
	@constant		kAudioUnitProperty_CocoaUI
						Scope:				Global
						Value Type:			struct AudioUnitCocoaViewInfo
						Access:				read

						Publishes the audio unit's custom Cocoa NSViews. The Host can determine how big this structure is by 
						querying the size of the property (i.e., How many alternate UI classes there are for the unit)
						Typically, most audio units will provide 1 UI class per unit
	
	@constant		kAudioUnitProperty_SupportedChannelLayoutTags
						Scope:				Input/Output
						Value Type:			AudioChannelLayoutTags[ variable number of elements ]
						Access:				read only

						Used with GetProperty to ascertain what an audio unit understands about
						laying out of channel orders. This will normally return one or more of the specified layout tags.
						
						When a specific set of layouts are returned, the client then uses the 
						kAudioUnitProperty_AudioChannelLayout property (with one of those layout tags specified) to set 
						the unit to use that layout. In this case the client (and the audio unit when reporting its 
						AudioChannelLayout) is only expected to have set an AudioChannelLayout which only sets the 
						layout tag as the valid field.
						
						Custom Channel Maps:
						Some audio units may return the tag:
							kAudioChannelLayoutTag_UseChannelDescriptions
						
						In this case, the host then can look at supported number of channels on that scope
						(using the kAudioUnitProperty_SupportedNumChannels), and supply an AudioChannelLayout with the 
						kAudioUnitProperty_AudioChannelLayout property to specify the layout, number of channels
						and location of each of those channels. This custom channel map MUST have a channel valence
						that is supported by the Audio Unit.
						
						The UseChannelBitmap field is NOT used within the context of the AudioUnit.
	
	@constant		kAudioUnitProperty_ParameterIDName
						Scope:				any
						Element:			AudioUnitParameterID of the parameter being queried
						Value Type:			AudioUnitParameterIDName
						Access:				read

						An audio unit returns the full parameter name in the GetParameterInfo struct/property.
						In some display situations however, there may only be room for a few characters, and
						truncating this full name may give a less than optimal name for the user. Thus, 
						this property can be used to ask the audio unit whether it can supply a truncated name, with
						the host suggesting a length (number of characters). If the unit returns a longer
						name than the host requests, that name may be truncated to the requested characters in display.
						The unit could return a shorter name than requested as well. The unit returns a CFString
						that should be released by the host. When using this property, the host asks for
						the name in the same scope and element as the unit publishes the parameter.

	@constant		kAudioUnitProperty_ParameterClumpName
						Scope:				any
						Value Type:			AudioUnitParameterIDName
						Access:				read

						This works in a similar manner to the ParameterIDName property, except that the inID
						value is one of the clumpID's that are returned with the audio unit's ParameterInfo 
						structure.
	
	@constant		kAudioUnitProperty_PresentPreset
						Scope:				Global/Part
						Value Type:			AUPreset
						Access:				read/write

						This property replaces the deprecated CurrentPreset property, due to the ambiguity of
						ownership of the CFString of the preset name in the older CurrentPreset property. 
						With PresentPreset the client of the audio unit owns the CFString when it retrieves the
						preset with PresentPreset and is expected to release this (as with ALL properties 
						that retrieve a CF object from an audio unit).
	
	@constant		kAudioUnitProperty_OfflineRender
						Scope:				Global
						Value Type:			UInt32
						Access:				Read / Write
						
						This is used by the host to indicate when an audio unit (that normally operates within a general real-time calling model) is 
						rendering in an offline context. A typical usage of this is to set this to true when the rendering operation an audio unit is being used within is 
						going to write out the results to a file. The value defaults to false, as the common usage of audio units is for real-time processing
	
	@constant		kAudioUnitProperty_ParameterStringFromValue
						Scope:				any
						Value Type:			AudioUnitParameterStringFromValue
						Access:				read

						This property is used with parameters that are marked with the
						kAudioUnitParameterFlag_HasName parameter info flag. This indicates that some
						(or all) of the values represented by the parameter can and should be
						represented by a special display string.
						
						This is NOT to be confused with kAudioUnitProperty_ParameterValueStrings. That property
						is used with parameters that are indexed and is typically used for instance to build
						a menu item of choices for one of several parameter values.
						
						kAudioUnitProperty_ParameterStringFromValue can have a continuous range, and merely states
						to the host that if it is displaying those parameter's values, they should request
						a name any time any value of the parameter is set when displaying that parameter.
						
						For instance (a trivial example), a unit may present a gain parameter in a dB scale,
						and wish to display its minimum value as "negative infinity". In this case, the audio unit
						will not return names for any parameter value greater than its minimum value - so the host
						will then just display the parameter value as is. For values less than or equal to the 
						minimum value, the audio unit will return a string for "negative infinity" which the host can
						use to display appropriately.
						
						A less trivial example might be a parameter that presents its values as seconds. However,
						in some situations this value should be better displayed in a SMPTE style of display:
							HH:MM:SS:FF
						In this case, the audio unit would return a name for any value of the parameter.
						
						The GetProperty call is used in the same scope and element as the inParamID 
						that is declared in the struct passed in to this property.
						
						If the *inValue member is NULL, then the audio unit should take the current value
						of the specified parameter. If the *inValue member is NOT NULL, then the audio unit should
						return the name used for the specified value.
						
						On exit, the outName may point to a CFStringRef (which if so must be released by the caller).
						If the parameter has no special name that should be applied to that parameter value,
						then outName will be NULL, and the host should display the parameter value as
						appropriate.
					
	
	@constant		kAudioUnitProperty_ParameterValueFromString
						Scope:				any
						Value Type:			AudioUnitParameterValueFromString
						Access:				read
	
						This property returns the value of a parameter from its string representation. See kAudioUnitProperty_ParameterStringFromValue.
						
	@constant		kAudioUnitProperty_IconLocation	
						Scope:				Global
						Value Type:			CFURLRef
						Access:				Read
						
						A URL that will specify the location of an icon file that can be used when presenting UI for this audio unit.
	
	@constant		kAudioUnitProperty_PresentationLatency
						Scope:				Input/Output
						Value Type:			Float64
						Access:				write

						This property is set by a host to describe to the audio unit the presentation latency of both
						any of its input and/or output audio data. 
						It describes this latency in seconds. A value of zero means either no latency
						or an unknown latency.
						
						This is a write only property because the host is telling the audio unit the latency of both the 
						data it provides it for input and the latency from getting the data from the unit until it is 
						presented.
						
						The property is should be set on each active input and output bus (Scope/Element pair). 
						For example, an audio unit with multiple outputs will have the output data it produces processed 
						by different audio units, etc before it is mixed and presented. Thus, in this case, each output 
						element could have a different presentation latency.
						
						This should not be confused with the Latency property, where the audio unit describes to the host 
						any processing latency it introduces between its input and its output.
						
						For input:
							Describes how long ago the audio given to an audio unit was acquired. For instance, when 
							reading from a file to the first audio unit, then its input presentation latency will be zero. 
							When processing audio input from a  device, then this initial input latency will be the 
							presentation latency of the device itself, the device's safety offset and latency.
							
							The next audio unit's (connected to that first unit) input presentation latency will be the 
							input presentation latency of the first unit, plus the processing latency (as expressed by 
							kAudioUnitProperty_Latency) of the first unit.
							
						For output:
							Describes how long before the output audio of an audio unit is to be presented. For instance, 
							when writing to a file, then the last audio unit's output presentation latency will be zero. 
							When the audio from that audio unit is to be played to an AudioDevice, then that initial 
							presentation latency will be the latency of the device itself - which is the I/O buffer size, 
							and the device's safety offset and latency
							
							The previous audio unit's (connected to this last unit) output presentation latency will be that 
							initial presentation latency plus the processing latency (as expressed by 
							kAudioUnitProperty_Latency) of the last unit.
							
						So, for a given audio unit anywhere within a mixing graph, the input and output presentation 
						latencies describe to that unit how long from the moment of generation it will take for its 
						input to arrive, and how long it will take for its output to be presented. 
						
						You can use this property, for example, to provide metering for an audio unit that
						is generating output to be presented to the user at a future time.
	
	@constant		kAudioUnitProperty_DependentParameters
						Scope:				any
						Value Type:			array of AUDependentParameter
						Access:				read
		
						This property is used for parameters with the kAudioUnitParameterFlag_IsGlobalMeta 
						or kAudioUnitParameterFlag_IsElementMeta flags set. Hosts applications (and the 
						AudioUnitParameterListener mechanism) can interrogate this property to determine which parameters 
						are dependent on a
						meta-parameter.
						
						For parameters marked with kAudioUnitParameterFlag_IsGlobalMeta, any non-global
						dependent parameters are assumed to be dependent in every element of their scope.
						
						For parameters marked with kAudioUnitParameterFlag_IsElementMeta, then its dependent
						parameters must all be the same scope, and are assumed to apply only within a single element,
						not to other instances of the same parameter in other elements.
	
	@constant		kAudioUnitProperty_AUHostIdentifier
						Scope:				Global
						Value Type:			AUHostVersionIdentifier
						Access:				write

						Determine which application (and which version) an audio unit is being hosted by. 
						This is made more complex through the intervention of audio units such as Kore, that are hosting 
						other audio units (in this case of course, the real host of the audio unit is the hosting unit, 
						not the host application, so the previous mechanism of getting the main bundle ID is no longer 
						correct). 
						
						There are also inconsistencies in the way that bundle identifiers are applied (with apps changing 
						these from version to version), and we'd prefer to see a more consistent identifier used with 
						this property. This is in spirit similar to the string returned by CFBundle API, except that we 
						require this host string be consistent and reliable through different revisions of the host.

						The audio unit is responsible for retaining the hostName string if it needs to use it past the 
						duration of the actual call. The host should set this property as early as possible within the 
						lifetime of the unit in a session.
						
						This API used to take a NumVersion struct. It is redefined to take an AUHostVersionIdentifier struct
						which is binary compatible with the existing usage, but not source compatible.
						
	@constant		kAudioUnitProperty_MIDIOutputCallbackInfo
						Scope:				Global
						Value Type:			CFArrayRef
						Access:				read

						Used to determine how many MIDI output streams the audio unit can generate  (and the name for 
						each of these outputs). Each MIDI output is a complete MIDI data stream, such as embodied by a 
						MIDIEndpointRef in CoreMIDI.
						
						The host can retrieve an array of CFStringRefs published by the audio unit, where :
							- the size of the array is the number of MIDI Outputs the audio unit supports
							- each item in the array is the name for that output at that index
						
						The host should release the array when it is finished with it.
						
						Once the host has determined that the audio unit supports this feature, it can then provide a 
						callback, through which the audio unit can send the MIDI data.
						See the documentation for the kAudioUnitProperty_MIDIOutputCallback property.
	
	@constant		kAudioUnitProperty_MIDIOutputCallback
						Scope:				Global
						Value Type:			AUMIDIOutputCallbackStruct
						Access:				write

						The host sets this property on the audio unit with the callback (and its user data) set 
						appropriately.
						
						Operational Parameters:
							In the render call, just as is the expected usage of the AUHostCallbacks, the audio unit can 
							call the provided callback to provide MIDI data to the host that it will associate with the 
							current AudioUnitRender call in process.

						The audio unit in the callback provides:
							- the user data provided by the host when the callback was established
							- the AudioTimeStamp that was provided to the audio unit for this particular call of 
								AudioUnitRender
							- the output number to associate this MIDI data with
							- a MIDI Packet List containing MIDI data. The time stamp values contained within the 
							MIDIPackets in this list are **sample offsets*** from the AudioTimeStamp provided. 
							This allows MIDI data to be time-stamped with a sample offset that is directly associated 
							with the audio data it is generating in the current call to the AudioUnitRender function

						There is no implied or expected association between the number (or position) of an audio unit's 
						audio or MIDI outputs.

	@constant		kAudioUnitProperty_InputSamplesInOutput
						Scope:			Global
						Value Type:		struct AUInputSamplesInOutputCallbackStruct
						Access: 		read/write
 
						An audio unit calls this callback at the end of its render call. The audio unit supplies the 
						following information:

						outputTime      - The timestamp passed in to the audio unit's render call. This timestamp 
											represents the time of the first output sample.
						inputSample     - The sample number of the first input sample that is present in the output 
											audio.
						numInputSamples - The number of input samples that were used and are present in the output 
											audio.

						This property allows a host application to determine which input samples correspond to a sample 
						in the output buffer. It is useful only for audio units that do time-stretching, such as the 
						AUVarispeed and AUTimePitch units, where the relationship between input and output samples is 
						non-trivial. For these units, the range of input samples that correspond to an output buffer 
						typically differs from the range of input samples that were pulled for that render call. 
						This difference arises because of internal buffering, processing latency, and other factors.
	
	@constant		kAudioUnitProperty_ClassInfoFromDocument
						Scope:			Global
						Value Type:		CFDictionary
						Access: 		read/write
 
						If the audio unit implements this property then it is going to do different actions establishing
						its state from a document rather than from a user preset. Thus, a host app should use this property
						first (instead of kAudioUnitProperty_ClassInfo) when restoring the state of an audio unit when 
						opening a document. If the audio unit returns an error (or doesn't implement this property) then
						the host should use the same preset with the kAudioUnitProperty_ClassInfo. 
 

	@constant		kAudioUnitProperty_ShouldAllocateBuffer
						Scope:			input/output elements (settable per element)
						Value Type:		UInt32
						Access: 		read/write
 
						By default this value is true. This affects the allocations of the buffers for I/O (the mData field
						of the AudioBufferList used with AudioUnitRender, callbacks and connections)
						
						If true, the element will create a buffer for rendering into.
						
						If false, the element will not create a buffer for rendering.
						
						For example, if the audio unit is only ever going to have a connection as its input and never a callback, then
						it should not need to create a buffer (the API contract expects an audio unit to provide a buffer for
						callbacks, but no buffer for connections).
						
						If the audio unit is always going to be pulled for audio with the client providing audio data buffers to 
						the AudioUnitRender call, then it will never need to create an audio buffer on the output side.
						
						So, this property can be used to control the default allocation strategy of an audio unit. If the audio unit
						needs a buffer, but one hasn't been allocated, then an error will be thrown from that call to AudioUnitRender.
						
						This property cannot be set on Initialised audio units as it may end up reallocating memory.


	@constant		kAudioUnitProperty_FrequencyResponse
						Scope:			input/output elements (settable per element)
						Value Type:		AudioUnitFrequencyResponseBin
						Access: 		read
						
						The property provides a way for a user interface view to get points for drawing a graph of the frequency
						response of the AU. 
						
						An array of AudioUnitFrequencyResponseBin are passed in to kAudioUnitProperty_FrequencyResponse
						with the mFrequency field filled in. The array is returned with the mMagnitude fields filled in.
						If fewer than kNumberOfResponseFrequencies are needed, then the first unused bin should be marked with 
						a negative frequency.
	
	@constant		kAudioUnitProperty_ParameterHistoryInfo
						Scope:			Global
						Value Type:		AudioUnitParameterHistoryInfo
						Access: 		read
						
						For parameters which have kAudioUnitParameterFlag_PlotHistory set, getting this property fills out the 
						AudioUnitParameterHistoryInfo struct containing the recommended update rate and history duration.

	@constant		kAudioUnitProperty_NickName
						Scope:			Global
						Value Type:		CFStringRef
						Access:			read/write
						 
						Provides a way for a host to set a custom name on an AU. 
 
						An example of when this is useful is when a host is managing a processing chain that contains multiple AU
						instances of the same subtype (and type and manufacturer). The host uses this property to assign a 
						unique name to each AU instance indicating what that particular instance's function is in the processing
						chain and can later query the property to distinguish between AU instances with the same type/subtype/manu
						tuple. It is the host's responsibility to keep the names unique if uniqueness is required. 
 
						When getting this property, ownership follows Core Foundation's 'Copy Rule'. This property may return NULL 
						which indicates that no name has been set on the AU.

	@constant		kAudioUnitProperty_RequestViewController
						Scope:			Global
						Value Type:		block: void (^)(AUViewControllerBase *)
						Access:			write
						
						If the audio unit is implemented using the version 3 API, it may provide a
						view controller, returned via this property. As with any other CoreFoundation
						or Foundation object returned by AudioUnitGetProperty, the caller must
						release the returned reference (i.e. the Copy rule is used).

	@constant		kAudioUnitProperty_ParametersForOverview
						Scope:			Global
						Value Type:		variably-sized array of struct AudioUnitParameter
						Access:			read
						
						A host may query an audio unit for a list of its N most important
						parameters, via this property. The size of the array passed to
						AudioUnitGetProperty controls the number of AudioUnitParameter values
						returned.
    @constant       kAudioUnitProperty_SupportsMPE
                        Scope:          Global
                        Value Type:     UInt32
                        Access:         read
                        
                        Indicates whether an audio unit supports Multi-dimensional Polyphonic Expression.
*/
CF_ENUM(AudioUnitPropertyID)
{
// range (0 -> 999)
	kAudioUnitProperty_ClassInfo					= 0,
	kAudioUnitProperty_MakeConnection				= 1,
	kAudioUnitProperty_SampleRate					= 2,
	kAudioUnitProperty_ParameterList				= 3,
	kAudioUnitProperty_ParameterInfo				= 4,
	kAudioUnitProperty_CPULoad						= 6,
	kAudioUnitProperty_StreamFormat					= 8,
	kAudioUnitProperty_ElementCount					= 11,
	kAudioUnitProperty_Latency						= 12,
	kAudioUnitProperty_SupportedNumChannels			= 13,
	kAudioUnitProperty_MaximumFramesPerSlice		= 14,
	kAudioUnitProperty_ParameterValueStrings		= 16,
	kAudioUnitProperty_AudioChannelLayout			= 19,  
	kAudioUnitProperty_TailTime						= 20,
	kAudioUnitProperty_BypassEffect					= 21,
	kAudioUnitProperty_LastRenderError				= 22,
	kAudioUnitProperty_SetRenderCallback			= 23,
	kAudioUnitProperty_FactoryPresets				= 24,
	kAudioUnitProperty_RenderQuality				= 26,
	kAudioUnitProperty_HostCallbacks				= 27,
	kAudioUnitProperty_InPlaceProcessing			= 29,
	kAudioUnitProperty_ElementName					= 30,
	kAudioUnitProperty_SupportedChannelLayoutTags	= 32,
	kAudioUnitProperty_PresentPreset				= 36,
	kAudioUnitProperty_DependentParameters			= 45,
	kAudioUnitProperty_InputSamplesInOutput			= 49,
	kAudioUnitProperty_ShouldAllocateBuffer			= 51,
	kAudioUnitProperty_FrequencyResponse			= 52,
	kAudioUnitProperty_ParameterHistoryInfo			= 53,
	kAudioUnitProperty_NickName                     = 54,
    kAudioUnitProperty_OfflineRender				= 37,
	kAudioUnitProperty_ParameterIDName				= 34,
	kAudioUnitProperty_ParameterStringFromValue		= 33,
	kAudioUnitProperty_ParameterClumpName			= 35,
	kAudioUnitProperty_ParameterValueFromString		= 38,
	kAudioUnitProperty_ContextName					= 25,
	kAudioUnitProperty_PresentationLatency			= 40,
	kAudioUnitProperty_ClassInfoFromDocument		= 50,
	kAudioUnitProperty_RequestViewController		= 56,
	kAudioUnitProperty_ParametersForOverview		= 57,
	kAudioUnitProperty_SupportsMPE					= 58,

#if !TARGET_OS_IPHONE
	kAudioUnitProperty_FastDispatch					= 5,
	kAudioUnitProperty_SetExternalBuffer			= 15,
	kAudioUnitProperty_GetUIComponentList			= 18,
	kAudioUnitProperty_CocoaUI						= 31,
	kAudioUnitProperty_IconLocation					= 39,
	kAudioUnitProperty_AUHostIdentifier				= 46,
#endif

	kAudioUnitProperty_MIDIOutputCallbackInfo       = 47,
	kAudioUnitProperty_MIDIOutputCallback           = 48,
};

#if AU_SUPPORT_INTERAPP_AUDIO
/*
    @enum           Inter-App Audio Property IDs
    @abstract       Properties used in inter-app audio.

	@constant		kAudioUnitProperty_RemoteControlEventListener
	@discussion			Scope:			Global
						Value Type:		AudioUnitRemoteControlEventListener
						Access:			read/write
						
					Provides a way for a host to receive AudioUnitRemoteControlEvents from a remote "node"
					audio unit. The supplied listener block is called when the audio unit sends a remote
					control event.

	@constant		kAudioUnitProperty_IsInterAppConnected
	@discussion			Scope: Global
						Value Type: UInt32 (0-1)
						Access: read-only
					
					Both host and node apps can query and listen to this property to determine when
					the audio unit has been connected to another app.

	@constant		kAudioUnitProperty_PeerURL
	@discussion			Scope: Global
						Value Type: CFURLRef
						Access: read-only
					
					Both host and node apps can query this property to obtain a URL which, when
					opened, will activate the other app.
					
					N.B. This URL is only valid while the host has an open connection to the node.
*/
CF_ENUM(AudioUnitPropertyID)
{
	kAudioUnitProperty_RemoteControlEventListener	= 100,
	kAudioUnitProperty_IsInterAppConnected			= 101,
	kAudioUnitProperty_PeerURL						= 102
};
#endif // AU_SUPPORT_INTERAPP_AUDIO



/*!
    @abstract       Keys contains in an audio unit preset (ClassInfo) dictionary
    @discussion     These strings are used as keys in the AUPreset-"classInfo" dictionary
					The actual keys are CFStrings to use these keys you define the key as:
						static const CFStringRef kMyVersionString = CFSTR(kAUPresetVersionKey);
*/
#define kAUPresetVersionKey 		"version"
#define kAUPresetTypeKey 			"type"
#define kAUPresetSubtypeKey 		"subtype"
#define kAUPresetManufacturerKey	"manufacturer"
#define kAUPresetDataKey			"data"
#define kAUPresetNameKey			"name"
#define kAUPresetNumberKey			"preset-number"
#define kAUPresetRenderQualityKey	"render-quality"
#define kAUPresetCPULoadKey			"cpu-load"
#define kAUPresetElementNameKey		"element-name"
#define kAUPresetExternalFileRefs	"file-references"

#if !TARGET_OS_IPHONE
	// these are keys to use when a preset contains data from other plugin formats
	// vstdata is used to signify VST state from a vst "bank"
	#define kAUPresetVSTDataKey			"vstdata"
	// vstpreset is used to signify VST state from a vst "preset"
	#define kAUPresetVSTPresetKey		"vstpreset"

	#define kAUPresetMASDataKey			"masdata"
#endif

/*!
    @define         kAUPresetPartKey
    @discussion     This key if present, distinguishes a global preset that is set 
					on the global scope with a part-based preset that is set on the part scope. 
					The value of this key is audio unit defined
*/
#define kAUPresetPartKey			"part"


/*!
    @struct         AudioUnitConnection
    @abstract       This structure contains the information needed to make a connection between a source
					and destination audio unit.
	@discussion		The structure is set on the destination audio unit's input element
    @var            sourceAudioUnit
						The audio unit that is the source for the connection
    @var            sourceOutputNumber
						The source audio unit's output element to be used in the connection
    @var            destInputNumber
						The destination audio unit's input element to be used in the connection						
*/
typedef struct AudioUnitConnection {
	AudioUnit __nullable	sourceAudioUnit;
	UInt32					sourceOutputNumber;
	UInt32					destInputNumber;
} AudioUnitConnection;

/*!
	@struct			AUChannelInfo
	@abstract		Define an audio unit's channel handling capabilities
*/
typedef struct AUChannelInfo {
	SInt16		inChannels;
	SInt16		outChannels;
} AUChannelInfo;

/*!
	@struct			AudioUnitExternalBuffer
	@abstract		Allow a host to tell an audio unit to use the provided memory for its input callback
*/
typedef struct AudioUnitExternalBuffer {
	Byte *		buffer;
	UInt32		size;
} AudioUnitExternalBuffer;

/*!
	@struct			AURenderCallbackStruct
	@abstract		Used by a host when registering a callback with the audio unit to provide input
*/
typedef struct AURenderCallbackStruct {
	AURenderCallback __nullable	inputProc;
	void * __nullable			inputProcRefCon;
} AURenderCallbackStruct;

/*!
	@struct			AUPreset
	@abstract		Used to publish and set factory presets on an audio unit
	@var  			presetNumber
						If < 0, then preset is a user preset
						If >= 0, then this field is used to select the factory preset
	@var  			presetName
						If a factory preset, the name of the specified factory preset
*/
typedef struct AUPreset {
	SInt32					presetNumber;
	CFStringRef	__nullable	presetName;
} AUPreset;

/*!
	@enum			RenderQuality
	@abstract		Used to get/set a render quality setting on an audio unit
	@discussion		Typically, this property is used to trade-off between CPU usage, latency
					and the quality of the audio unit's processing/output.
*/
enum {
	kRenderQuality_Max								= 127,
	kRenderQuality_High								= 96,
	kRenderQuality_Medium							= 64,
	kRenderQuality_Low								= 32,
	kRenderQuality_Min								= 0
};


/*!
	@enum			kNumberOfResponseFrequencies
	@abstract		The maximum number of frequency response bins for kAudioUnitProperty_FrequencyResponse.
	@discussion		An array of AudioUnitFrequencyResponseBin are passed in to kAudioUnitProperty_FrequencyResponse
					with the mFrequency field filled in. The array is returned with the mMagnitude fields filled in.
					If fewer than kNumberOfResponseFrequencies are needed, then the first unused bin should be marked with 
					a negative frequency.
*/
enum {
	kNumberOfResponseFrequencies = 1024
};

/*!
	@struct			AudioUnitFrequencyResponseBin
	@abstract		Structure used to get the magnitude of the frequency response at a particular frequency via kAudioUnitProperty_FrequencyResponse. 
	@discussion		An array of AudioUnitFrequencyResponseBin are passed in to kAudioUnitProperty_FrequencyResponse
					with the mFrequency field filled in. The array is returned with the mMagnitude fields filled in.
					If fewer than kNumberOfResponseFrequencies are needed, then the first unused bin should be marked with 
					a negative frequency.
*/
typedef struct AudioUnitFrequencyResponseBin
{
	Float64		mFrequency;
	Float64		mMagnitude;
} AudioUnitFrequencyResponseBin;

/*!
	@typedef		HostCallback_GetBeatAndTempo
	@abstract		Retrieve information about the current beat and/or tempo
	@discussion
		If the host app has set this callback, then the audio unit can use this to get the current
		beat and tempo as they relate to the first sample in the render buffer. The audio unit can
		call this callback only from within the audio unit render call (otherwise the host is unable
		to provide information accurately to the audio unit as the information obtained is relate to
		the current AudioUnitRender call). If the host cannot provide the requested information, it
		will return kAudioUnitErr_CannotDoInCurrentContext.
	
		The AudioUnit can provide NULL for any of the requested parameters (except for
		inHostUserData) if it is not interested in that particular piece of information

	@param			inHostUserData			Must be provided by the audio unit when it makes this call. It is the client data provided by the host when it set the HostCallbacks property
	@param			outCurrentBeat			The current beat, where 0 is the first beat. Tempo is defined as the number of whole-number (integer) beat values (as indicated by the outCurrentBeat field) per minute.
	@param			outCurrentTempo			The current tempo
*/
typedef OSStatus (*HostCallback_GetBeatAndTempo)(void * __nullable	inHostUserData,
											Float64	* __nullable	outCurrentBeat,
											Float64	* __nullable	outCurrentTempo);

/*!
	@typedef		HostCallback_GetMusicalTimeLocation
	@abstract		Retrieve information about the musical time state of the host
	@discussion
		If the host app has set this callback, then the audio unit can use this to obtain
		information about the state of musical time in the host. The audio unit can call this
		callback only from within the audio unit render call (otherwise the host is unable to
		provide information accurately to the audio unit as the information obtained is relate to
		the current AudioUnitRender call). If the host cannot provide the requested information, it
		will return kAudioUnitErr_CannotDoInCurrentContext.

		The AudioUnit can provide NULL for any of the requested parameters (except for
		inHostUserData) if it is not interested in that particular piece of information

	@param			inHostUserData					Must be provided by the audio unit when it makes this call. It is the client data provided by the host when it set the HostCallbacks property
	@param			outDeltaSampleOffsetToNextBeat	The number of samples until the next whole beat from the start sample of the current rendering buffer
	@param			outTimeSig_Numerator			The Numerator of the current time signature
	@param			outTimeSig_Denominator			The Denominator of the current time signature (4 is a quarter note, etc)
	@param			outCurrentMeasureDownBeat		The beat that corresponds to the downbeat (first beat) of the current measure that is being rendered

*/
typedef OSStatus (*HostCallback_GetMusicalTimeLocation)(void * __nullable	inHostUserData,
												UInt32 * __nullable			outDeltaSampleOffsetToNextBeat,
												Float32 * __nullable		outTimeSig_Numerator,
												UInt32 * __nullable			outTimeSig_Denominator,
												Float64 * __nullable		outCurrentMeasureDownBeat);

/*!
	@typedef		HostCallback_GetTransportState
	@abstract		Retrieve information about the time line's (or transport) state of the host. 
	@discussion
		If the host app has set this callback, then the audio unit can use this to obtain
		information about the transport state of the host's time line. The audio unit can call this
		callback only from within the audio unit render call (otherwise the host is unable to
		provide information accurately to the audio unit as the information obtained is relate to
		the current AudioUnitRender call. If the host cannot provide the requested information, it
		will return kAudioUnitErr_CannotDoInCurrentContext.
	
		The AudioUnit can provide NULL for any of the requested parameters (except for
		inHostUserData) if it is not interested in that particular piece of information
	
	@param			inHostUserData					Must be provided by the audio unit when it makes this call. It is the client data provided by the host when it set the HostCallbacks property
	@param			outIsPlaying					Returns true if the host's transport is currently playing, false if stopped
	@param			outTransportStateChanged		Returns true if there was a change to the state of, or discontinuities in, the host's transport (generally since the callback was last called). Can indicate such state changes as start/top, time moves (jump from one time line to another).
	@param			outCurrentSampleInTimeLine		Returns the current sample count in the time line of the host's transport time.  
	@param			outIsCycling					Returns true if the host's transport is currently cycling or looping
	@param			outCycleStartBeat				If cycling is true, the start beat of the cycle or loop point in the host's transport
	@param			outCycleEndBeat					If cycling is true, the end beat of the cycle or loop point in the host's transport
	
*/
typedef OSStatus (*HostCallback_GetTransportState)(void * __nullable	inHostUserData,
										Boolean * __nullable			outIsPlaying,
										Boolean * __nullable			outTransportStateChanged,
										Float64 * __nullable			outCurrentSampleInTimeLine,
										Boolean * __nullable			outIsCycling,
										Float64 * __nullable			outCycleStartBeat,
										Float64 * __nullable			outCycleEndBeat);

/*!
	@typedef		HostCallback_GetTransportState2
	@abstract		Retrieve information about the time line's (or transport) state of the host. 
	@discussion
		If the host app has set this callback, then the audio unit can use this to obtain
		information about the transport state of the host's time line. The audio unit can call this
		callback only from within the audio unit render call (otherwise the host is unable to
		provide information accurately to the audio unit as the information obtained is relate to
		the current AudioUnitRender call. If the host cannot provide the requested information, it
		will return kAudioUnitErr_CannotDoInCurrentContext.

		The AudioUnit can provide NULL for any of the requested parameters (except for
		inHostUserData) if it is not interested in that particular piece of information
	
	@param			inHostUserData					Must be provided by the audio unit when it makes this call. It is the client data provided by the host when it set the HostCallbacks property
	@param			outIsPlaying					Returns true if the host's transport is currently playing, false if stopped
	@param			outIsRecording					Returns true if the host is currently record-enabled, otherwise false.
	@param			outTransportStateChanged		Returns true if there was a change to the state of, or discontinuities in, the host's transport (generally since the callback was last called). Can indicate such state changes as start/top, time moves (jump from one time line to another).
	@param			outCurrentSampleInTimeLine		Returns the current sample count in the time line of the host's transport time.  
	@param			outIsCycling					Returns true if the host's transport is currently cycling or looping
	@param			outCycleStartBeat				If cycling is true, the start beat of the cycle or loop point in the host's transport
	@param			outCycleEndBeat					If cycling is true, the end beat of the cycle or loop point in the host's transport
	
*/
typedef OSStatus (*HostCallback_GetTransportState2)(void * __nullable	inHostUserData,
										Boolean * __nullable			outIsPlaying,
										Boolean	* __nullable			outIsRecording,
										Boolean * __nullable			outTransportStateChanged,
										Float64 * __nullable			outCurrentSampleInTimeLine,
										Boolean * __nullable			outIsCycling,
										Float64 * __nullable			outCycleStartBeat,
										Float64 * __nullable			outCycleEndBeat);

/*!
	@struct			HostCallbackInfo
	@abstract		Contains the various callbacks for an audio unit to call
	@discussion
		Any callback can be NULL.
*/
typedef struct HostCallbackInfo {
	void * __nullable									hostUserData;
	HostCallback_GetBeatAndTempo __nullable				beatAndTempoProc;
    HostCallback_GetMusicalTimeLocation __nullable		musicalTimeLocationProc;
	HostCallback_GetTransportState __nullable			transportStateProc;
	HostCallback_GetTransportState2 __nullable			transportStateProc2;
} HostCallbackInfo;

/*!
	@struct			AUDependentParameter
	@abstract		Used to represent a dependent parameter that can change as a result of its parent meta-parameter
					changing
*/
typedef struct AUDependentParameter {
	AudioUnitScope			mScope;
	AudioUnitParameterID	mParameterID;
} AUDependentParameter;


#if !TARGET_OS_IPHONE
/*!
	@struct			AudioUnitCocoaViewInfo
	@abstract		The location and class name of one or more view factory objects an Audio Unit publishes
	@var  			mCocoaAUViewBundleLocation
						Contains the location of the bundle which the host app can then use to locate the bundle
	@var  			mCocoaAUViewClass
						Contains the names of the classes that implements the required protocol (AUCocoaUIBase). This class is a view factory that creates the NSView object that is the AudioUnit view.
*/
typedef struct AudioUnitCocoaViewInfo {
	CFURLRef	mCocoaAUViewBundleLocation;
	CFStringRef	__nonnull mCocoaAUViewClass[1];
} AudioUnitCocoaViewInfo;

/*!
	@struct			AUHostVersionIdentifier
	@abstract		Used to describe the name and version of the audio unit's host
*/
typedef struct AUHostVersionIdentifier {
	CFStringRef 		hostName;	
	UInt32				hostVersion;
} AUHostVersionIdentifier;
#endif //!TARGET_OS_IPHONE

/*!
	@struct			MIDIPacketList
	@abstract		Forward declaration of MIDIPacketList found in <CoreMIDI/MIDIServices.h>
*/
struct MIDIPacketList;

/*
	@typedef		AUMIDIOutputCallback
	@abstract		A callback used by an audio unit to provide MIDI data to a host application
*/
typedef OSStatus
(*AUMIDIOutputCallback)(void * __nullable				userData,
						const AudioTimeStamp *			timeStamp,
						UInt32							midiOutNum,
						const struct MIDIPacketList *	pktlist);

/*!
	@struct			AUMIDIOutputCallbackStruct
	@abstract		Set by host application to provide the callback and user data for an audio 
					unit that provides MIDI output
*/
typedef struct AUMIDIOutputCallbackStruct {
	AUMIDIOutputCallback	midiOutputCallback;
	void * __nullable		userData;
} AUMIDIOutputCallbackStruct;

/*!
	@struct			AUInputSamplesInOutputCallbackStruct
	@abstract		Used by a host when registering a callback with an audio unit, to provide 
					input-to-output samples mapping
*/
typedef struct AUInputSamplesInOutputCallbackStruct {
	AUInputSamplesInOutputCallback		inputToOutputCallback;
	void * __nullable					userData;
} AUInputSamplesInOutputCallbackStruct;


/*!
	@struct			AudioUnitParameterHistoryInfo
	@abstract		This structure contains the suggested update rate and history duration for parameters which have the kAudioUnitParameterFlag_PlotHistory flag set.
					The structure is filled out by getting kAudioUnitProperty_ParameterHistoryInfo.
	@var  			updatesPerSecond
						This is the number of times per second that it is suggested that the host get the value of this parameter.
	@var  			historyDurationInSeconds
						This is the duration in seconds of history that should be plotted.
*/
typedef struct AudioUnitParameterHistoryInfo
{
	Float32		updatesPerSecond;
	Float32		historyDurationInSeconds;
} AudioUnitParameterHistoryInfo;


//=====================================================================================================================
#pragma mark - Parameter Definitions

// assume kAudioUnitParameterUnit_Generic if not found in this enum
/*!
	@enum			AudioUnitParameterUnit
	@constant		kAudioUnitParameterUnit_Generic
						untyped value generally between 0.0 and 1.0
	@constant		kAudioUnitParameterUnit_Indexed
						takes an integer value (good for menu selections)
	@constant		kAudioUnitParameterUnit_Boolean
						0.0 means FALSE, non-zero means TRUE
	@constant		kAudioUnitParameterUnit_Percent
						usually from 0 -> 100, sometimes -50 -> +50
	@constant		kAudioUnitParameterUnit_Seconds
						absolute or relative time
	@constant		kAudioUnitParameterUnit_SampleFrames
						one sample frame equals (1.0/sampleRate) seconds
	@constant		kAudioUnitParameterUnit_Phase
						-180 to 180 degrees
	@constant		kAudioUnitParameterUnit_Rate
						rate multiplier, for playback speed, etc. (e.g. 2.0 == twice as fast)
	@constant		kAudioUnitParameterUnit_Hertz
						absolute frequency/pitch in cycles/second
	@constant		kAudioUnitParameterUnit_Cents
						unit of relative pitch
	@constant		kAudioUnitParameterUnit_RelativeSemiTones
						useful for coarse detuning
	@constant		kAudioUnitParameterUnit_MIDINoteNumber
						absolute pitch as defined in the MIDI spec (exact freq may depend on tuning table)
	@constant		kAudioUnitParameterUnit_MIDIController
						a generic MIDI controller value from 0 -> 127
	@constant		kAudioUnitParameterUnit_Decibels
						logarithmic relative gain
	@constant		kAudioUnitParameterUnit_LinearGain
						linear relative gain
	@constant		kAudioUnitParameterUnit_Degrees
						-180 to 180 degrees, similar to phase but more general (good for 3D coord system)
	@constant		kAudioUnitParameterUnit_EqualPowerCrossfade
						0 -> 100, crossfade mix two sources according to sqrt(x) and sqrt(1.0 - x)
	@constant		kAudioUnitParameterUnit_MixerFaderCurve1
						0.0 -> 1.0, pow(x, 3.0) -> linear gain to simulate a reasonable mixer channel fader response
	@constant		kAudioUnitParameterUnit_Pan
						standard left to right mixer pan
	@constant		kAudioUnitParameterUnit_Meters
						distance measured in meters
	@constant		kAudioUnitParameterUnit_AbsoluteCents
						absolute frequency measurement : 
						if f is freq in hertz then absoluteCents = 1200 * log2(f / 440) + 6900
	@constant		kAudioUnitParameterUnit_Octaves
						octaves in relative pitch where a value of 1 is equal to 1200 cents
	@constant		kAudioUnitParameterUnit_BPM
						beats per minute, ie tempo
    @constant		kAudioUnitParameterUnit_Beats
						time relative to tempo, i.e., 1.0 at 120 BPM would equal 1/2 a second
	@constant		kAudioUnitParameterUnit_Milliseconds
						parameter is expressed in milliseconds
	@constant		kAudioUnitParameterUnit_Ratio
						for compression, expansion ratio, etc.
	@constant		kAudioUnitParameterUnit_CustomUnit
						this is the parameter unit type for parameters that present a custom unit name
*/
typedef CF_ENUM(UInt32, AudioUnitParameterUnit)
{
	kAudioUnitParameterUnit_Generic				= 0,
	kAudioUnitParameterUnit_Indexed				= 1,
	kAudioUnitParameterUnit_Boolean				= 2,
	kAudioUnitParameterUnit_Percent				= 3,
	kAudioUnitParameterUnit_Seconds				= 4,
	kAudioUnitParameterUnit_SampleFrames		= 5,
	kAudioUnitParameterUnit_Phase				= 6,
	kAudioUnitParameterUnit_Rate				= 7,
	kAudioUnitParameterUnit_Hertz				= 8,
	kAudioUnitParameterUnit_Cents				= 9,
	kAudioUnitParameterUnit_RelativeSemiTones	= 10,
	kAudioUnitParameterUnit_MIDINoteNumber		= 11,
	kAudioUnitParameterUnit_MIDIController		= 12,
	kAudioUnitParameterUnit_Decibels			= 13,
	kAudioUnitParameterUnit_LinearGain			= 14,
	kAudioUnitParameterUnit_Degrees				= 15,
	kAudioUnitParameterUnit_EqualPowerCrossfade = 16,
	kAudioUnitParameterUnit_MixerFaderCurve1	= 17,
	kAudioUnitParameterUnit_Pan					= 18,
	kAudioUnitParameterUnit_Meters				= 19,
	kAudioUnitParameterUnit_AbsoluteCents		= 20,
	kAudioUnitParameterUnit_Octaves				= 21,
	kAudioUnitParameterUnit_BPM					= 22,
    kAudioUnitParameterUnit_Beats               = 23,
	kAudioUnitParameterUnit_Milliseconds		= 24,
	kAudioUnitParameterUnit_Ratio				= 25,
	kAudioUnitParameterUnit_CustomUnit			= 26
};

/*!
	@enum			AudioUnitParameterOptions
	@discussion		Bit positions 18, 17, and 16 are set aside for display scales. Bit 19 is reserved.
	@constant		kAudioUnitParameterFlag_CFNameRelease
	@constant		kAudioUnitParameterFlag_PlotHistory
	@constant		kAudioUnitParameterFlag_MeterReadOnly
	@constant		kAudioUnitParameterFlag_DisplayMask
	@constant		kAudioUnitParameterFlag_DisplaySquareRoot
	@constant		kAudioUnitParameterFlag_DisplaySquared
	@constant		kAudioUnitParameterFlag_DisplayCubed
	@constant		kAudioUnitParameterFlag_DisplayCubeRoot
	@constant		kAudioUnitParameterFlag_DisplayExponential
	@constant		kAudioUnitParameterFlag_HasClump
	@constant		kAudioUnitParameterFlag_ValuesHaveStrings
	@constant		kAudioUnitParameterFlag_DisplayLogarithmic		
	@constant		kAudioUnitParameterFlag_IsHighResolution
		This flag provides a hint to a host that this parameter should be controlled through the
		highest resolution if the host has limitations on the control resolution of parameter
		values. Generally this means that controlling this parameter with a single MIDI Control
		message (i.e. 128 values) is too course a grain for that parameter, and a finer control
		resolution should be used if possible. If this flag is not set, then a host can assume that
		a 7-bit control quantization is acceptable. Ideally, parameters should be controlled in the
		fullest resolution that they are published with.
	@constant		kAudioUnitParameterFlag_NonRealTime
		Changing the parameter in real-time will cause a glitch or otherwise undesirable effect.
	@constant		kAudioUnitParameterFlag_CanRamp
		If set, the parameter can be ramped.
	@constant		kAudioUnitParameterFlag_ExpertMode
		If set, the parameter is obscure (hint to UI to only display in expert mode).
	@constant		kAudioUnitParameterFlag_HasCFNameString
		In the original ParameterInfo a C string only was specified. With MacOS 10.2 and later, the
		last four bytes of this string are reserved for a CFStringRef, which gives the ability to
		used Unicode encoding, necessary for providing a name in languages using non-ASCII
		characters. If this flag bit is set, the CFStringRef is valid.
	@constant		kAudioUnitParameterFlag_IsGlobalMeta
		If set, changing this parameter may change any number of others in the AudioUnit.
	@constant		kAudioUnitParameterFlag_IsElementMeta
		If set, changing this parameter may change others in the same element as the current
		parameter.
	@constant		kAudioUnitParameterFlag_IsReadable
	@constant		kAudioUnitParameterFlag_IsWritable
*/
typedef CF_OPTIONS(UInt32, AudioUnitParameterOptions)
{
	kAudioUnitParameterFlag_CFNameRelease		= (1UL << 4),

	kAudioUnitParameterFlag_OmitFromPresets		= (1UL << 13),
	kAudioUnitParameterFlag_PlotHistory			= (1UL << 14),
	kAudioUnitParameterFlag_MeterReadOnly		= (1UL << 15),
	
	// bit positions 18,17,16 are set aside for display scales. bit 19 is reserved.
	kAudioUnitParameterFlag_DisplayMask			= (7UL << 16) | (1UL << 22),
	kAudioUnitParameterFlag_DisplaySquareRoot	= (1UL << 16),
	kAudioUnitParameterFlag_DisplaySquared		= (2UL << 16),
	kAudioUnitParameterFlag_DisplayCubed		= (3UL << 16),
	kAudioUnitParameterFlag_DisplayCubeRoot		= (4UL << 16),
	kAudioUnitParameterFlag_DisplayExponential	= (5UL << 16),

	kAudioUnitParameterFlag_HasClump	 		= (1UL << 20),
	kAudioUnitParameterFlag_ValuesHaveStrings	= (1UL << 21),
	
	kAudioUnitParameterFlag_DisplayLogarithmic 	= (1UL << 22),
	
	kAudioUnitParameterFlag_IsHighResolution 	= (1UL << 23),
	kAudioUnitParameterFlag_NonRealTime 		= (1UL << 24),
	kAudioUnitParameterFlag_CanRamp 			= (1UL << 25),
	kAudioUnitParameterFlag_ExpertMode 			= (1UL << 26),
	kAudioUnitParameterFlag_HasCFNameString 	= (1UL << 27),
	kAudioUnitParameterFlag_IsGlobalMeta 		= (1UL << 28),
	kAudioUnitParameterFlag_IsElementMeta		= (1UL << 29),
	kAudioUnitParameterFlag_IsReadable			= (1UL << 30),
	kAudioUnitParameterFlag_IsWritable			= (1UL << 31)
};

/*!
	@struct			AudioUnitParameterInfo
	@var  			name
						UNUSED - set to zero - UTF8 encoded C string (originally). 
	@var  			unitName
						only valid if kAudioUnitParameterUnit_CustomUnit is set. If kAudioUnitParameterUnit_CustomUnit
						is set, this field must contain a valid CFString.
	@var  			clumpID
						only valid if kAudioUnitParameterFlag_HasClump
	@var  			cfNameString
						only valid if kAudioUnitParameterFlag_HasCFNameString
	@var  			unit				
						if the "unit" field contains a value not in the enum above, then assume 
						kAudioUnitParameterUnit_Generic
	@var  			minValue
	@var  			maxValue
	@var  			defaultValue
	@var  			flags
						Due to some vagaries about the ways in which Parameter's CFNames have been described, it was
						necessary to add a flag: kAudioUnitParameterFlag_CFNameRelease
						In normal usage a parameter name is essentially a static object, but sometimes an audio unit will 
						generate parameter names dynamically.. As these are expected to be CFStrings, in that case
						the host should release those names when it is finished with them, but there was no way
						to communicate this distinction in behavior.
						Thus, if an audio unit will (or could) generate a name dynamically, it should set this flag in 
						the parameter's info. The host should check for this flag, and if present, release the parameter
						name when it is finished with it.
*/
typedef struct AudioUnitParameterInfo
{
	char						name[52];
	CFStringRef __nullable		unitName;
	UInt32						clumpID;
	CFStringRef __nullable		cfNameString;
	AudioUnitParameterUnit		unit;
	AudioUnitParameterValue		minValue;
	AudioUnitParameterValue		maxValue;
	AudioUnitParameterValue		defaultValue;
	AudioUnitParameterOptions	flags;
} AudioUnitParameterInfo;

/*!
	@enum			Audio Unit Clump ID
	@discussion		Audio unit developers should not use a clump ID of 0. This value is reserved for system use.
*/
enum {
	kAudioUnitClumpID_System = 0
};

#ifdef CF_INLINE

CF_INLINE AudioUnitParameterOptions GetAudioUnitParameterDisplayType(AudioUnitParameterOptions flags)
{
	return flags & kAudioUnitParameterFlag_DisplayMask;
}

CF_INLINE AudioUnitParameterOptions SetAudioUnitParameterDisplayType(AudioUnitParameterOptions flags, AudioUnitParameterOptions displayType)
{
	return (flags & ~kAudioUnitParameterFlag_DisplayMask) | displayType;
}

#else

/*! @define GetAudioUnitParameterDisplayType */
#define GetAudioUnitParameterDisplayType(flags) \
	((flags) & kAudioUnitParameterFlag_DisplayMask)

/*! @define SetAudioUnitParameterDisplayType */
#define SetAudioUnitParameterDisplayType(flags, displayType) \
	(((flags) & ~kAudioUnitParameterFlag_DisplayMask) | (displayType))

#endif // CF_INLINE

/*! @define AudioUnitDisplayTypeIsLogarithmic */
#define AudioUnitDisplayTypeIsLogarithmic(flags) \
	(GetAudioUnitParameterDisplayType(flags) == kAudioUnitParameterFlag_DisplayLogarithmic)
	
/*! @define AudioUnitDisplayTypeIsSquareRoot */
#define AudioUnitDisplayTypeIsSquareRoot(flags) \
	(GetAudioUnitParameterDisplayType(flags) == kAudioUnitParameterFlag_DisplaySquareRoot)
	
/*! @define AudioUnitDisplayTypeIsSquared */
#define AudioUnitDisplayTypeIsSquared(flags) \
	(GetAudioUnitParameterDisplayType(flags) == kAudioUnitParameterFlag_DisplaySquared)
	
/*! @define AudioUnitDisplayTypeIsCubed */
#define AudioUnitDisplayTypeIsCubed(flags) \
	(GetAudioUnitParameterDisplayType(flags) == kAudioUnitParameterFlag_DisplayCubed)

/*! @define AudioUnitDisplayTypeIsCubeRoot */
#define AudioUnitDisplayTypeIsCubeRoot(flags) \
	(GetAudioUnitParameterDisplayType(flags) == kAudioUnitParameterFlag_DisplayCubeRoot)

/*! @define AudioUnitDisplayTypeIsExponential */
#define AudioUnitDisplayTypeIsExponential(flags) \
	(GetAudioUnitParameterDisplayType(flags) == kAudioUnitParameterFlag_DisplayExponential)

/*
	The following properties are used with display names
*/

/*!
	@enum			Audio Unit Parameter Full Name
	@discussion		Used with the AudioUnitParameterIDName.inDesiredLength field to indicate the full name
					of the requested parameter.
*/
enum {
	kAudioUnitParameterName_Full = -1
};

/*!
	@struct			AudioUnitParameterIDName
	@abstract		Used to provide shorter names for a specified parameter
*/
typedef struct AudioUnitParameterNameInfo {
	AudioUnitParameterID	inID;
	SInt32					inDesiredLength;
	CFStringRef __nullable	outName;
} AudioUnitParameterIDName;

/*!
	@struct			AudioUnitParameterStringFromValue
	@abstract		Provide a string representation of a parameter's value
*/
typedef struct AudioUnitParameterStringFromValue {
	AudioUnitParameterID				inParamID;
	const AudioUnitParameterValue *		inValue;	
	CFStringRef __nullable				outString;
} AudioUnitParameterStringFromValue;

/*!
	@struct			AudioUnitParameterValueFromString
	@abstract		Provide the parameter's value for a given string representation of it
*/
typedef struct AudioUnitParameterValueFromString {
	AudioUnitParameterID		inParamID;
	CFStringRef					inString;
	AudioUnitParameterValue		outValue;
} AudioUnitParameterValueFromString;


#if AU_SUPPORT_INTERAPP_AUDIO
/*!
	@enum			AudioUnitRemoteControlEvent
	@abstract		In inter-app audio, messages to control the host's transport state.
*/
typedef CF_ENUM(UInt32, AudioUnitRemoteControlEvent) {
	kAudioUnitRemoteControlEvent_TogglePlayPause	= 1,
	kAudioUnitRemoteControlEvent_ToggleRecord		= 2,
	kAudioUnitRemoteControlEvent_Rewind				= 3
};

/*!	@typedef		AudioUnitRemoteControlEventListener
	@abstract		Block called to receive a remote control event.
*/
typedef void (^AudioUnitRemoteControlEventListener)(AudioUnitRemoteControlEvent event);
#endif // AU_SUPPORT_INTERAPP_AUDIO

//=====================================================================================================================
#pragma mark - Configuration Info Keys

//	These strings are used as keys to the dictionary of configuration info returned by
//	AudioComponentGetConfigurationInfo(). Information about them is presented inline with the
//	declaration.

/*!
	@define		kAudioUnitConfigurationInfo_HasCustomView
	@discussion	This is a boolean value that indicates whether or not the AU has a custom view
*/
#define kAudioUnitConfigurationInfo_HasCustomView	"HasCustomView"

/*!
	@define		kAudioUnitConfigurationInfo_ChannelConfigurations
	@discussion	This is an array of pairs of values where each item in the array is an array of two
				numbers and is the equivalent of an AUChannelInfo. If the AudioUnit is an effect and
				it doesn't implement kAudioUnitProperty_SupportedNumChannels, the array will contain
				only the single entry, { -1, -1}. If the AudioUnit is an instrument or a generator
				and doesn't implement kAudioUnitProperty_SupportedNumChannels, the array will be
				empty and means that the AU's initial state is all that is supported.
*/
#define kAudioUnitConfigurationInfo_ChannelConfigurations	"ChannelConfigurations"

/*!
	@define		kAudioUnitConfigurationInfo_InitialInputs
	@discussion	An array of numbers whose size is equal to the number of input buses posessed by the
				AU. Each number in the array represents the number of channels for the corresponding
				bus.
*/
#define kAudioUnitConfigurationInfo_InitialInputs	"InitialInputs"

/*!
	@define		kAudioUnitConfigurationInfo_InitialOutputs
	@discussion	An array of numbers whose size is equal to the number of output buses posessed by
				the AU. Each number in the array represents the number of channels for the
				corresponding bus.
*/
#define kAudioUnitConfigurationInfo_InitialOutputs	"InitialOutputs"

/*!
 @define		kAudioUnitConfigurationInfo_IconURL
 @discussion	A CFURLRef value that indicates the location of an icon of the audio unit.
 */
#define kAudioUnitConfigurationInfo_IconURL			"IconURL"

/*!
 @define		kAudioUnitConfigurationInfo_BusCountWritable
 @discussion	An array of booleans whose size is three representing Global, Input and Output scope
				in the order it is defined in CoreAudioTypes.h. Each value represents whether the bus
				count is writable for the specified scope.
 */
#define kAudioUnitConfigurationInfo_BusCountWritable	"BusCountWritable"

/*!
 @define		kAudioUnitConfigurationInfo_SupportedChannelLayoutTags
 @discussion	A dictionary that contains two arrays one for input scope and output scope. Each array
				of numbers whose size is equal to number of supported channel layout tags supported for the scope
				by the AU. Each number in the array represents the channel layout tag.
 */

#define kAudioUnitConfigurationInfo_SupportedChannelLayoutTags	"SupportedChannelLayoutTags"

//=====================================================================================================================
#pragma mark - Output Unit
/*!
    @enum           Output Unit Properties
    @abstract       The collection of properties for output units
	@constant		kAudioOutputUnitProperty_IsRunning
	@discussion			Scope:
						Value Type:
						Access:
*/
CF_ENUM(AudioUnitPropertyID) {
// range  (2000 -> 2999)
	kAudioOutputUnitProperty_IsRunning				= 2001
};

#pragma mark -
#pragma mark OS X Availability

#if !TARGET_OS_IPHONE

//=====================================================================================================================
#pragma mark - Music Effects and Instruments
/*!
    @enum           Music Effect and Instrument Unit (MusicDevice) Properties
    @abstract       The collection of Music Effects and Instrument Unit Property IDs
	@discussion
		These properties are used to:
			Describe a current set of mappings between MIDI messages and Parameter value setting
			Create a mapping between a parameter and a MIDI message through either:
				- explicitly adding (or removing) the mapping
				- telling the audio unit to hot-map the next MIDI message to a specified Parameter
			The same MIDI Message can map to one or more parameters
			
		These properties normally apply only to the two types of audio units that implement 
		the MIDI API, instrument units ('aumu') and music effects ('aumf').

		These properties are used in the Global scope. The scope and element members of the structure describe
		the scope and element of the parameter. In all usages, mScope, mElement and mParameterID must be
		correctly specified.

		
		* The AUParameterMIDIMapping Structure

		Command				mStatus			mData1			
		Note Off			0x8n			Note Num		
		Note On				0x9n			Note Num		
		Key Pressure		0xAn			Note Num		
		Control Change		0xBn			ControllerID	
		Patch Change		0xCn			Patch Num		
		Channel Pressure	DxDn			0 (Unused)		
		Pitch Bend			0xEn			0 (Unused)		
		
		(where n is 0-0xF to correspond to MIDI channels 1-16)
		
		Details:

		In general MIDI Commands can be mapped to either a specific channel as specified in the mStatus bit.
		If the kAUParameterMIDIMapping_AnyChannelFlag bit is set mStatus is a MIDI channel message, then the 
		MIDI channel number in the status byte is ignored; the mapping is from the specified MIDI message on ANY channel.
		
		For note commands (note on, note off, key pressure), the MIDI message can trigger either with just a specific
		note number, or any note number if the kAUParameterMIDIMapping_AnyNoteFlag bit is set. In these instances, the
		note number is used as the trigger value (for instance, a note message could be used to set the 
		cut off frequency of a filter).
		
		When the parameter mapping list changes through addition/replace, removal, the implementation should
		fire a notification on the kAudioUnitProperty_AllParameterMIDIMappings property. The host can then
		retrieve the full set of mappings for the audio unit.
		
		When a hot mapping is made, the notification should just be delivered for the HotMap property. The host can
		retrieve the last current hot mapping made through getting the value of that property.
	
	@constant		kAudioUnitProperty_AllParameterMIDIMappings
	@discussion			Scope:				any
						Value Type:			array of AUParameterMIDIMapping
						Access:				read/write

						This property allows setting and retrieving the current mapping state between 
						(some/many/all of) an audio unit's parameters and MIDI messages. When set, it should replace 
						any previous mapped settings the audio unit had.
					
						If this property is implemented by a non-MIDI capable audio unit (such as an 'aufx' type), 
						then the property is read only and should recommend a suggested set of mappings for the host 
						to perform. In this case, it is the host's responsibility to map MIDI message to the audio 
						unit parameters.
						
						This property's size varies depending on the number of mappings currently in effect. A host 
						application should always get the size of this property before retrieving it. The audio
						unit should return an error if the host doesn't provide enough space to return all of the 
						current mappings.
	
	@constant		kAudioUnitProperty_AddParameterMIDIMapping
	@discussion			Scope:				any
						Value Type:			array of AUParameterMIDIMapping
						Access:				write
						
						Use this property to add parameter-to-MIDI mappings to an audio unit's existing set of 
						mappings. There can be only one mapping per parameter. When you set a mapping for a parameter, 
						it replaces the previous mapping.
	
	@constant		kAudioUnitProperty_RemoveParameterMIDIMapping
	@discussion			Scope:				any
						Value Type:			array of AUParameterMIDIMapping
						Access:				write

						Use this property to remove mappings from an audio unit. If a mapping is specified that
						does not currently exist in an audio unit, then the audio unit should ignore the request. 
						The Scope/Element/ParameterID is used to find the mapping to remove.

	@constant		kAudioUnitProperty_HotMapParameterMIDIMapping
	@discussion			Scope:				any
						Value Type:			AUParameterMIDIMapping
						Access:				read/write

						This property can be used in two ways, determined by the value supplied by the host 
						application.
						
						(1) If a mapping structure is provided, then that structure provides all the information 
						that the audio unit should use to map the parameter, except for the MIDI message. The audio 
						unit should then listen for the next MIDI message and associate that MIDI message with the 
						supplied parameter mapping. When this MIDI message is received and the mapping made, the 
						audio unit should also issue a notification on this property to indicate to the host that 
						the mapping has been made. The host can then retrieve the mapping that was made by getting the 
						value of this property.
						
						To avoid possible confusion, it is recommended that once the host has retrieved this mapping 
						(if it is presenting a user interface to describe the mappings, for example), that the host
						should then clear the mapping state, as described in (2).
						
						The only time this property will return a valid value is when an audio unit has implemented the 
						requested mapping. If the audio unit's mapping state has been cleared (or if it has not been 
						asked to make a mapping), then the audio unit should return a kAudioUnitErr_InvalidPropertyValue 
						error when the host tries to read this property's value.
						
						(2) If the value passed in this property is NULL, and if the audio unit had a parameter that 
						it was in the process of mapping, the audio unit should disregard the parameter mapping request 
						and discard the partially mapped structure. If the value is NULL and the audio unit is not in 
						the process of mapping, the audio unit can just ignore the request.
						
						At all times, the _AllMappings property will completely describe the current known state of an 
						audio unit's mappings of MIDI messages to parameters.		
*/
CF_ENUM(AudioUnitPropertyID) {
	kAudioUnitProperty_AllParameterMIDIMappings		= 41,
	kAudioUnitProperty_AddParameterMIDIMapping		= 42,
	kAudioUnitProperty_RemoveParameterMIDIMapping   = 43,
	kAudioUnitProperty_HotMapParameterMIDIMapping   = 44
};
	
/*!
	@enum			ParameterMIDIMappings
	@abstract		General defined values to customize the behavior of parameter-to-MIDI mappings

	@constant		kAUParameterMIDIMapping_AnyChannelFlag
	@discussion			If this flag is set and the value of the mStatus field is a MIDI channel message, then 
						the MIDI channel number in the status byte is ignored; the mapping is from the specified 
						MIDI message on any channel.
	
	@constant		kAUParameterMIDIMapping_AnyNoteFlag
	@discussion			If this flag is set and the value of the mStatus field is a Note On, Note Off, or 
						Polyphonic Pressure message, the message's note number is ignored. The mapping is from 
						any note number.
	
	@constant		kAUParameterMIDIMapping_SubRange
	@discussion			Set this flag if the MIDI control should map only to a sub-range of the parameter's value.
						Then specify that range in the mSubRangeMin and mSubRangeMax member fields.
						
	@constant		kAUParameterMIDIMapping_Toggle
	@discussion			Intended for Boolean typed parameters. When this property is set, it means that the 
						parameter's value should be toggled when the mapped MIDI message is received. For example,
						if the parameter's value is currently TRUE, when the mapped MIDI message is received
						the value changes to FALSE. 

	@constant		kAUParameterMIDIMapping_Bipolar
	@discussion			This property is useful when mapping a parameter to a MIDI Controller. When set, it 
						indicates that the parameter can assume only two values: on or off. For this reason, a 
						parameter associated with this property is typically Boolean. For example, if this 
						property is set for a parameter mapped to a sustain pedal MIDI controller, controller 
						values from 0 to 64 result in the parameter switched to its "off" state; controller
						values from 65 to 127 result in the parameter switched to its "on" state.
						
						This property works in connection with the kAUParameterMIDIMapping_Bipolar_On property.
						The value of the kAUParameterMIDIMapping_Bipolar_On property 

	@constant		kAUParameterMIDIMapping_Bipolar_On
	@discussion			Determines whether the  "on" state of a parameter is mapped to the "on" or "off" state 
						of the associated MIDI controller. Only valid  if the  kAUParameterMIDIMapping_Bipolar 
						property is set.
*/
typedef CF_OPTIONS(UInt32, AUParameterMIDIMappingFlags) {
	kAUParameterMIDIMapping_AnyChannelFlag		= (1L << 0),
	kAUParameterMIDIMapping_AnyNoteFlag			= (1L << 1),
	kAUParameterMIDIMapping_SubRange			= (1L << 2),
	kAUParameterMIDIMapping_Toggle				= (1L << 3),	
	kAUParameterMIDIMapping_Bipolar				= (1L << 4),
	kAUParameterMIDIMapping_Bipolar_On			= (1L << 5)
};

/*!
	@struct			AUParameterMIDIMapping
	@abstract		Represents a mapping between a MIDI message and an audio unit's parameter.
	@discussion		The reserved fields in this structure are for future use. In the current implementation, 
					they help align the structure to 64 bit size. Do not use the names of these fields in a 
					host application. They are subject to change.
*/
typedef struct AUParameterMIDIMapping
{
	AudioUnitScope				mScope;
	AudioUnitElement			mElement;
	AudioUnitParameterID		mParameterID;
	AUParameterMIDIMappingFlags	mFlags;
	AudioUnitParameterValue		mSubRangeMin;
	AudioUnitParameterValue		mSubRangeMax;
	UInt8						mStatus;
	UInt8						mData1;
	UInt8						reserved1; // MUST be set to zero
	UInt8						reserved2; // MUST be set to zero
	UInt32						reserved3; // MUST be set to zero
} AUParameterMIDIMapping;



//=====================================================================================================================
#pragma mark - Music Device
/*!
    @enum           Instrument Unit (MusicDevice) Properties
    @abstract       The collection of Instrument Unit Property IDs

	@constant		kMusicDeviceProperty_MIDIXMLNames
	@discussion			Scope:
						Value Type:
						Access:

	@constant		kMusicDeviceProperty_PartGroup
	@discussion			Scope:				Part
						Value Type:			AudioUnitElement
						Access:				read/write

						This property's value specifies the group ID (the Group scope's element) 
						that the part is (or should be) assigned to. The property is used in the Part scope, 
						where the element ID is the part that is being queried (or assigned).
						
						This property may be implemented in an audio unit as read only, as writeable only if the 
						audio unit is uninitialized, or as read/write. Apple recommends that it should be 
						writable at any time.
						
						The effect of assigning a new group to a part is undefined. Typically, however, it can be 
						expected that all existing notes would be turned off before the re-assignment is made by 
						the audio unit.

	@constant		kMusicDeviceProperty_DualSchedulingMode
	@discussion			Scope:				Global
						Value Type:			UInt32
						Access:				write

						Some instrument units need to distinguish realtime note and control events (such as from 
						incoming MIDI) from sequenced or pre-scheduled events. To support this, a host application 
						may set this property to 1. If the instrument unit returns a value of noErr, it supports 
						an alternate interpretation of the inOffsetSampleFrame parameter for the following 
						functions:

							MusicDeviceMIDIEvent
							MusicDeviceStartNote
							MusicDeviceStopNote
							AudioUnitSetParameter

						Once the host sets this property to 1 and the instrument unit returns noErr, the 
						inOffsetSampleFrame field becomes a bitfield:

							kMusicDeviceSampleFrameMask_SampleOffset = 0xFFFFFF // AND with this to obtain sample offset
							kMusicDeviceSampleFrameMask_IsScheduled = 0x01000000

						The IsScheduled bit should be set on events which are being scheduled ahead of time from 
						a prerecorded track. The IsScheduled bit should be clear on events which are being sent 
						to the instrument unit in response to realtime events, such as incoming MIDI or control 
						changes in a view.

	@constant		kMusicDeviceProperty_SupportsStartStopNote
	@discussion			Scope:				Global
						Value Type:			UInt32
						Access:				read
						
						The MusicDeviceStartNote and MusicDeviceStopNote APIs have been available since Mac OS X v10.0. 
						However, many third-party audio units do not implement these calls. This property can
						be used to determine if an audio unit does provide a compliant implementation. A compliant
						audio unit will both implement the property and return !0 as the value for the property. 
						Apple's DLSMusicDevice unit has implemented MusicDeviceStartNote and MusicDeviceStopNote
						since Mac OS X v10.0. The kMusicDeviceProperty_SupportsStartStopNote property was introduced
						with Mac OS X v10.5, so the DLSMusicDevice unit will not return an appropriate value for
						this property on a pre-10.5 system.
						
*/	
CF_ENUM(AudioUnitPropertyID) {
// range  (1000 -> 1999)
	kMusicDeviceProperty_MIDIXMLNames				= 1006,
	kMusicDeviceProperty_PartGroup					= 1010,
	kMusicDeviceProperty_DualSchedulingMode			= 1013,
	kMusicDeviceProperty_SupportsStartStopNote		= 1014
};

/*!
    @enum			DualSchedulingMode
 */
enum {
	kMusicDeviceSampleFrameMask_SampleOffset = 0xFFFFFF, // AND with this to obtain the sample offset
	kMusicDeviceSampleFrameMask_IsScheduled = 0x01000000
};


//=====================================================================================================================
#pragma mark - Offline Unit
/*!
    @enum           Offline Unit Properties
    @abstract       The collection of properties for offline units 
	@constant		kAudioUnitOfflineProperty_InputSize
	@discussion			Scope:			Global
						Value Type:		UInt64
						Access:			read/write

						Once this property is set, an audio unit will assume that its input samples 
						have been reset to a new region. Setting this property will also cause the 
						audio unit's internal DSP state to be reset. That is, the audio unit calls 
						the AudioUnitReset function on itself.
						
						This property tells the offline unit how many samples to process. Once it 
						knows this number it will then request from 0 to (nSamples-1) in its input
						callback. The host of the audio unit is then required to provide the samples 
						specified in the sample count field of that Input's callback.

	@constant		kAudioUnitOfflineProperty_OutputSize
	@discussion			Scope:			Global
						Value Type:		UInt64
						Access:			read
						
						The host can use this property to estimate how many output samples an audio 
						unit will produce for the specified input samples. The property value
						is invalid if InputSize is not set. 
						
						The host cannot assume that the value returned is exact.
						It is a guide only, so is suitable for use in a progress bar, for instance.
						
						Termination of processing is solely determined by the setting of the 
						kAudioUnitStatus_OfflineRenderComplete property in the 
						ioRenderActionFlags from the AudioUnitRender function.

	@constant		kAudioUnitOfflineProperty_StartOffset
	@discussion			Scope:			Global
						Value Type:		UInt64
						Access:			read/write

						The host sets this property to tell an audio unit that the start offset of 
						the data it is processing has been changed. This should be set along with 
						the InputSize property, so that the unit knows its input data has been set 
						or changed.

	@constant		kAudioUnitOfflineProperty_PreflightRequirements
	@discussion			Scope:			Global
						Value Type:		UInt32
						Access:			read

						Returns one of the kOfflinePreflight_ results (see the Offline Preflight 
						enumeration).
						
	@constant		kAudioUnitOfflineProperty_PreflightName
	@discussion			Scope:			Global
						Value Type:		CFStringRef
						Access:			read

						For an audio unit that allows or requires preflighting, this property lets
						the unit give its host application a name to describe the preflight 
						operations.
*/
CF_ENUM(AudioUnitPropertyID) {
// range (3020->3040)
	kAudioUnitOfflineProperty_InputSize				= 3020,
	kAudioUnitOfflineProperty_OutputSize			= 3021,
	kAudioUnitOfflineProperty_StartOffset			= 3022,
	kAudioUnitOfflineProperty_PreflightRequirements	= 3023,
	kAudioUnitOfflineProperty_PreflightName			= 3024
};

/*!
	@enum		Offline Preflight Flags
	@abstract	Used to indicate an Offline Unit's preflight requirements
	@constant	kOfflinePreflight_NotRequired
	@discussion		Offline unit does not require preflight
	@constant	kOfflinePreflight_Optional
	@discussion		Offline unit will generally behave better if it is preflighted, but it is not
					required to be preflighted.
	@constant	kOfflinePreflight_Required
	@discussion		Offline unit requires preflighting or it cannot do its work

*/
enum {
	kOfflinePreflight_NotRequired 	= 0,
	kOfflinePreflight_Optional		= 1,
	kOfflinePreflight_Required		= 2
};

//=====================================================================================================================
#pragma mark - Panner Unit
/*!
    @enum           Panner Unit Properties
    @abstract       The collection of properties for panner units
	@constant		kAudioUnitProperty_DistanceAttenuationData
	@discussion		This property is deprecated.
						Scope:			Global
						Value Type:		AUDistanceAttenuationData
						Access:			Read
 
*/
CF_ENUM(AudioUnitPropertyID) {
// range (3060->3999)
	kAudioUnitProperty_DistanceAttenuationData      = 3600
} API_DEPRECATED("no longer supported", macos(10.5, 10.11)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
	@struct			AUDistanceAttenuationData
*/
typedef struct AUDistanceAttenuationData
{
	UInt32	 inNumberOfPairs;
	struct {
		Float32	inDistance;	// 0-1000
		Float32 outGain;	// 0-1
	} pairs[1]; // this is a variable length array of inNumberOfPairs elements
} AUDistanceAttenuationData API_DEPRECATED("no longer supported", macos(10.5, 10.11)) API_UNAVAILABLE(ios, watchos, tvos);


//=====================================================================================================================
#pragma mark - Translation Service
/*!
    @enum           Translation Properties
    @abstract       The collection of properties for migrating data from other audio plug-ins to the 
    				Audio Unit architecture
	@discussion		While this is a general service, there are two formats that are explicitly defined: 
					MAS and VST. An audio unit may have MAS settings given to it in one of two ways:

						(1) The settings may have a single setting. This may be set multiple times with 
						different settings each time. In this case, numberOfSettings will be 1.

						(2) The settings may be set in one hit, providing all SettingData at once. 
						In this case, numberOfSettings may be more than 1, and will be the number of 
						settings the host has from the MAS plugin.

						AU-VST - the CFDataRef data contains VST chunk data with no additional information. 

					In addition, this can be used to migrate settings from an older audio unit; this allows manufacturers 
					to deprecate older audio units and replace them with new ones. The data for the older audio unit is 
					the audio unit preset CFDictionary that that unit generated.

	@constant		kAudioUnitMigrateProperty_FromPlugin
	@discussion			Scope:
						Value Type:
						Access:

	@constant		kAudioUnitMigrateProperty_OldAutomation
	@discussion			Scope:
						Value Type:
						Access:
*/
CF_ENUM(AudioUnitPropertyID) {
// range (4000->4020)
 	kAudioUnitMigrateProperty_FromPlugin			= 4000,
	kAudioUnitMigrateProperty_OldAutomation			= 4001
};

/*!
	@enum			Other Plug-in Formats
*/
CF_ENUM(UInt32) {
	kOtherPluginFormat_Undefined	= 0, //reserving this value for future use
	kOtherPluginFormat_kMAS			= 1,
	kOtherPluginFormat_kVST			= 2,
	kOtherPluginFormat_AU			= 3
};

/*!
	@struct			AudioUnitOtherPluginDesc

	@var			format
					One of the OtherPluginFormat values
						
	@var			plugin
						struct AudioClassDescription {
							OSType mType;
							OSType mSubType;
							OSType mManufacturer;
						};
						is defined in <CoreAudioTypes/CoreAudioTypes.h>

					mType specifies a generic, plug-in format defined descriptor
							mSubType is usually left to the manufacturer to use at their discretion
							mManufacturer is a registered code to identify all plugins from the same manufacturer

*/
typedef struct  AudioUnitOtherPluginDesc
{
	UInt32 						format;
	AudioClassDescription		plugin;
} AudioUnitOtherPluginDesc;

/*!
	@struct			AudioUnitParameterValueTranslation
	@abstract		Used to translate another plug-in's parameter values to  audio unit parameter 
					values
*/
typedef struct AudioUnitParameterValueTranslation 
{
	AudioUnitOtherPluginDesc	otherDesc;
	UInt32						otherParamID;
	Float32						otherValue;
	AudioUnitParameterID		auParamID;
	AudioUnitParameterValue		auValue;
} AudioUnitParameterValueTranslation;

/*!
	@struct			AudioUnitPresetMAS_SettingData
	@discussion		AU-MAS specific structs for the data contained in the "masdata" key of an audio 
					unit preset dictionary
*/
typedef struct AudioUnitPresetMAS_SettingData
{
	UInt32 				isStockSetting; // zero or 1  i.e., "long bool"
	UInt32 				settingID;
	UInt32 				dataLen; //length of following data
	UInt8 				data[1];
} AudioUnitPresetMAS_SettingData;

/*!
	@struct			AudioUnitPresetMAS_Settings
	@discussion		See MAS documentation
*/
typedef struct AudioUnitPresetMAS_Settings
{
	UInt32 							manufacturerID;
	UInt32 							effectID;
	UInt32 							variantID;
	UInt32 							settingsVersion;
	UInt32 							numberOfSettings;
	AudioUnitPresetMAS_SettingData 	settings[1];
} AudioUnitPresetMAS_Settings;

#endif // !TARGET_OS_IPHONE

//=====================================================================================================================
#pragma mark -
#pragma mark Apple Specific Properties

//=====================================================================================================================
#pragma mark - AUConverter
/*!
    @enum           Apple AUConverter Property IDs
    @abstract       The collection of property IDs for Apple AUConverter
	
	@constant		kAudioUnitProperty_SampleRateConverterComplexity
	@discussion			Scope:			Global
						Value Type:		UInt32
						Access:			read/write
*/
CF_ENUM(AudioUnitPropertyID) {
	kAudioUnitProperty_SampleRateConverterComplexity	= 3014
};

/*!
	@enum			Audio Unit Sample Rate Converter Complexity
	@discussion		The lowest quality of the Mastering algorithm is higher than the highest quality of the Normal algorithm.
	@constant		kAudioUnitSampleRateConverterComplexity_Normal
	@discussion			Normal quality sample rate conversion.
	@constant		kAudioUnitSampleRateConverterComplexity_Mastering
	@discussion			Mastering quality sample rate conversion. More expensive.
*/
CF_ENUM(UInt32) {
	kAudioUnitSampleRateConverterComplexity_Linear				= 'line',	// linear interpolation
	kAudioUnitSampleRateConverterComplexity_Normal				= 'norm',	// the default
	kAudioUnitSampleRateConverterComplexity_Mastering			= 'bats'	// higher quality, more expensive
};

//=====================================================================================================================
#pragma mark - AUHAL and device units
/*!
    @enum           Apple Output Property IDs
    @abstract       The collection of property IDs for Apple output units
	
	@constant		kAudioOutputUnitProperty_CurrentDevice
	@discussion			Scope:			Global
						Value Type:		AudioObjectID
						Access:			read/write
						
						The audio device being used (or to be used) by and output device unit
						
	@constant		kAudioOutputUnitProperty_ChannelMap
	@discussion			Scope:			Input/Output
						Value Type:		Array of SInt32
						Access:			Read / Write

						This will also work with AUConverter. This property is used to map input channels from an input (source) to a destination.
						The number of channels represented in the channel map is the number of channels of the destination. The channel map entries
						contain a channel number of the source that should be mapped to that destination channel. If -1 is specified, then that 
						destination channel will not contain any channel from the source (so it will be silent)
						
	@constant		kAudioOutputUnitProperty_EnableIO
	@discussion			Scope: { scope output, element 0 = output } { scope input, element 1 = input }
						Value Type: UInt32
						Access: read/write
							Output units default to output-only operation. Host applications may disable 
							output or enable input operation using this property, if the output unit 
							supports it. 0=disabled, 1=enabled using I/O proc.

	@constant		kAudioOutputUnitProperty_StartTime
	@discussion			Scope: Global
						Value Type: AudioOutputUnitStartAtTimeParams
						Access: write only
							When this property is set on an output unit, it will cause the next Start request
							(but no subsequent Starts) to use AudioDeviceStartAtTime, using the specified 
							timestamp, passing false for inRequestedStartTimeIsInput.

	@constant		kAudioOutputUnitProperty_SetInputCallback
	@discussion			Scope: Global
						Value Type: AURenderCallbackStruct
						Access: read/write
							When an output unit has been enabled for input operation, this callback can be 
							used to provide a single callback to the host application from the input 
							I/O proc, in order to notify the host that input is available and may be 
							obtained by calling the AudioUnitRender function.
							
							Note that the inputProc will always receive a NULL AudioBufferList in ioData.
							You must call AudioUnitRender in order to obtain the audio.

	@constant		kAudioOutputUnitProperty_HasIO
	@discussion			Scope: { scope output, element 0 = output } { scope input, element 1 = input }
						Value Type: UInt32
						Access:
							See kAudioOutputUnitProperty_EnableIO
							Property value is 1 if there are any valid hardware streams on the specified element.

	@constant		kAudioOutputUnitProperty_StartTimestampsAtZero
	@discussion			Scope: Global
						Value Type: UInt32
						Access: read/write

							Apple output units typically begin their stream of timestamps presented to their
							inputs at sample time 0. Some applications may wish to receive the HAL's timestamps
							directly instead. When this property is set to false, the output unit's sample times
							will be direct reflections of the HAL's -- except when a sample rate conversion
							makes this impossible.
							
							This property also applies to AUConverter. Its value defaults to 1 for AUHAL;
							1 for other AUs.
*/
CF_ENUM(AudioUnitPropertyID) {
	kAudioOutputUnitProperty_CurrentDevice			= 2000,
	kAudioOutputUnitProperty_ChannelMap				= 2002, // this will also work with AUConverter
	kAudioOutputUnitProperty_EnableIO				= 2003,
	kAudioOutputUnitProperty_StartTime				= 2004,
	kAudioOutputUnitProperty_SetInputCallback		= 2005,
	kAudioOutputUnitProperty_HasIO					= 2006,
	kAudioOutputUnitProperty_StartTimestampsAtZero  = 2007	// this will also work with AUConverter
};

#if AU_SUPPORT_INTERAPP_AUDIO
/*!
    @enum           Apple Inter-App Output Property IDs
    @abstract       The collection of property IDs for Apple output units with inter-app audio on iOS.
	
	@constant		kAudioOutputUnitProperty_MIDICallbacks
	@discussion			Scope: Global
						Value Type: AudioOutputUnitMIDICallbacks
						Access: read/write

					When an output unit is published as a remote instrument or music effect, this
					property must be set on the unit in order to receive MIDI events from the
					host. The specified callbacks will be called at render time, immediately
					prior to the request to render a buffer.

	@constant		kAudioOutputUnitProperty_HostReceivesRemoteControlEvents
	@discussion			Scope: Global
						Value Type: UInt32
						Access: read-only
					Indicates whether the connected host app (if any) receives remote control events.

	@constant		kAudioOutputUnitProperty_RemoteControlToHost
	@discussion			Scope: Global
						Value Type: AudioUnitRemoteControlEvent
						Access: write-only
					A node app can set this property on its output unit in order to send a remote
					control event to the host app.

	@constant		kAudioOutputUnitProperty_HostTransportState
	@discussion			Scope: Global
						Value Type: UInt32 (dummy, always 0)
						Access: listener only
					Indicates that the host's record or play transport state has changed and that any
					UI reflecting it should be updated. The actual state must be fetched from the
					HostCallbacks.

	@constant		kAudioOutputUnitProperty_NodeComponentDescription
	@discussion			Scope: Global
						Value Type: AudioComponentDescription
						Access: read-only
					If a single output unit is published with multiple component descriptions, the
					node app needs to know which component description the host used to connect.
					This property returns that component description.
*/
CF_ENUM(AudioUnitPropertyID) {
	kAudioOutputUnitProperty_MIDICallbacks			= 2010,
	kAudioOutputUnitProperty_HostReceivesRemoteControlEvents
													= 2011,
	kAudioOutputUnitProperty_RemoteControlToHost	= 2012,
	kAudioOutputUnitProperty_HostTransportState		= 2013,
	kAudioOutputUnitProperty_NodeComponentDescription = 2014
};

/*!
	@struct AudioOutputUnitMIDICallbacks
	@abstract For inter-app audio, callbacks for receiving MIDI messages.
	@discussion
		The supplied callback functions are called from the realtime rendering thread, before each
		render cycle, to provide any incoming MIDI messages.
*/
typedef struct {
	void * __nullable userData;
	
	// see MusicDeviceMIDIEvent, MusicDeviceSysEx
	void (*MIDIEventProc)(void * __nullable userData, UInt32 inStatus, UInt32 inData1, UInt32 inData2, UInt32 inOffsetSampleFrame);
	void (*MIDISysExProc)(void * __nullable userData, const UInt8 *inData, UInt32 inLength);
} AudioOutputUnitMIDICallbacks;
#endif // AU_SUPPORT_INTERAPP_AUDIO

/*!
	@struct			AudioOutputUnitStartAtTimeParams
*/
typedef struct AudioOutputUnitStartAtTimeParams {
	// see AudioDeviceStartAtTime
	AudioTimeStamp			mTimestamp;
	UInt32					mFlags;
} AudioOutputUnitStartAtTimeParams;

//=====================================================================================================================
#pragma mark - AUVoiceProcessing unit
/*!
	@enum           Apple Voice Processing Property IDs for OS X and iOS
	@abstract       The collection of property IDs for Apple voice processing units.

	@constant		kAUVoiceIOProperty_BypassVoiceProcessing
	@discussion			Scope: Global
						Value Type: UInt32
						Access: read/write
							Bypass all processing done by the voice processing unit. When set to 0 
							(default), the processing is activated otherwise it is disabled.

	@constant		kAUVoiceIOProperty_VoiceProcessingEnableAGC
	@discussion			Scope: Global
						Value Type: UInt32
						Access: read/write
							Enable automatic gain control on the processed microphone/uplink 
                            signal. On by default.
 
	 @constant		kAUVoiceIOProperty_MuteOutput
	 @discussion		Scope: Global
						Value Type: UInt32
						Access: read/write
							Mutes the output of the voice processing unit. 
							0 (default) = muting off. 1 = mute output.  
*/
CF_ENUM(AudioUnitPropertyID) {
	kAUVoiceIOProperty_BypassVoiceProcessing		= 2100,
	kAUVoiceIOProperty_VoiceProcessingEnableAGC		= 2101,
	kAUVoiceIOProperty_MuteOutput					= 2104 
	
};


#pragma mark - AUVoiceProcessing unit deprecated properties

#if TARGET_OS_IPHONE
/*!
 @enum			Deprecated Apple Voice Processing Property ID (iOS only)
 @constant		kAUVoiceIOProperty_DuckNonVoiceAudio
 @discussion			Scope: Global
                        Value Type: UInt32
                        Access: read/write
                 DEPRECATED. Enable ducking of the non voice audio signal. Since
                 music signals are typically louder than voice, ducking the music signal 
                 can increase the intelligibility of voice chats. Note that the amount of
                 ducking is dependent on the audio route. Set to 0 to turn off or 1 to 
                 turn on. On by default. Deprecation note: What is being deprecated is the
                 ability to turn off this feature via this property. In the future, ducking
                 will always be on.
*/
CF_ENUM(AudioUnitPropertyID) {
	kAUVoiceIOProperty_DuckNonVoiceAudio			= 2102
} API_DEPRECATED("not longer supported", ios(3.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
#endif

/*!
 @enum           Apple Voice Processing Property IDs that are being deprecated
 @constant		kAUVoiceIOProperty_VoiceProcessingQuality
 @discussion		Scope: Global
                    Value Type: UInt32
                    Access: read/write
                DEPRECATED. Sets the quality of the voice processing unit. Quality values
                are comprised between 0 (lowest) and 127 (highest).
 */
CF_ENUM(AudioUnitPropertyID) {
	kAUVoiceIOProperty_VoiceProcessingQuality		= 2103
} __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7, __MAC_10_9, __IPHONE_3_0, __IPHONE_7_0);

//=====================================================================================================================
#pragma mark - AUNBandEQ unit
/*!
	@enum           Apple N-Band EQ Audio Unit Property IDs
	@abstract       The collection of property IDs for the Apple N-Band EQ Audio Unit.
	
	@constant		kAUNBandEQProperty_NumberOfBands
	@discussion			Scope: Global
						Value Type: UInt32
						Access: read/write
							Specifies the number of equalizer bands. If more than kAUNBandEQProperty_MaxNumberOfBands
							are specified, an error is returned.
							Can only be set if the unit is uninitialized.
	
	@constant		kAUNBandEQProperty_MaxNumberOfBands
	@discussion			Scope: Global
						Value Type: UInt32
						Access: read-only
							Returns the maximum number of equalizer bands.
							
	@constant		kAUNBandEQProperty_BiquadCoefficients
	@discussion			Scope: Global
						Value Type: array of Float64
						Access: read-only
							Returns an array of Float64 values, 5 per band.
*/

CF_ENUM(AudioUnitPropertyID) {
	kAUNBandEQProperty_NumberOfBands			= 2200,
	kAUNBandEQProperty_MaxNumberOfBands			= 2201,
	kAUNBandEQProperty_BiquadCoefficients		= 2203
};

#if !TARGET_OS_IPHONE

/*!
 @enum         Apple Voice Processing AudioUnit Error IDs
 @abstract     These are the various error IDs returned by Voice Processing audio unit.
 
 @constant     kAUVoiceIOErr_UnexpectedNumberOfInputChannels
               This error indicates that an unexpected number of input channels was encountered during initialization of voice processing audio unit

*/
CF_ENUM(OSStatus) {
    kAUVoiceIOErr_UnexpectedNumberOfInputChannels     = -66784,
};

#endif

//=====================================================================================================================
#pragma mark - Mixers
/*!
    @enum           Apple Mixer Property IDs
    @abstract       The collection of property IDs for Apple mixers
	
	@constant		kAudioUnitProperty_MeteringMode
	@discussion			Scope: { scope / element }
						Value Type: UInt32
						Access: read/write
						
						Enable or disable metering on a particular scope/element

	@constant		kAudioUnitProperty_MatrixLevels
	@discussion			This property can be used for both the AUMatrixMixer and AUMultiChannelMixer.
	
						AUMatrixMixer
						Scope:			Global
						Value Type:		Float32 array
						Access:			read/write
						
						This property is used to retrieve the entire state of a matrix mixer. The size required is
						the number of (input  channels + 1) * (output channels + 1) - see _MatrixDimensions
						
						So a matrix mixer that has 2 input channels and 2 output channels, will need a 3 x 3 array of Float32
						  
						Global volume is stored at volumes[2][2]
						Input volumes are stored in the last column (volumes[0][2] for the first input channel,  volumes[1][2] for the second)
						Output volumes are stored in the last row (volumes [2][0] and [2][1])
						Cross point volumes are stored at their expected locations ([0][1], etc)
						
						AUMultiChannelMixer
						Scope:			Input
						Value Type:		Float32 array
						Access:			read/write
						
						Gets/sets the matrix levels for one input element. This allows arbitrary mixing configurations
						from all input channels to all output channels.
						The size required is the number of (input channels) * (output channels).
						The matrix stores only the crosspoint gains, there are no overall input or output channel gains.
						
	@constant		kAudioUnitProperty_MatrixDimensions
	@discussion			Scope:			Global
						Value Type:		2 x UInt32
						Access:			Read only
							
						Returns the total number of channels for input and output of a given matrix mixer

	@constant		kAudioUnitProperty_MeterClipping
	@discussion			Scope:			Global
						Value Type:		AudioUnitMeterClipping
						Access:			Read
						
						A mixer returns an AudioUnitMeterClipping structure.


	@constant		kAudioUnitProperty_InputAnchorTimeStamp
	@discussion			Scope:			Input
						Value Type:		AudioTimeStamp
						Access:			Read / Write
						
						There are situations, for example moving an input between mixers, where the
						input's sample time timeline needs to be made continuous. This facilitates
						the operation: after disconnecting the input, fetch its anchor time stamp,
						then before reconnecting it, set the same anchor time stamp. The input's
						sequence of sample times will be maintained.
 
						This property cannot be accessed while the input is rendering.
*/
CF_ENUM(AudioUnitPropertyID) {
	// General mixers
	kAudioUnitProperty_MeteringMode					= 3007,
	
	// Matrix Mixer
	kAudioUnitProperty_MatrixLevels					= 3006,
	kAudioUnitProperty_MatrixDimensions				= 3009,
	kAudioUnitProperty_MeterClipping				= 3011,
	
	// Multichannel Mixer
	kAudioUnitProperty_InputAnchorTimeStamp			= 3016
};

/*!
	@struct			AudioUnitMeterClipping
	
	@var  			peakValueSinceLastCall; 
						The maximum value seen on the channel since the last time the property was retrieved.
	@var  			sawInfinity;
						TRUE if there was an infinite value on this channel.
	@var  			sawNotANumber
						TRUE if there was a floating point Not-A-Number value on this channel.
*/
typedef struct AudioUnitMeterClipping
{
	Float32 peakValueSinceLastCall; 
	Boolean sawInfinity;
	Boolean sawNotANumber;
} AudioUnitMeterClipping;

//=====================================================================================================================
#pragma mark - _SpatialMixer
/*!
    @enum           Apple Mixer Property IDs
    @abstract       The collection of property IDs for AUSpatialMixer
    
    @constant		kAudioUnitProperty_ReverbRoomType
						Scope:			Global
						Value Type:		UInt32
						Access:			Read / Write
						
	@constant		kAudioUnitProperty_UsesInternalReverb
						Scope:			Global
						Value Type:		UInt32
						Access:			Read / Write
						
	@constant		kAudioUnitProperty_SpatializationAlgorithm
						Scope:			Input
						Value Type:		UInt32
						Access:			Read / Write
						
						Used to set the spatialisation algorithm used by an input of AUSpatialMixer. See kSpatializationAlgorithm_
						
	@constant		kAudioUnitProperty_SpatialMixerRenderingFlags
						Scope:			Input
						Value Type:		UInt32
						Access:			Read / Write

						Used to enable various rendering operations on a given input for the 3DMixer. See k3DMixerRenderingFlags_
						
	@constant		kAudioUnitProperty_SpatialMixerAttenuationCurve
						Scope:			Input
						Value Type:		UInt32
						Access:			Read / Write

	@constant		kAudioUnitProperty_SpatialMixerDistanceParams
						Scope:			Input
						Value Type:		MixerDistanceParams
						Access:			Read / Write
*/
CF_ENUM(AudioUnitPropertyID) {
	kAudioUnitProperty_ReverbRoomType				= 10,
	kAudioUnitProperty_UsesInternalReverb			= 1005,
	kAudioUnitProperty_SpatializationAlgorithm		= 3000,
	kAudioUnitProperty_SpatialMixerDistanceParams	= 3010,
	kAudioUnitProperty_SpatialMixerAttenuationCurve	= 3013,
	kAudioUnitProperty_SpatialMixerRenderingFlags	= 3003,
};

/*!
	@enum 	Spatialization Algorithms
*/
typedef CF_ENUM(UInt32, AUSpatializationAlgorithm) {
	kSpatializationAlgorithm_EqualPowerPanning 		= 0,
	kSpatializationAlgorithm_SphericalHead 			= 1,
	kSpatializationAlgorithm_HRTF			 		= 2,
	kSpatializationAlgorithm_SoundField		 		= 3,
	kSpatializationAlgorithm_VectorBasedPanning		= 4,
	kSpatializationAlgorithm_StereoPassThrough		= 5,
    kSpatializationAlgorithm_HRTFHQ                 = 6
};

/*!
	@enum	Reverb Room Types
	@discussion Used to specify room type (as identified by a factory preset number) on Apple audio 
				units that use internal reverb.
*/
typedef CF_ENUM(UInt32, AUReverbRoomType) {
	kReverbRoomType_SmallRoom		= 0,
	kReverbRoomType_MediumRoom		= 1,
	kReverbRoomType_LargeRoom		= 2,
	kReverbRoomType_MediumHall		= 3,
	kReverbRoomType_LargeHall		= 4,
	kReverbRoomType_Plate			= 5,
	kReverbRoomType_MediumChamber	= 6,
	kReverbRoomType_LargeChamber	= 7,
	kReverbRoomType_Cathedral		= 8,
	kReverbRoomType_LargeRoom2		= 9,
	kReverbRoomType_MediumHall2		= 10,
	kReverbRoomType_MediumHall3		= 11,
	kReverbRoomType_LargeHall2		= 12	
};

/*!
	@enum AUSpatialMixer Attenuation Curves
*/
typedef CF_ENUM(UInt32, AUSpatialMixerAttenuationCurve) {
	kSpatialMixerAttenuationCurve_Power					= 0,
    kSpatialMixerAttenuationCurve_Exponential			= 1,
    kSpatialMixerAttenuationCurve_Inverse				= 2,
    kSpatialMixerAttenuationCurve_Linear				= 3
};

/*!
	@struct			MixerDistanceParams
*/
typedef struct MixerDistanceParams {
	Float32					mReferenceDistance;
	Float32					mMaxDistance;
	Float32					mMaxAttenuation;	// in decibels
} MixerDistanceParams;

/*!
	@enum	AUSpatial Mixer Rendering Flags
*/
typedef CF_OPTIONS(UInt32, AUSpatialMixerRenderingFlags) {
	kSpatialMixerRenderingFlags_InterAuralDelay			= (1L << 0),
	kSpatialMixerRenderingFlags_DistanceAttenuation		= (1L << 2),
};

//=====================================================================================================================
#pragma mark - _3DMixer (Deprecated)
/*!
    // AUMixer3D is deprecated. Use AUSpatialMixer instead.
 
    @enum           Apple Mixer Property IDs
    @abstract       The collection of property IDs for Apple mixers

	@constant		kAudioUnitProperty_MeteringMode
	@discussion			Scope: { scope / element }
						Value Type: UInt32
						Access: read/write
						
						Enable or disable metering on a particular scope/element
						
	@constant		kAudioUnitProperty_DopplerShift
	@discussion			Scope:			Input
						Value Type:		UInt32
						Access:			Write
						
						Use a boolean true/false value to enable doppler shift for any specified input
						
	@constant		kAudioUnitProperty_3DMixerRenderingFlags
	@discussion			Scope:			Input
						Value Type:		UInt32
						Access:			Read / Write

						Used to enable various rendering operations on a given input for the 3DMixer. See k3DMixerRenderingFlags_
						
	@constant		kAudioUnitProperty_3DMixerDistanceAtten
	@discussion			Scope:			
						Value Type:
						Access:

	@constant		kAudioUnitProperty_3DMixerDistanceParams
	@discussion			Scope:
						Value Type:
						Access:

	@constant		kAudioUnitProperty_ReverbPreset
	@discussion			Scope:
						Value Type:
						Access:

	@constant		kAudioUnitProperty_3DMixerAttenuationCurve 
	@discussion			Scope:
						Value Type:
						Access:
*/
CF_ENUM(AudioUnitPropertyID) {
	kAudioUnitProperty_3DMixerDistanceParams		= 3010,
	kAudioUnitProperty_3DMixerAttenuationCurve		= 3013,
	kAudioUnitProperty_DopplerShift					= 3002,
	kAudioUnitProperty_3DMixerRenderingFlags		= 3003,
	kAudioUnitProperty_3DMixerDistanceAtten			= 3004,
	kAudioUnitProperty_ReverbPreset					= 3012
} __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7, __MAC_10_11, __IPHONE_3_0, __IPHONE_9_0);

/*!
	@enum	3D Mixer Rendering Flags
*/
typedef CF_OPTIONS(UInt32, AU3DMixerRenderingFlags) {
	k3DMixerRenderingFlags_InterAuralDelay			= (1L << 0),
	k3DMixerRenderingFlags_DopplerShift				= (1L << 1),
	k3DMixerRenderingFlags_DistanceAttenuation		= (1L << 2),
	k3DMixerRenderingFlags_DistanceFilter			= (1L << 3),
	k3DMixerRenderingFlags_DistanceDiffusion		= (1L << 4),
	k3DMixerRenderingFlags_LinearDistanceAttenuation = (1L << 5),
	k3DMixerRenderingFlags_ConstantReverbBlend		= (1L << 6)
};

/*!
	@enum 3D Mixer Attenuation Curves
*/
typedef CF_ENUM(UInt32, AU3DMixerAttenuationCurve) {
	k3DMixerAttenuationCurve_Power					= 0,
    k3DMixerAttenuationCurve_Exponential			= 1,
    k3DMixerAttenuationCurve_Inverse				= 2,
    k3DMixerAttenuationCurve_Linear					= 3
};

//=====================================================================================================================
#pragma mark - AUScheduledSoundPlayer
/*!
    @enum           Apple AUScheduledSoundPlayer Property IDs
    @abstract       The collection of property IDs for the Apple AUScheduledSoundPlayer audio unit.

    @discussion     The AUScheduledSoundPlayer audio unit lets a client schedule audio buffers for
                    future playback, with sample-accurate timing.
                    
                    
                    Elements and Formats
                    
                    This unit has one output element and no input elements. The output's format
                    should be a canonical audio unit stream format (native Float32, deinterleaved).


                    Scheduling

                    To schedule slices of audio for future playback, set the
                    kAudioUnitProperty_ScheduleAudioSlice property, with a ScheduledAudioSlice
                    structure as the property value. The slice's mTimeStamp.mSampleTime field
                    determines when the slice will be played. This sample number is relative to
                    the unit's start time, which you must set using the
                    kAudioUnitProperty_ScheduleStartTimeStamp property before playback will
                    begin.

                    You must retain, unmodified, the ScheduledAudioSlice structure, including
                    its mBufferList and the buffers to which it points, until the slice has been
                    completely played, or until you stop playback by uninitializing or resetting
                    the unit. The format of the slice's buffer list must match the unit's output
                    stream format.
                    
                    As of OS X 10.10 and iOS 8.0, you can use an invalid time stamp (no flags set
                    in mFlags) to indicate that the slice should be played immediately following the
                    previous slice (or immediately, if there are no slices playing).
                    
                    (The fields other than mSampleTime and mFlags in the mTimestamp structure are
                    currently ignored.)
                    
                    
                    Completion
                    
                    To receive a callback when the slice has been played, store a pointer to a
                    callback function in the mCompletionProc field. This function will be called 
                    (from the audio unit's rendering thread) when the slice has been completely 
                    played -- or when the slice is determined to be unplayable due to an error. 
                    As an alternative, you may also poll the slice's 
                    (mFlags & kScheduledAudioSliceFlag_Complete).

                    Upon completion, you can test (mFlags & kScheduledAudioSliceFlag_BeganToRenderLate) 
                    to determine whether some portion of the slice was not played due to its having 
                    been scheduled too late relative to the current playback time.
                    
                    
                    Start Time
                    
                    The audio unit will not play any slices following initialization or reset, until
                    its start time has been set. The start time establishes the beginning of a
                    timeline: the timestamps of all slices in the schedule are relative to the
                    start time.

                    Set a start time by setting the kAudioUnitProperty_ScheduleStartTimeStamp 
                    property with an AudioTimeStamp structure. If the timestamp contains a valid 
                    sample time (timestamp.mFlags & kAudioTimeStampSampleTimeValid), then playback 
                    begins when the timestamp passed to the AudioUnitRender function reaches the 
                    specified sample time. If the specified sample time is -1, playback begins on 
                    the next render cycle.
                    
                    If the start timestamp does not contain a valid sample time, but does contain a
                    valid host time (timestamp.mFlags & kAudioTimeStampHostTimeValid), then the
                    specified host time is translated to the sample time at which playback will
                    begin. A host time of 0 means "start on the next render cycle."
                    
                    The kAudioUnitProperty_ScheduleStartTimeStamp property may be queried to obtain 
                    the time at which playback began. If the start time has not yet been reached,
                    the timestamp returned will be whatever the host application last set.
                    
                    
                    Current play time
                    
                    The kAudioUnitProperty_CurrentPlayTime property may be queried to determine the 
                    audio unit's current time offset from its start time. This is useful, for 
                    example, to monitor playback progress.
                    
                    
                    Unscheduling events
                    
                    To clear an audio unit's play schedule, call the AudioUnitReset function. The 
                    completion proc (if any) for each slice in the schedule will called. Playback 
                    will not resume until a new start time has been set. This also happens when 
                    the audio unit is uninitialized.
    
    @constant       kAudioUnitProperty_ScheduleAudioSlice
    @discussion         Scope:
                        Value Type: ScheduledAudioSlice
                        Access:

    @constant       kAudioUnitProperty_ScheduleStartTimeStamp
    @discussion         Scope:
                        Value Type: AudioTimeStamp
                        Access:
                            Sample time or host time valid. Sample time takes precedence, 
                            -1 means "now". Host time of 0 means "now."
                            
    @constant       kAudioUnitProperty_CurrentPlayTime
    @discussion         Scope:
                        Value Type: AudioTimeStamp
                        Access:
                            AudioTimeStamp, relative to start time, sample time of -1 if not yet started.
*/
CF_ENUM(AudioUnitPropertyID) {
	kAudioUnitProperty_ScheduleAudioSlice			= 3300,
	kAudioUnitProperty_ScheduleStartTimeStamp		= 3301,
	kAudioUnitProperty_CurrentPlayTime				= 3302
};

/*!
    @enum           ScheduledAudioSlice
    @abstract           bits in ScheduledAudioSlice.mFlags

    @constant       kScheduledAudioSliceFlag_Complete
    		            Set if the unit is done with this slice
    @constant       kScheduledAudioSliceFlag_BeganToRender
    		            Set if any portion of the buffer has been played
    @constant       kScheduledAudioSliceFlag_BeganToRenderLate
    		            Set if any portion of the buffer was not played because it was scheduled late
    @constant       kScheduledAudioSliceFlag_Loop
    		            specifies that the buffer should loop indefinitely
    @constant       kScheduledAudioSliceFlag_Interrupt
    		            specifies that the buffer should interrupt any previously scheduled buffer
                        (by default, buffers following a playing buffer are not played until the
                        playing buffer has completed).
    @constant       kScheduledAudioSliceFlag_InterruptAtLoop
    		            specifies that the buffer should interrupt any previously scheduled buffer,
                        but only at a loop point in that buffer.

*/
typedef CF_OPTIONS(UInt32, AUScheduledAudioSliceFlags) {
    kScheduledAudioSliceFlag_Complete               = 0x01,
    kScheduledAudioSliceFlag_BeganToRender          = 0x02,
    kScheduledAudioSliceFlag_BeganToRenderLate      = 0x04,

    kScheduledAudioSliceFlag_Loop                   = 0x08, // new for OS X 10.10 and iOS 8.0
    kScheduledAudioSliceFlag_Interrupt              = 0x10, // new for OS X 10.10 and iOS 8.0
    kScheduledAudioSliceFlag_InterruptAtLoop        = 0x20  // new for OS X 10.10 and iOS 8.0
};

typedef struct ScheduledAudioSlice ScheduledAudioSlice; // forward dec, see definition below
/*!
	@typedef			ScheduledAudioSliceCompletionProc
*/
typedef void (*ScheduledAudioSliceCompletionProc)(void * __nullable userData, ScheduledAudioSlice *bufferList);

/*
	@struct				ScheduledAudioSlice
	@var  				mTimeStamp
	@var  				mCompletionProc
							May be null
	@var  				mCompletionProcUserData
	@var  				mFlags
	@var  				mReserved
							Must be 0
	@var  				mReserved2
							For internal use
	@var  				mNumberFrames
							Must be consistent with byte count of mBufferList
	@var  				mBufferList
							Must contain deinterleaved Float32
*/
struct ScheduledAudioSlice {
	AudioTimeStamp									mTimeStamp;
	ScheduledAudioSliceCompletionProc __nullable	mCompletionProc;
	void *											mCompletionProcUserData;
	AUScheduledAudioSliceFlags						mFlags;
	UInt32											mReserved;		// must be 0
	void *	__nullable								mReserved2;		// for internal use
	UInt32											mNumberFrames;  // must be consistent with byte count of mBufferList
	AudioBufferList *								mBufferList;	// must contain deinterleaved Float32
};

//=====================================================================================================================
#pragma mark - AUAudioFilePlayer
/*!
    @enum           Apple AUAudioFilePlayer Property IDs
    @abstract       The collection of property IDs for Apple AUAudioFilePlayer
	@discussion		This audio unit lets you schedule regions of audio files for future playback,
					with sample-accurate timing.

					The unit is a subclass of AUScheduledSoundPlayer and inherits all of its
					behavior. In particular, this unit implements the kAudioUnitProperty_ScheduleStartTimeStamp 
					and kAudioUnitProperty_CurrentPlayTime properties. Instead of scheduling 
					slices (buffers) of audio to be played (via kAudioUnitProperty_ScheduleAudioSlice), 
					however, you schedule regions of audio files to be played. The unit reads and
					converts audio file data into its own internal buffers. It performs disk I/O
					on a high-priority thread shared among all instances of this unit within a
					process. Upon completion of a disk read, the unit internally schedules
					buffers for playback.


					Elements and Formats
					
					This unit has one output element and no input elements. The output's format
					should be a canonical audio unit stream format (native Float32,
					deinterleaved). This format should have at least as many channels are in the
					audio file(s) to be played (otherwise channels will be dropped). During
					playback, all audio file data is converted to the unit's output format.
					

					Audio Files

					Before starting playback, you must first open all audio files to be played
					using the AudioFile API's (see AudioToolbox/AudioFile.h), and pass their
					AudioFileIDs to the unit by setting the kAudioUnitProperty_ScheduledFileIDs
					property. This property must not be set during playback. The audio files must
					be kept open for the duration of playback.


					Scheduling Regions
					
					To schedule the playback of a region of an audio file, set the
					kAudioUnitProperty_ScheduledFileRegion property. This is a
					ScheduledAudioFileRegion structure. mTimeStamp.mSampleTime must be valid and
					is interpreted relative to the unit's start time -- the start time semantics
					(using kAudioUnitProperty_ScheduleStartTimeStamp) are identical to those of
					AUScheduledSoundPlayer. Unlike the ScheduledAudioSlice structures, the unit
					makes copies of ScheduledAudioFileRegions, so you may create them on the
					stack or otherwise reuse/dispose of them immediately after scheduling them.
					
					
					Priming
					
					You should set kAudioUnitProperty_ScheduledFilePrime after scheduling
					initial file regions to be played and before starting playback. This SetProperty call
					will begin reading the audio files and not return until the number of frames
					specified by the property value have been read.
					
					
					Completion Callbacks
					
					A region's completion callback (mCompletionProc) is called when it has been
					completely scheduled for reading from disk. This callback is issued on the disk 
					read thread. If the region is not read from disk in time to play at its
					scheduled time, mCompletionProc is called a second time with an error code,
					also from the read thread. Note that the region passed to the callback will not
					be the same memory object as was passed by the client (since the unit copies the region).
					
					
					Start Time and Current Time
					
					These properties work identically as in AUScheduledSoundPlayer.
					
					
					Unscheduling regions
					
					To clear the unit's play schedule, call the AudioUnitReset function. The completion proc
					(if any) for each file region in the schedule will be called. Playback will
					not resume until a new start time has been set. This also happens when the
					unit is uninitialized.
					
					
					Customization
					
					The size and number of the player's disk read buffers default to "sensible"
					values, but may be configured with the properties:
						kAudioUnitProperty_ScheduledFileBufferSizeFrames
						kAudioUnitProperty_ScheduledFileNumberBuffers
					

					Bugs
					
					kAudioUnitProperty_ScheduledFileBufferSizeFrames
					kAudioUnitProperty_ScheduledFileNumberBuffers
						are currently unimplemented

					An option to make the unit not perform conversion from the audio file sample
					rate to the unit's output rate may be desirable.
	
	@constant		kAudioUnitProperty_ScheduledFileIDs
	@discussion			Scope:
						Value Type: Array of AudioFileIDs
						Access:
							Must set this property on scheduled file player for all files to be played

	@constant		kAudioUnitProperty_ScheduledFileRegion
	@discussion			Scope:
						Value Type: ScheduledAudioFileRegion
						Access:

	@constant		kAudioUnitProperty_ScheduledFilePrime
	@discussion			Scope:
						Value Type: UInt32
						Access:
							The number of frames to read from disk before returning, or 0 to specify use 
							of a default value

	@constant		kAudioUnitProperty_ScheduledFileBufferSizeFrames
	@discussion			Scope:
						Value Type: UInt32
						Access:

	@constant		kAudioUnitProperty_ScheduledFileNumberBuffers
	@discussion			Scope:
						Value Type: UInt32
						Access:
*/
CF_ENUM(AudioUnitPropertyID) {
	kAudioUnitProperty_ScheduledFileIDs				= 3310,
	kAudioUnitProperty_ScheduledFileRegion			= 3311,
	kAudioUnitProperty_ScheduledFilePrime			= 3312,
	kAudioUnitProperty_ScheduledFileBufferSizeFrames = 3313,
	kAudioUnitProperty_ScheduledFileNumberBuffers   = 3314
};

typedef struct ScheduledAudioFileRegion ScheduledAudioFileRegion; //forward declaration, see definition below
/*!
	@typedef		ScheduledAudioFileRegionCompletionProc
*/
typedef void (*ScheduledAudioFileRegionCompletionProc)(void * __nullable userData,
				ScheduledAudioFileRegion *fileRegion, OSStatus result);

/*!
	@struct			ScheduledAudioFileRegion
	@var  			mTimeStamp
	@var  			mCompletionProc
						may be NULL
	@var  			mCompletionProcUserData
	@var  			mAudioFile
						must be a valid and open AudioFileID
						defined in AudioToolbox/AudioFile.h: typedef	struct OpaqueAudioFileID	*AudioFileID;
	@var  			mLoopCount
						0 = don't loop
	@var  			mStartFrame
						offset into file
	@var  			mFramesToPlay
						number of frames to play
	
*/
struct ScheduledAudioFileRegion {
	AudioTimeStamp										mTimeStamp;
	ScheduledAudioFileRegionCompletionProc __nullable	mCompletionProc;
	void * __nullable									mCompletionProcUserData;
	struct OpaqueAudioFileID *							mAudioFile;
	UInt32												mLoopCount;
	SInt64												mStartFrame;
	UInt32												mFramesToPlay;
};

#if !TARGET_OS_IPHONE

//=====================================================================================================================
#pragma mark - OS X-specific Music Device Properties used by DLSMusicDevice
/*!
 @enum			Property IDs
 @abstract       OS X-only audio unit property IDs used by the DLSMusicDevice
 
 @constant		kMusicDeviceProperty_SoundBankData
 @discussion			Scope:
 Value Type:
 Access:
 
 @constant		kMusicDeviceProperty_StreamFromDisk
 @discussion			Scope:
 Value Type:
 Access:
 
 @constant		kMusicDeviceProperty_SoundBankFSRef
 @discussion			Scope:
 Value Type:
 Access:
 
 */

CF_ENUM(AudioUnitPropertyID) {
	kMusicDeviceProperty_UsesInternalReverb			= kAudioUnitProperty_UsesInternalReverb,
	kMusicDeviceProperty_SoundBankData				= 1008,
	kMusicDeviceProperty_StreamFromDisk				= 1011,
	kMusicDeviceProperty_SoundBankFSRef				= 1012
};

#endif	// TARGET_OS_IPHONE

//=====================================================================================================================
#pragma mark - Music Device Properties used by DLSMusicDevice

/*!
	@enum           Generic Property IDs
	@abstract       Audio unit property IDs used by DLSMusicDevice (OSX)
 
	@constant		kMusicDeviceProperty_InstrumentName
	@discussion			Scope:				Global
						Value Type:			CFURLRef
						Access:				Read
 
	@constant		kMusicDeviceProperty_InstrumentNumber
	@discussion			Scope:				Global
						Value Type: 		UInt32
						Access:				Read
 */

CF_ENUM(AudioUnitPropertyID) {
	kMusicDeviceProperty_InstrumentName				= 1001,
	kMusicDeviceProperty_InstrumentNumber 			= 1004
};

//=====================================================================================================================
#pragma mark - Music Device Properties used by DLSMusicDevice and AUMIDISynth

/*!
	@enum           Generic Property IDs
	@abstract       Audio unit property IDs used by AUMIDISynth (iOS) and DLSMusicDevice (OSX)
 
	@constant		kMusicDeviceProperty_InstrumentCount
	@discussion			Scope:				Global
						Value Type:			UInt32
						Access:				Read
 
					For a mono-timbral music instrument, this property should return 0 (it should be implemented).
 
					For a multi-timbral music instrument, this property can return the number of independent patches that
					are available to be chosen as an active patch for the instrument. For instance, for Apple's DLS Music Device
					and AUMIDISynth, this value returns the number of patches that are found in a given DLS or SoundFont file when loaded.
 
	@constant		kMusicDeviceProperty_BankName
	@discussion			Scope:				Global
						Value Type: 		CFStringRef
						Access: 			Read
 
	@constant		kMusicDeviceProperty_SoundBankURL
	@discussion			Scope:				Global
						Value Type:			CFURLRef
						Access:				Read (Read/Write for AUMIDISynth)
						
					For DLSMusicDevice, this is a read-only property to return the URL for the currently-loaded bank file.
					For AUMIDISynth it is also writeable, and is used to specify the URL for the sound bank to load and use 
					for playback.
 */

CF_ENUM(AudioUnitPropertyID) {
	kMusicDeviceProperty_InstrumentCount 			= 1000,
	kMusicDeviceProperty_BankName					= 1007,
	kMusicDeviceProperty_SoundBankURL				= 1100
};

//=====================================================================================================================
#pragma mark - AUMIDISynth

/*!
	@enum			Apple AUMIDISynth Property IDs
	@abstract		The collection of property IDs for the Apple Midi Synth audio unit.
 
	@discussion		The AUMIDISynth audio unit lets a client create fully GM-compatible Midi Synth.
 
	@constant		kAUMIDISynthProperty_EnablePreload
	@discussion			Scope:			Global
						Value Type:		UInt32
						Access: 		Write
 
 					Setting this property to 1 puts the MIDISynth in a mode where it will attempt to load
 					instruments from the bank or file when it receives a program change message.  This
 					is used internally by the MusicSequence.  It should only be used prior to MIDI playback,
					and must be set back to 0 before attempting to start playback.
 */

CF_ENUM(AudioUnitPropertyID) {
	kAUMIDISynthProperty_EnablePreload				= 4119
};

//=====================================================================================================================
#pragma mark - AUSampler

/*!
	@enum			Apple AUSampler Property IDs
	@abstract		The collection of property IDs for the Apple Sampler audio unit.
 
	@discussion		The AUSampler audio unit lets a client create an editable, interactive
					sampler synthesizer instrument.
 
	@constant		kAUSamplerProperty_LoadInstrument
	@discussion			Scope:			Global
						Value Type:		AUSamplerInstrumentData
						Access:			Write
							Load an instrument from an external DLS or Soundfont2 bank file, or from other file formats.
 
	@constant		kAUSamplerProperty_LoadAudioFiles
	@discussion			Scope:			Global
						Value Type:		CFArrayRef
						Access:			Write
							Create a new preset from a list of audio file paths.  The CFArray should contain a set
							of CFURLRefs, one per file.  The previous preset will be completely cleared.
 */
CF_ENUM(AudioUnitPropertyID) {
	// range (4100->4999)
	kAUSamplerProperty_LoadInstrument				= 4102,
	kAUSamplerProperty_LoadAudioFiles				= 4101
};

/*
	@struct			AUSamplerInstrumentData
	@abstract		Used for loading an instrument from either an external bank file (i.e. DLS or SoundFont), an Apple
 					.aupreset, a Logic or GarageBand EXS24 sampler instrument, or creating a new default instrument from
 					a single audio file.  The path to the bank or instrument file is specified in the fileURL field.
 					The instrumentType field distinguishes between the instrument types.  The remaining fields of this
 					struct are used only for the kInstrumentType_DLSPreset and kInstrumentType_SF2Preset types to
 					identify the particular bank and preset IDs for the instrument you wish to load from the bank.
 					They represent values for MIDI controllers 0 and 32 and the MIDI present change message that would be
 					sent to a GM2-compatible synth for program changes.  Use the provided constants
 					(kAUSampler_DefaultMelodicBankMSB,  kAUSampler_DefaultPercussionBankMSB) to designate  melodic or
 					percussion banks per the GM2 specification (GM-compatible DLS or Soundfont banks).  For custom
 					non-GM-compatible DLS and Soundfont banks, use the actual MSB/LSB values associated with the desired preset.

	@var  			fileURL
						The URL of the path to the bank or instrument file.   Caller is responsible for releasing the
 						provided CFURLRef.
	@var  			instrumentType
						The type of instrument being loaded or created.  For example, use kInstrumentType_DLSPreset to load an
 						instrument from a DLS bank file.
	@var  			bankMSB
						For the preset instruments, the most significant byte value for a particular bank variation within that
 						file.  Range is 0 to 127.  Use kAUSampler_DefaultMelodicBankMSB by default.
	@var  			bankLSB
						For the preset instruments, the least significant byte value for a particular bank variation within that
 						file.  Range is 0 to 127.  Use kAUSampler_DefaultBankLSB by default.
	@var  			presetID
						For the preset instruments, the numeric ID of a particular preset within that bank to load.
 						Range is 0 to 127.
 */

typedef struct AUSamplerInstrumentData {
	CFURLRef				fileURL;
	UInt8					instrumentType;
	UInt8					bankMSB;
	UInt8					bankLSB;
	UInt8					presetID;
} AUSamplerInstrumentData;

/*
	@enum			InstrumentTypes
	@abstract		Values to specify the type of instrument being loaded.

	@constant		kInstrumentType_DLSPreset
	@discussion			A preset from a DLS bank file.  Bank MSB, LSB and preset ID must be specified.
 
	@constant		kInstrumentType_SF2Preset
	@discussion			A preset from a SoundFont2 bank file.  Bank MSB, LSB and preset ID must be specified.
 
	@constant		kInstrumentType_AUPreset
	@discussion			A native Apple .aupreset file created using the AUSampler's custom view.
 
	@constant		kInstrumentType_Audiofile
	@discussion			An audio file which will be used to create a default instrument with that file as its sole sample.
	
 	@constant		kInstrumentType_EXS24
	@discussion			A Logic or GarageBand sampler instrument.

 */

enum
{
	kInstrumentType_DLSPreset	= 1,
	kInstrumentType_SF2Preset	= kInstrumentType_DLSPreset,
	kInstrumentType_AUPreset	= 2,
	kInstrumentType_Audiofile	= 3,
	kInstrumentType_EXS24		= 4
};

enum 
{
	kAUSampler_DefaultPercussionBankMSB	=	0x78,
	kAUSampler_DefaultMelodicBankMSB	=	0x79,
	kAUSampler_DefaultBankLSB			=	0x00
};


//=====================================================================================================================
#pragma mark - AUDeferredRenderer
/*!
	@enum			AUDeferredRenderer
	@discussion		This audio unit has one input element and one output element. They must both have
					the same format, which must be canonical (Float32 deinterleaved) and must have 
					the same number of channels.

					The AUDeferredRenderer unit creates a high-priority producer thread, on which 
					calls by this AU for input are performed at a constant buffer size. This buffer size may be
					set with the kAudioUnitProperty_DeferredRendererPullSize property. The deferred 
					renderer may be asked to render at different buffer sizes by a downstream unit or
					host application, but it always pulls upstream at its constant buffer size.
					The upstream pull size MUST be greater than or equal to the downstream pull
					size.

					The upstream producer thread runs in advance of calls to its Render
					function, with respect to the timestamps being passed to Render and
					PullInput. The difference between these timestamps is the unit's "latency",
					which is always at least one upstream pull buffer. The client may specify
					additional latency with the property
					kAudioUnitProperty_DeferredRendererExtraLatency, which is a number of sample
					frames.

					It is possible, at Render time, for the producer thread to have not yet
					finished rendering the necessary data. This generates an error. In order to
					give the producer a small amount of extra time to finish rendering, the
					client may set the unit's property
					kAudioUnitProperty_DeferredRendererWaitFrames. If this property is non-zero,
					then when Render finds that insufficient data has been produced, it will
					sleep for the amount of realtime corresponding to the number of wait frames.
					It will then check again to see if the required amount of data has been
					produced, and fail if it hasn't.

	@constant		kAudioUnitProperty_DeferredRendererPullSize
	@discussion			Scope:
						Value Type: UInt32
						Access:

	@constant		kAudioUnitProperty_DeferredRendererExtraLatency
	@discussion			Scope:
						Value Type: UInt32
						Access:

	@constant		kAudioUnitProperty_DeferredRendererWaitFrames
	@discussion			Scope:
						Value Type: UInt32
						Access:
*/
CF_ENUM(AudioUnitPropertyID) {
	kAudioUnitProperty_DeferredRendererPullSize		= 3320,
	kAudioUnitProperty_DeferredRendererExtraLatency	= 3321,
	kAudioUnitProperty_DeferredRendererWaitFrames   = 3322
};

#if !TARGET_OS_IPHONE

//=====================================================================================================================
#pragma mark - AUNetReceive
/*!
	@enum			AUNetReceive
	@constant		kAUNetReceiveProperty_Hostname
	@discussion			Scope: Global
						Value Type: CFStringRef
						Access:
						The hostname from which you wish to receive audio.
						For GetProperty, the returned CFStringRef is a copy and therefore must be released by the caller.
						The UI view for AUNetReceive does the resolution of Bonjour service names to hostnames. 
						Clients who are using this AU programmatically using Bonjour will have to do this resolution themselves. 
						It is not done by the AU.

	@constant		kAUNetReceiveProperty_Password
	@discussion			Scope: Global
						Value Type: CFStringRef
						Access: Read / Write
						The password to send to the sender. Leave unset or set to the empty string for no password.
						For GetProperty, the returned CFStringRef is a copy and therefore must be released by the caller.
*/
CF_ENUM(AudioUnitPropertyID) {
	kAUNetReceiveProperty_Hostname                  = 3511,
	kAUNetReceiveProperty_Password                  = 3512
};
	
//=====================================================================================================================
#pragma mark - AUNetSend
/*!
	@enum			AUNetSend
	@constant		kAUNetSendProperty_PortNum
	@discussion			Scope: Global
						Value Type: UInt32
						Access: Read / Write
						The network port number on which to send.

	@constant		kAUNetSendProperty_TransmissionFormat
	@discussion			Scope: Global
						Value Type: AudioStreamBasicDescription
						Access: Read / Write
						Get or set an arbitrary format that will be used to transmit the audio.
						For compressed formats, it is recommended to use kAUNetSendProperty_TransmissionFormatIndex instead of this property,
						since there is no way to specify a bit rate with this property.

	@constant		kAUNetSendProperty_TransmissionFormatIndex
	@discussion			Scope: Global
						Value Type: UInt32
						Access: Read / Write
						Get or set the index of the preset format that will be used to transmit the audio.
						The format indices can be found in the NetSendPresetFormat enum.

	@constant		kAUNetSendProperty_ServiceName
	@discussion			Scope: Global
						Value Type: CFStringRef
						Access: Read / Write
						The name you want to publish for this network service.
						For GetProperty, the returned CFStringRef is a copy and therefore must be released by the caller.

	@constant		kAUNetSendProperty_Disconnect
	@discussion			Scope: Global
						Value Type: UInt32
						Access: Read / Write
						In order to disconnect, call this with a non-zero value.
						In order to connect, call this with a zero value. 
						For GetProperty, the returned value the last value set by the caller.
						To get the current connection status, get the value of the parameter kAUNetReceiveParam_Status.

	@constant		kAUNetSendProperty_Password
	@discussion			Scope: Global
						Value Type: CFStringRef
						Access: Read / Write
						The password that must be used by the receiver. Leave unset or set to the empty string for no password.
						For GetProperty, the returned CFStringRef is a copy and therefore must be released by the caller.

*/
CF_ENUM(AudioUnitPropertyID) {
	kAUNetSendProperty_PortNum                      = 3513,
	kAUNetSendProperty_TransmissionFormat           = 3514,
	kAUNetSendProperty_TransmissionFormatIndex      = 3515,
	kAUNetSendProperty_ServiceName                  = 3516,
	kAUNetSendProperty_Disconnect                   = 3517,
	kAUNetSendProperty_Password                     = 3518
};

/*!
	@enum			NetSendPresetFormat
	@constant		kAUNetSendPresetFormat_PCMFloat32
	@discussion			1411 kilobits per second per channel @ 44100KHz (kilo == 1000 not 1024)
	@constant		kAUNetSendPresetFormat_PCMInt24
	@discussion			1058 kilobits per second per channel @ 44100KHz
	@constant		kAUNetSendPresetFormat_PCMInt16
	@discussion			706 kilobits per second per channel @ 44100KHz
	@constant		kAUNetSendPresetFormat_Lossless24
	@discussion			650 kilobits per second per channel @ 44100KHz
	@constant		kAUNetSendPresetFormat_Lossless16
	@discussion			350 kilobits per second per channel @ 44100KHz
	@constant		kAUNetSendPresetFormat_ULaw
	@discussion			353 kilobits per second per channel @ 44100KHz
	@constant		kAUNetSendPresetFormat_IMA4
	@discussion			176 kilobits per second per channel @ 44100KHz
	@constant		kAUNetSendPresetFormat_AAC_128kbpspc
	@discussion			128 kilobits per second per channel
	@constant		kAUNetSendPresetFormat_AAC_96kbpspc
	@discussion			96 kilobits per second per channel
	@constant		kAUNetSendPresetFormat_AAC_80kbpspc
	@discussion			80 kilobits per second per channel
	@constant		kAUNetSendPresetFormat_AAC_64kbpspc
	@discussion			64 kilobits per second per channel
	@constant		kAUNetSendPresetFormat_AAC_48kbpspc
	@discussion			48 kilobits per second per channel
	@constant		kAUNetSendPresetFormat_AAC_40kbpspc
	@discussion			40 kilobits per second per channel
	@constant		kAUNetSendPresetFormat_AAC_32kbpspc
	@discussion			32 kilobits per second per channel
	@constant		kAUNetSendNumPresetFormats = 14
*/
CF_ENUM(AudioUnitPropertyID) {
	kAUNetSendPresetFormat_PCMFloat32		= 0,
	kAUNetSendPresetFormat_PCMInt24			= 1,
	kAUNetSendPresetFormat_PCMInt16			= 2,
	kAUNetSendPresetFormat_Lossless24		= 3,
	kAUNetSendPresetFormat_Lossless16		= 4,
	kAUNetSendPresetFormat_ULaw				= 5,
	kAUNetSendPresetFormat_IMA4				= 6,
	kAUNetSendPresetFormat_AAC_128kbpspc	= 7,
	kAUNetSendPresetFormat_AAC_96kbpspc		= 8,
	kAUNetSendPresetFormat_AAC_80kbpspc		= 9,
	kAUNetSendPresetFormat_AAC_64kbpspc		= 10,
	kAUNetSendPresetFormat_AAC_48kbpspc		= 11,
	kAUNetSendPresetFormat_AAC_40kbpspc		= 12,
	kAUNetSendPresetFormat_AAC_32kbpspc		= 13,
	kAUNetSendPresetFormat_AAC_LD_64kbpspc	= 14,
	kAUNetSendPresetFormat_AAC_LD_48kbpspc	= 15,
	kAUNetSendPresetFormat_AAC_LD_40kbpspc	= 16,
	kAUNetSendPresetFormat_AAC_LD_32kbpspc	= 17,
	kAUNetSendNumPresetFormats				= 18
};

#endif // _TARGET_OS_IPHONE for Apple Specific audio units

//=====================================================================================================================
#pragma mark -
#pragma mark Deprecated Properties

#if !TARGET_OS_IPHONE

// NumVersion is no longer used (originally from MacTypes.h)
#if TARGET_RT_BIG_ENDIAN
typedef struct AUNumVersion {
                                              /* Numeric version part of 'vers' resource */
  UInt8               majorRev;               /*1st part of version number in BCD*/
  UInt8               minorAndBugRev;         /*2nd & 3rd part of version number share a byte*/
  UInt8               stage;                  /*stage code: dev, alpha, beta, final*/
  UInt8               nonRelRev;              /*revision level of non-released version*/
} AUNumVersion;
#else
typedef struct AUNumVersion {
                                              /* Numeric version part of 'vers' resource accessible in little endian format */
  UInt8               nonRelRev;              /*revision level of non-released version*/
  UInt8               stage;                  /*stage code: dev, alpha, beta, final*/
  UInt8               minorAndBugRev;         /*2nd & 3rd part of version number share a byte*/
  UInt8               majorRev;               /*1st part of version number in BCD*/
} AUNumVersion;
#endif  /* TARGET_RT_BIG_ENDIAN */

/*!
	@struct			AUHostIdentifier
	@abstract		Used to describe the name and version of the audio unit's host
*/
typedef struct AUHostIdentifier {
	CFStringRef 		hostName;	
	AUNumVersion		hostVersion;
} AUHostIdentifier;

//=====================================================================================================================
// GENERIC
enum {
	kAudioUnitParameterFlag_Global		= (1L << 0),	//	parameter scope is global
	kAudioUnitParameterFlag_Input		= (1L << 1),	//	parameter scope is input
	kAudioUnitParameterFlag_Output		= (1L << 2),	//	parameter scope is output
	kAudioUnitParameterFlag_Group		= (1L << 3)		//	parameter scope is group
};

enum {
	kAudioUnitParameterFlag_HasName				= kAudioUnitParameterFlag_ValuesHaveStrings
};

CF_ENUM(AudioUnitPropertyID) {
	//kAudioUnitProperty_SetInputCallback		= 7 -> deprecated
	kAudioUnitProperty_SRCAlgorithm				= 9, // see kAudioUnitProperty_SampleRateConverterComplexity
	kAudioUnitProperty_MIDIControlMapping		= 17, // see ParameterMIDIMapping Properties
	kAudioUnitProperty_CurrentPreset			= 28, // see PresentPreset

	kAudioUnitProperty_ParameterValueName		= kAudioUnitProperty_ParameterStringFromValue,
	kAudioUnitProperty_BusCount					= kAudioUnitProperty_ElementCount,

	kAudioOfflineUnitProperty_InputSize			= kAudioUnitOfflineProperty_InputSize,
	kAudioOfflineUnitProperty_OutputSize		= kAudioUnitOfflineProperty_OutputSize
};

CF_ENUM(UInt32) {
	kAudioUnitSRCAlgorithm_Polyphase			= 'poly',	// same as kAudioUnitSampleRateConverterComplexity_Normal
	kAudioUnitSRCAlgorithm_MediumQuality		= 'csrc'	// same as kAudioUnitSampleRateConverterComplexity_Normal
};


// Deprecated in Mac OS X v10.2. See AUParameterMIDIMapping.
typedef struct AudioUnitMIDIControlMapping
{
	UInt16					midiNRPN;
	UInt8					midiControl;
	UInt8					scope;
	AudioUnitElement		element;
	AudioUnitParameterID	parameter;
} AudioUnitMIDIControlMapping;

// Deprecated. See AudioUnitParameterStringFromValue for equivalent structure, but with clearer field names
typedef struct AudioUnitParameterValueName {
	AudioUnitParameterID		inParamID;
	const Float32 * __nonnull	inValue;	// may be NULL if should translate current parameter value
	CFStringRef					outName;  	// see comments for kAudioUnitProperty_ParameterStringFromValue
} AudioUnitParameterValueName;


//=====================================================================================================================
// Deprecated. These properties are Apple specific.
CF_ENUM(AudioUnitPropertyID) {
	kMusicDeviceProperty_GroupOutputBus				= 1002,
	kMusicDeviceProperty_SoundBankFSSpec			= 1003,
	kAudioUnitProperty_PannerMode					= 3008
};

CF_ENUM(AudioUnitPropertyID) {
	kAudioUnitProperty_SpeakerConfiguration			= 3001
};

// Deprecated in favor of the newer AudioChannelLayout
// structure and its supporting property.
enum {
	kSpeakerConfiguration_HeadPhones		 		= 0,
	kSpeakerConfiguration_Stereo			 		= 1,
	kSpeakerConfiguration_Quad			 			= 2,
	kSpeakerConfiguration_5_0						= 3,
	kSpeakerConfiguration_5_1				 		= kSpeakerConfiguration_5_0
};

#endif // !TARGET_OS_IPHONE

// Deprecated in favor of the newer AUSamplerInstrumentData
// structure and its supporting property.

typedef struct AUSamplerBankPresetData {
	CFURLRef				bankURL;
	UInt8					bankMSB;
	UInt8					bankLSB;
	UInt8					presetID;
	UInt8					reserved;
} AUSamplerBankPresetData;

CF_ENUM(AudioUnitPropertyID) {
	kAUSamplerProperty_LoadPresetFromBank			= 4100,
	kAUSamplerProperty_BankAndPreset				= kAUSamplerProperty_LoadPresetFromBank
};

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioUnitProperties_h
#else
#include <AudioToolboxCore/AudioUnitProperties.h>
#endif
// ==========  AudioToolbox.framework/Headers/AudioServices.h
/*!
	@file		AudioServices.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2006-2015 by Apple, Inc., all rights reserved.
    @abstract   API's for general high level audio services.

    @discussion

    AudioServices provides a means to play audio for things such as UI sound effects.
*/

#ifndef AudioToolbox_AudioServices_h
#define AudioToolbox_AudioServices_h

//==================================================================================================
#pragma mark    Includes

#include <TargetConditionals.h>
#include <Availability.h>
#if !TARGET_OS_IPHONE
    #include <CoreAudio/AudioHardware.h>
    #include <AudioToolbox/AudioHardwareService.h>
#elif TARGET_OS_IOS && !TARGET_OS_UIKITFORMAC
    // AudioSession.h is deprecated and unavailable in UIKITFORMAC.
    #include <AudioToolbox/AudioSession.h>
#endif
#include <CoreFoundation/CoreFoundation.h>

//==================================================================================================
CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

//==================================================================================================
#pragma mark    AudioServices Error Constants

/*!
    @enum           AudioServices error codes
    @abstract       Error codes returned from the AudioServices portion of the API.
    @constant       kAudioServicesNoError
                        No error has occurred
    @constant       kAudioServicesUnsupportedPropertyError 
                        The property is not supported.
    @constant       kAudioServicesBadPropertySizeError 
                        The size of the property data was not correct.
    @constant       kAudioServicesBadSpecifierSizeError 
                        The size of the specifier data was not correct.
    @constant       kAudioServicesSystemSoundUnspecifiedError 
                        A SystemSound unspecified error has occurred.
    @constant       kAudioServicesSystemSoundClientTimedOutError 
                        The SystemSound client message timed out
    @constant       kAudioServicesSystemSoundExceededMaximumDurationError
                        The SystemSound's duration exceeded the allowable threshold
*/
CF_ENUM(OSStatus)
{
	kAudioServicesNoError									=  0,
	kAudioServicesUnsupportedPropertyError					= 'pty?',
	kAudioServicesBadPropertySizeError						= '!siz',
	kAudioServicesBadSpecifierSizeError 					= '!spc',

	kAudioServicesSystemSoundUnspecifiedError				= -1500,
	kAudioServicesSystemSoundClientTimedOutError			= -1501,
    kAudioServicesSystemSoundExceededMaximumDurationError   = -1502
};

//==================================================================================================
#pragma mark    AudioServices Types

/*!
    @typedef        SystemSoundID
    @abstract       SystemSoundIDs are created by the System Sound client application
                    for playback of a provided AudioFile.
*/
typedef UInt32      SystemSoundID;

/*!
    @typedef        AudioServicesPropertyID
    @abstract       Type used for specifying an AudioServices property.
*/
typedef UInt32      AudioServicesPropertyID;

/*!
    @typedef        AudioServicesSystemSoundCompletionProc
    @abstract       A function to be executed when a SystemSoundID finishes playing.
    @discussion     AudioServicesSystemSoundCompletionProc may be provided by client application to be
                    called when a SystemSoundID has completed playback.
    @param          ssID
                        The SystemSoundID that completed playback
    @param          clientData
                        Client application user data
*/
typedef void
(*AudioServicesSystemSoundCompletionProc)(  SystemSoundID       ssID,
                                        	void* __nullable    clientData);

//==================================================================================================
#pragma mark    AudioServices Constants

#if !TARGET_OS_IPHONE
/*!
    @enum           AudioServices constants
    @abstract       Constants for use with System Sound portion of the AudioServices APIs.
    @constant       kSystemSoundID_UserPreferredAlert 
                        Use this constant with the play sound APIs to
                        playback the alert sound selected by the User in System Preferences.
    @constant       kSystemSoundID_FlashScreen
                        Use this constant with the play sound APIs to flash the screen
                        - Desktop systems only
*/
CF_ENUM(SystemSoundID)
{
    kSystemSoundID_UserPreferredAlert   = 0x00001000,
    kSystemSoundID_FlashScreen          = 0x00000FFE,
        // this has been renamed to be consistent
    kUserPreferredAlert     = kSystemSoundID_UserPreferredAlert
};
#endif

/*!
    @enum           AudioServices constants
    @constant       kSystemSoundID_Vibrate
                        Use this constant with the play sound APIs to vibrate the device
                        - iOS only 
                            - on a device with no vibration capability (like iPod Touch) this will 
                            do nothing
*/
CF_ENUM(SystemSoundID)
{
    kSystemSoundID_Vibrate              = 0x00000FFF
};

//==================================================================================================
#pragma mark    AudioServices Properties

/*!
    @enum           AudioServices property codes
    @abstract       These are the property codes used with the AudioServices API.
    @constant       kAudioServicesPropertyIsUISound
                        a UInt32 where 1 means that the SystemSoundID passed in the
                        inSpecifier parameter will respect the 'Play user interface sounds effects'
                        check box in System Preferences and be silent when the user turns off UI
                        sounds. This property is set to 1 by default. Set to 0 if it is desired for
                        an SystemSoundID to always be heard when passed to AudioServicesPlaySystemSound(), 
                        regardless of user's setting in the Sound Preferences.
    @constant       kAudioServicesPropertyCompletePlaybackIfAppDies 
                        a UInt32 where 1 means that the SystemSoundID passed in the
                        inSpecifier parameter will finish playing even if the client application goes away.
*/
CF_ENUM(AudioServicesPropertyID)
{
    kAudioServicesPropertyIsUISound                   = 'isui',
    kAudioServicesPropertyCompletePlaybackIfAppDies   = 'ifdi'
};

//==================================================================================================
#pragma mark    AudioServices Functions

/*!
    @functiongroup  AudioServices
*/

/*!
    @function       AudioServicesCreateSystemSoundID
    @abstract       Allows the application to designate an audio file for playback by the System Sound server.
    @discussion     Returned SystemSoundIDs are passed to AudioServicesPlayAlertSoundWithCompletion() 
                    and AudioServicesPlaySystemSoundWithCompletion() to be played.
 
                    The maximum supported duration for a system sound is 30 secs.
    @param          inFileURL
                        A CFURLRef for an AudioFile.
    @param          outSystemSoundID
                        Returns a SystemSoundID.
*/
extern OSStatus 
AudioServicesCreateSystemSoundID(   CFURLRef                    inFileURL,
                                    SystemSoundID*              outSystemSoundID)
                                                                API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
                                                                ;
	
/*!
    @function       AudioServicesDisposeSystemSoundID
    @abstract       Allows the System Sound server to dispose any resources needed for the provided
                    SystemSoundID.
    @discussion     Allows the application to tell the System Sound server that the resources for the
                    associated audio file are no longer required.
    @param          inSystemSoundID
                        A SystemSoundID that the application no longer needs to use.
*/
extern OSStatus 
AudioServicesDisposeSystemSoundID(SystemSoundID inSystemSoundID)                                    
                                                                API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
                                                                ;

/*!
    @function       AudioServicesPlayAlertSoundWithCompletion
    @abstract       Play an alert sound
    @discussion     Play the sound designated by the provided SystemSoundID with alert sound behavior.
    @param          inSystemSoundID
                        The SystemSoundID to be played. On the desktop the kSystemSoundID_UserPreferredAlert
                        constant can be passed in to play back the alert sound selected by the user
                        in System Preferences. On iOS there is no preferred user alert sound.
    @param          inCompletionBlock
                        The completion block gets executed for every attempt to play a system sound irrespective
                        of success or failure. The callbacks are issued on a serial queue and the client is
                        responsible for handling thread safety.
*/
extern void
AudioServicesPlayAlertSoundWithCompletion(  SystemSoundID inSystemSoundID,
                                            void (^__nullable inCompletionBlock)(void))
                                                                    API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
                                                                    ;
                                                                
/*!
    @function       AudioServicesPlaySystemSoundWithCompletion
    @abstract       Play a system sound
    @discussion     Play the sound designated by the provided SystemSoundID.
    @param          inSystemSoundID
                        The SystemSoundID to be played.
    @param          inCompletionBlock
                        The completion block gets executed for every attempt to play a system sound irrespective 
                        of success or failure. The callbacks are issued on a serial queue and the client is 
                        responsible for handling thread safety.
*/
extern void
AudioServicesPlaySystemSoundWithCompletion(     SystemSoundID inSystemSoundID,
                                                void (^__nullable inCompletionBlock)(void))
                                                                        API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
                                                                        ;
                                                                
/*!
    @function       AudioServicesGetPropertyInfo
    @abstract       Get information about the size of an AudioServices property and whether it can
                    be set.
    @param          inPropertyID
                        a AudioServicesPropertyID constant.
    @param          inSpecifierSize
                        The size of the specifier data.
    @param          inSpecifier
                        A specifier is a buffer of data used as an input argument to some of the
                        properties.
    @param          outPropertyDataSize
                        The size in bytes of the current value of the property. In order to get the
                        property value, you will need a buffer of this size.
    @param          outWritable
                        Will be set to 1 if writable, or 0 if read only.
    @result         returns kAudioServicesNoError if successful.
*/                            
extern OSStatus 
AudioServicesGetPropertyInfo( AudioServicesPropertyID   inPropertyID,
                              UInt32                    inSpecifierSize,
                              const void * __nullable   inSpecifier,
                              UInt32 * __nullable       outPropertyDataSize,
                              Boolean * __nullable      outWritable)
                                                                    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
                                                                    ;

/*!
    @function       AudioServicesGetProperty
    @abstract       Retrieve the indicated property data
    @param          inPropertyID
                        a AudioServicesPropertyID constant.
    @param          inSpecifierSize
                        The size of the specifier data.
    @param          inSpecifier
                        A specifier is a buffer of data used as an input argument to some of the
                        properties.
    @param          ioPropertyDataSize
                        On input, the size of the outPropertyData buffer. On output the number of
                        bytes written to the buffer.
    @param          outPropertyData
                        The buffer in which to write the property data. May be NULL if caller only
                        wants ioPropertyDataSize to be filled with the amount that would have been
                        written.
    @result         returns kAudioServicesNoError if successful.
*/                        
extern OSStatus 
AudioServicesGetProperty(   AudioServicesPropertyID         inPropertyID,
                            UInt32                          inSpecifierSize,
                            const void * __nullable         inSpecifier,
                            UInt32 *                        ioPropertyDataSize,
                            void * __nullable               outPropertyData)
                                                                API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
                                                                ;

/*!
    @function       AudioServicesSetProperty
    @abstract       Set the indicated property data
    @param          inPropertyID
                        a AudioServicesPropertyID constant.
    @param          inSpecifierSize
                        The size of the specifier data.
    @param          inSpecifier
                        A specifier is a buffer of data used as an input argument to some of the
                        properties.
    @param          inPropertyDataSize
                        The size of the inPropertyData buffer.
    @param          inPropertyData
                        The buffer containing the property data.
    @result         returns kAudioServicesNoError if successful.
*/
extern OSStatus 
AudioServicesSetProperty(   AudioServicesPropertyID             inPropertyID,
                            UInt32                              inSpecifierSize,
                            const void * __nullable             inSpecifier,
                            UInt32                              inPropertyDataSize,
                            const void *                        inPropertyData)
                                                                API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
                                                                ;
                                                                
/*!
    This function will be deprecated in a future release. Use AudioServicesPlayAlertSoundWithCompletion instead.
 
    @function       AudioServicesPlayAlertSound
    @abstract       Play an Alert Sound
    @discussion     Play the provided SystemSoundID with AlertSound behavior.
    @param          inSystemSoundID
                        A SystemSoundID for the System Sound server to play. On the desktop you
                        can pass the kSystemSoundID_UserPreferredAlert constant to playback the alert sound 
                        selected by the user in System Preferences. On iOS there is no preferred user alert sound.
*/
extern void 
AudioServicesPlayAlertSound(SystemSoundID inSystemSoundID)                                          
                                                                API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
                                                                ;
                                                                
/*!
    This function will be deprecated in a future release. Use AudioServicesPlaySystemSoundWithCompletion instead.
 
    @function       AudioServicesPlaySystemSound
    @abstract       Play the sound designated by the provided SystemSoundID.
    @discussion     A SystemSoundID indicating the desired System Sound to be played.
    @param          inSystemSoundID
                        A SystemSoundID for the System Sound server to play.
*/
extern void 
AudioServicesPlaySystemSound(SystemSoundID inSystemSoundID)                                         
                                                                API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
                                                                ;
                                                                
/*!
    This function will be deprecated in a future release. Use AudioServicesPlayAlertSoundWithCompletion 
    or AudioServicesPlaySystemSoundWithCompletion instead.
 
    @function       AudioServicesAddSystemSoundCompletion
    @abstract       Call the provided Completion Routine when provided SystemSoundID
                    finishes playing.
    @discussion     Once set, the System Sound server will send a message to the System Sound client
                    indicating which SystemSoundID has finished playing.
    @param          inSystemSoundID
                        The SystemSoundID to associate with the provided completion
                        routine.
    @param          inRunLoop
                        A CFRunLoopRef indicating the desired run loop the completion routine should
                        be run on. Pass NULL to use the main run loop.
    @param          inRunLoopMode
                        A CFStringRef indicating the run loop mode for the runloop where the
                        completion routine will be executed. Pass NULL to use kCFRunLoopDefaultMode.
    @param          inCompletionRoutine
                        An AudioServicesSystemSoundCompletionProc to be called when the provided
                        SystemSoundID has completed playing in the server.
    @param          inClientData
                        A void* to pass client data to the completion routine.
*/
extern OSStatus 
AudioServicesAddSystemSoundCompletion(  SystemSoundID                                       inSystemSoundID,
                                    	CFRunLoopRef __nullable                             inRunLoop,
                                    	CFStringRef __nullable                              inRunLoopMode,
                                    	AudioServicesSystemSoundCompletionProc              inCompletionRoutine,
                                    	void * __nullable                                   inClientData)
                                                                    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
                                                                    ;

/*!
    This function will be deprecated in a future release. Use AudioServicesPlayAlertSoundWithCompletion
    or AudioServicesPlaySystemSoundWithCompletion instead.
 
    @function       AudioServicesRemoveSystemSoundCompletion
    @abstract       Disassociate any completion proc for the specified SystemSoundID
    @discussion     Tells the SystemSound client to remove any completion proc associated with the
                    provided SystemSoundID
    @param          inSystemSoundID
                        The SystemSoundID for which completion routines should be
                        removed.
*/
extern void 
AudioServicesRemoveSystemSoundCompletion(SystemSoundID inSystemSoundID)                             
                                                                    API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
                                                                    ;

CF_ASSUME_NONNULL_END
    
#ifdef __cplusplus
}
#endif

#endif /* AudioToolbox_AudioServices_h */
// ==========  AudioToolbox.framework/Headers/AudioFormat.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AudioFormat.h>)
/*!
	@file		AudioFormat.h
	@framework	AudioToolbox.framework
	@copyright	(c) 1985-2015 by Apple, Inc., all rights reserved.
    @abstract	API for finding things out about audio formats.
*/

#ifndef AudioToolbox_AudioFormat_h
#define AudioToolbox_AudioFormat_h

//=============================================================================
//	Includes
//=============================================================================

//	System Includes
#include <Availability.h>
#include <CoreAudioTypes/CoreAudioTypes.h>

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//	Types
//=============================================================================

/*!
    @typedef	AudioFormatPropertyID
    @abstract   A type for four char codes for property IDs
*/
typedef UInt32	AudioFormatPropertyID;

/*!
    @enum		PanningMode
    @abstract   Different panning algorithms.
    @constant   kPanningMode_SoundField
					Sound field panning algorithm
    @constant   kPanningMode_VectorBasedPanning
					Vector based panning algorithm
*/
typedef CF_ENUM(UInt32, AudioPanningMode) {
	kPanningMode_SoundField		 					= 3,
	kPanningMode_VectorBasedPanning					= 4
};

/*!
    @struct		AudioPanningInfo
    @abstract   This struct is for use with kAudioFormatProperty_PanningMatrix.
    @var        mPanningMode			the PanningMode to be used for the pan
    @var        mCoordinateFlags		the coordinates are specified as in the AudioChannelDescription struct in CoreAudioTypes.h
    @var        mCoordinates			the coordinates are specified as in the AudioChannelDescription struct in CoreAudioTypes.h
    @var        mGainScale				
					mGainScale is used to multiply the panning values.
					In typical usage you are applying an existing volume.
					value in 0 -> 1 (where 1 is unity gain) to the panned values.
					1 would give you panning at unity.
					0 would give you back a matrix of zeroes.
    @var        mOutputChannelMap				
					This is the channel map that is going to be used to determine channel volumes for this pan.
*/
struct AudioPanningInfo {
	AudioPanningMode			mPanningMode;
	UInt32						mCoordinateFlags;
	Float32						mCoordinates[3];	
	Float32						mGainScale;
	const AudioChannelLayout *	mOutputChannelMap;
};
typedef struct AudioPanningInfo AudioPanningInfo;

/*!
    @enum		AudioBalanceFadeType
    @abstract   used for mType field of AudioBalanceFade struct
    @constant   kAudioBalanceFadeType_MaxUnityGain
					the gain value never exceeds 1.0, the opposite channel fades out. 
					This can reduce overall loudness when the balance or fade is not in the center.
    @constant   kAudioBalanceFadeType_EqualPower
					The overall loudness remains constant, but gain can exceed 1.0.
					the gain value is 1.0 when the balance and fade are in the center.
					From there they can increase to +3dB (1.414) and decrease to -inf dB (0.0).
*/
typedef CF_ENUM(UInt32, AudioBalanceFadeType) {
	kAudioBalanceFadeType_MaxUnityGain = 0,
	kAudioBalanceFadeType_EqualPower = 1
};
	
/*!
    @struct		AudioBalanceFade
    @abstract   this struct is used with kAudioFormatProperty_BalanceFade
    @var        mLeftRightBalance 
					-1 is full left, 0 is center, +1 is full right
    @var        mBackFrontFade 
					-1 is full rear, 0 is center, +1 is full front
    @var        mType 
					an AudioBalanceFadeType constant
    @var        mChannelLayout 
					a pointer to an AudioChannelLayout
*/
struct AudioBalanceFade
{
	Float32						mLeftRightBalance;		// -1 is full left, 0 is center, +1 is full right
	Float32						mBackFrontFade;			// -1 is full rear, 0 is center, +1 is full front
	AudioBalanceFadeType		mType;					// max unity gain, or equal power.
	const AudioChannelLayout*	mChannelLayout;
};
typedef struct AudioBalanceFade AudioBalanceFade;

/*!
    @struct		AudioFormatInfo
    @abstract   this struct is used as a specifier for the kAudioFormatProperty_FormatList property
    @var        mASBD 
					an AudioStreamBasicDescription
    @var        mMagicCookie 
					a pointer to the decompression info for the data described in mASBD
    @var        mMagicCookieSize 
					the size in bytes of mMagicCookie
*/
struct AudioFormatInfo
{
	AudioStreamBasicDescription		mASBD;
	const void*						mMagicCookie;
	UInt32							mMagicCookieSize;
};
typedef struct AudioFormatInfo AudioFormatInfo;

/*!
    @struct		ExtendedAudioFormatInfo
    @abstract   this struct is used as a specifier for the kAudioFormatProperty_FormatList property
    @var        mASBD 
					an AudioStreamBasicDescription
    @var        mMagicCookie 
					a pointer to the decompression info for the data described in mASBD
    @var        mMagicCookieSize 
					the size in bytes of mMagicCookie
	@var  		mClassDescription
					an AudioClassDescription specifying the codec to be used in answering the question.
*/
struct ExtendedAudioFormatInfo
{
	AudioStreamBasicDescription		mASBD;
	const void* __nullable			mMagicCookie;
	UInt32							mMagicCookieSize;
	AudioClassDescription			mClassDescription;
};
typedef struct ExtendedAudioFormatInfo ExtendedAudioFormatInfo;

//=============================================================================
//	Properties - for various format structures.
//=============================================================================

/*!
    @enum		AudioFormatProperty constants
    @abstract   constants for use with AudioFormatGetPropertyInfo and AudioFormatGetProperty.
    @constant   kAudioFormatProperty_FormatInfo
					Retrieves general information about a format. The specifier is a
					magic cookie, or NULL.
					On input, the property value is an AudioStreamBasicDescription which 
					should have at least the mFormatID filled out. On output it will be filled out
					as much as possible given the information known about the format 
					and the contents of the magic cookie (if any is given).
					If multiple formats can be described by the AudioStreamBasicDescription and the associated magic cookie,
					this property will return the base level format.
    @constant   kAudioFormatProperty_FormatIsVBR
					Returns whether or not a format has a variable number of bytes per
					packet. The specifier is an AudioStreamBasicDescription describing
					the format to ask about. The value is a UInt32 where non-zero means
					the format is variable bytes per packet.
    @constant   kAudioFormatProperty_FormatIsExternallyFramed
					Returns whether or not a format requires external framing information,
					i.e. AudioStreamPacketDescriptions. 
					The specifier is an AudioStreamBasicDescription describing
					the format to ask about. The value is a UInt32 where non-zero means
					the format is externally framed. Any format which has variable byte sized packets
					requires AudioStreamPacketDescriptions.
    @constant   kAudioFormatProperty_FormatEmploysDependentPackets
					Returns whether or not a format is capable of combining independently
					decodable packets with dependent packets. The specifier is an
					AudioStreamBasicDescription describing the format to ask about.
					The value is a UInt32 where zero means that all packets in streams
					of the specified format are independently decodable and non-zero means
					that streams of the specified format may include dependent packets.
    @constant   kAudioFormatProperty_FormatIsEncrypted
                    Returns whether or not a format is encrypted. The specifier is a UInt32 format ID.
                    The value is a UInt32 where non-zero means the format is encrypted.
    @constant   kAudioFormatProperty_EncodeFormatIDs
					No specifier needed. Must be set to NULL.
					Returns an array of UInt32 format IDs for formats that are valid output formats 
					for a converter. 
    @constant   kAudioFormatProperty_DecodeFormatIDs
					No specifier needed. Must be set to NULL.
					Returns an array of UInt32 format IDs for formats that are valid input formats 
					for a converter. 
    @constant   kAudioFormatProperty_Encoders
					The specifier is the format that you are interested in, e.g. 'aac '
					Returns an array of AudioClassDescriptions for all installed encoders for the given format 
    @constant   kAudioFormatProperty_Decoders
					The specifier is the format that you are interested in, e.g. 'aac '
					Returns an array of AudioClassDescriptions for all installed decoders for the given format 
    @constant   kAudioFormatProperty_AvailableEncodeBitRates
					The specifier is a UInt32 format ID.
					The property value is an array of AudioValueRange describing all available bit rates.
    @constant   kAudioFormatProperty_AvailableEncodeSampleRates
					The specifier is a UInt32 format ID.
					The property value is an array of AudioValueRange describing all available sample rates.
    @constant   kAudioFormatProperty_AvailableEncodeChannelLayoutTags
					The specifier is an AudioStreamBasicDescription with at least the mFormatID 
					and mChannelsPerFrame fields set.
					The property value is an array of AudioChannelLayoutTags for the format and number of
					channels specified. If mChannelsPerFrame is zero, then all layouts supported by
					the format are returned.	
    @constant   kAudioFormatProperty_AvailableEncodeNumberChannels
					The specifier is an AudioStreamBasicDescription with at least the mFormatID field set.
					The property value is an array of UInt32 indicating the number of channels that can be encoded.
					A value of 0xFFFFFFFF indicates that any number of channels may be encoded. 
    @constant   kAudioFormatProperty_FormatName
					Returns a name for a given format. The specifier is an
					AudioStreamBasicDescription describing the format to ask about.
					The value is a CFStringRef. The caller is responsible for releasing the
					returned string. For some formats (eg, Linear PCM) you will get back a
					descriptive string (e.g. 16-bit, interleaved, etc...)
    @constant   kAudioFormatProperty_ASBDFromESDS
					Returns an audio stream description for a given ESDS. The specifier is an ESDS. 
					The value is a AudioStreamBasicDescription. If multiple formats can be described 
					by the ESDS this property will return the base level format.
    @constant   kAudioFormatProperty_ChannelLayoutFromESDS
					Returns an audio channel layout for a given ESDS. The specifier is an
					ESDS. The value is a AudioChannelLayout.
    @constant   kAudioFormatProperty_ASBDFromMPEGPacket
					Returns an audio stream description for a given MPEG Packet. The specifier is an MPEG Packet. 
					The value is a AudioStreamBasicDescription.					
    @constant   kAudioFormatProperty_FormatList
					Returns a list of AudioFormatListItem structs describing the audio formats contained within the compressed bit stream
					as described by the magic cookie. The specifier is an AudioFormatInfo struct. The mFormatID member of the 
					ASBD struct must filled in. Formats are returned in order from the most to least 'rich', with 
					channel count taking the highest precedence followed by sample rate. The kAudioFormatProperty_FormatList property 
					is the preferred method for discovering format information of the audio data. If the audio data can only be described
					by a single AudioFormatListItem, this property would be equivalent to using the kAudioFormatProperty_FormatInfo property,
					which should be used by the application as a fallback case, to ensure backward compatibility with existing systems 
					when kAudioFormatProperty_FormatList is not present on the running system.
    @constant   kAudioFormatProperty_OutputFormatList
					Returns a list of AudioFormatListItem structs describing the audio formats which may be obtained by decoding the format
					described by the specifier.
					The specifier is an AudioFormatInfo struct. At a minimum formatID member of the ASBD struct must filled in. Other fields
					may be filled in. If there is no magic cookie, then the number of channels and sample rate should be filled in. 
	@constant	kAudioFormatProperty_FirstPlayableFormatFromList
					The specifier is a list of 1 or more AudioFormatListItem. Generally it is the list of these items returned from kAudioFormatProperty_FormatList. The property value retrieved is an UInt32 that specifies an index into that list. The list that the caller provides is generally sorted with the first item as the best format (most number of channels, highest sample rate), and the returned index represents the first item in that list that can be played by the system. 
					Thus, the property is typically used to determine the best playable format for a given (layered) audio stream
	@constant   kAudioFormatProperty_ValidateChannelLayout
					The specifier is an AudioChannelLayout. The property value and size are not used and must be set to NULL.
					This property validates an AudioChannelLayout. This is useful if the layout has come from an untrusted source such as a file.
					It returns noErr if the AudioChannelLayout is OK, kAudio_ParamError if there is a structural problem with the layout,
					or kAudioFormatUnknownFormatError for unrecognized layout tags or channel labels.
	@constant   kAudioFormatProperty_ChannelLayoutForTag
					Returns the channel descriptions for a standard channel layout.
					The specifier is a AudioChannelLayoutTag (the mChannelLayoutTag field 
					of the AudioChannelLayout struct) containing the layout constant. 
					The value is an AudioChannelLayout structure. In typical use a AudioChannelLayout
					can be valid with just a defined AudioChannelLayoutTag (ie, those layouts
					have predefined speaker locations and orderings).
					Returns an error if the tag is kAudioChannelLayoutTag_UseChannelBitmap 
    @constant   kAudioFormatProperty_TagForChannelLayout
					Returns an AudioChannelLayoutTag for a layout, if there is one.
					The specifier is an AudioChannelLayout containing the layout description.
					The value is an AudioChannelLayoutTag.
					This can be used to reduce a layout specified by kAudioChannelLayoutTag_UseChannelDescriptions
					or kAudioChannelLayoutTag_UseChannelBitmap to a known AudioChannelLayoutTag.
    @constant   kAudioFormatProperty_ChannelLayoutForBitmap
					Returns the channel descriptions for a standard channel layout.
					The specifier is a UInt32 (the mChannelBitmap field 
					of the AudioChannelLayout struct) containing the layout bitmap. The value
					is an AudioChannelLayout structure. In some uses, an AudioChannelLayout can be 
					valid with the layoutTag set to "use bitmap" and the bitmap set appropriately.
    @constant   kAudioFormatProperty_BitmapForLayoutTag
					Returns a bitmap for an AudioChannelLayoutTag, if there is one.
					The specifier is a AudioChannelLayoutTag  containing the layout tag.
					The value is an UInt32 bitmap. The bits are as defined in CoreAudioTypes.h.
					To go in the other direction, i.e. get a layout tag for a bitmap, 
					use kAudioFormatProperty_TagForChannelLayout where your layout tag 
					is kAudioChannelLayoutTag_UseChannelBitmap and the bitmap is filled in.
    @constant   kAudioFormatProperty_ChannelLayoutName
					Returns the a name for a particular channel layout. The specifier is
					an AudioChannelLayout containing the layout description. The value
					is a CFStringRef. The caller is responsible for releasing the
					returned string.
    @constant   kAudioFormatProperty_ChannelLayoutSimpleName
					Returns the a simpler name for a channel layout than does kAudioFormatProperty_ChannelLayoutName. 
					It omits the channel labels from the name. The specifier is
					an AudioChannelLayout containing the layout description. The value
					is a CFStringRef. The caller is responsible for releasing the
					returned string.
    @constant   kAudioFormatProperty_ChannelName
					Returns the name for a particular channel. The specifier is an
					AudioChannelDescription which has the mChannelLabel field set. The value
					is a CFStringRef. The caller is responsible for releasing the
					returned string.
    @constant   kAudioFormatProperty_ChannelShortName
					Returns an abbreviated name for a particular channel. The specifier is an
					AudioChannelDescription which has the mChannelLabel field set. The value
					is a CFStringRef. The caller is responsible for releasing the
					returned string.
    @constant   kAudioFormatProperty_MatrixMixMap
					Returns a matrix of scaling coefficients for converting audio from one channel map 
					to another in a standard way, if one is known. Otherwise an error is returned.
					The specifier is an array of two pointers to AudioChannelLayout structures. 
					The first points to the input layout, the second to the output layout.
					The value is a two dimensional array of Float32 where the first dimension (rows) 
					is the input channel and the second dimension (columns) is the output channel. 
    @constant   kAudioFormatProperty_ChannelMap
					Returns an array of SInt32 for reordering input channels.
					The specifier is an array of two pointers to AudioChannelLayout structures. 
					The first points to the input layout, the second to the output layout.
					The length of the output array is equal to the number of output channels.
    @constant   kAudioFormatProperty_NumberOfChannelsForLayout
					This is a general call for parsing a AudioChannelLayout provided as the specifier,
					to determine the number of valid channels that are represented. So, if the
					LayoutTag is specified, it returns the number of channels for that layout. If 
					the bitmap is specified, it returns the number of channels represented by that bitmap.
					If the layout tag is 'kAudioChannelLayoutTag_UseChannelDescriptions' it returns
						the number of channel descriptions.
    @constant   kAudioFormatProperty_AreChannelLayoutsEquivalent
					Returns a UInt32 which is 1 if two layouts are equivalent and 0 if they are not equivalent.
					In order to be equivalent, the layouts must describe the same channels in the same order.
					Whether the layout is represented by a bitmap, channel descriptions or a channel layout tag is not significant.
					The channel coordinates are only significant if the channel label is kAudioChannelLabel_UseCoordinates.
					The specifier is an array of two pointers to AudioChannelLayout structures. 
					The value is a pointer to the UInt32 result.
    @constant   kAudioFormatProperty_ChannelLayoutHash
					Returns a UInt32 which represents the hash of the provided channel layout.
					The specifier is a pointer to an AudioChannelLayout structure.
					The value is a pointer to the UInt32 result.
    @constant   kAudioFormatProperty_TagsForNumberOfChannels
					returns an array of AudioChannelLayoutTags for the number of channels specified.
					The specifier is a UInt32 number of channels. 
    @constant   kAudioFormatProperty_PanningMatrix
					This call will pass in an AudioPanningInfo struct that specifies one of the
					kPanningMode_ constants for the panning algorithm and an AudioChannelLayout
					to describe the destination channel layout. As in kAudioFormatProperty_MatrixMixMap
					the return value is an array of Float32 values of the number of channels
						represented by this specified channel layout. It is presumed that the source 
					being panned is mono (thus for a quad channel layout, 4 Float32 values are returned).
					The intention of this API is to provide support for panning operations that are
					strictly manipulating the respective volumes of the channels. Thus, more
					complex panners (like HRTF, distance filtering etc,) will not be represented
						by this API. The resultant volume scalars can then be applied to a mixer
					or some other processing code to adapt the individual volumes of the mixed
					output.
					The volume values will typically be presented within a 0->1 range (where 1 is unity gain)
					For stereo formats, vector based panning is equivalent to the equal-power pan mode.
    @constant   kAudioFormatProperty_BalanceFade
					get an array of coefficients for applying left/right balance and front/back fade.
					The specifier is an AudioBalanceFade struct. 
					the return value is an array of Float32 values of the number of channels
						represented by this specified channel layout.  
					The volume values will typically be presented within a 0->1 range (where 1 is unity gain)
    @constant   kAudioFormatProperty_ID3TagSize
					Returns a UInt32 indicating the ID3 tag size. 
					The specifier must begin with the ID3 tag header and be at least 10 bytes in length
    @constant   kAudioFormatProperty_ID3TagToDictionary
					Returns a CFDictionary containing key/value pairs for the frames in the ID3 tag
					The specifier is the entire ID3 tag
					Caller must call CFRelease for the returned dictionary
					
*/
CF_ENUM(AudioFormatPropertyID)
{
//=============================================================================
//	The following properties are concerned with the AudioStreamBasicDescription
//=============================================================================
	kAudioFormatProperty_FormatInfo						= 'fmti',
	kAudioFormatProperty_FormatName						= 'fnam',
	kAudioFormatProperty_EncodeFormatIDs				= 'acof',
	kAudioFormatProperty_DecodeFormatIDs				= 'acif',
	kAudioFormatProperty_FormatList						= 'flst',
    kAudioFormatProperty_ASBDFromESDS                   = 'essd',
    kAudioFormatProperty_ChannelLayoutFromESDS          = 'escl',
	kAudioFormatProperty_OutputFormatList				= 'ofls',
	kAudioFormatProperty_FirstPlayableFormatFromList	= 'fpfl',
	kAudioFormatProperty_FormatIsVBR					= 'fvbr',	
	kAudioFormatProperty_FormatIsExternallyFramed		= 'fexf',
	kAudioFormatProperty_FormatEmploysDependentPackets  = 'fdep',
	kAudioFormatProperty_FormatIsEncrypted				= 'cryp',
	kAudioFormatProperty_Encoders						= 'aven',	
	kAudioFormatProperty_Decoders						= 'avde',
	kAudioFormatProperty_AvailableEncodeBitRates		= 'aebr',
	kAudioFormatProperty_AvailableEncodeSampleRates		= 'aesr',
	kAudioFormatProperty_AvailableEncodeChannelLayoutTags = 'aecl',
	kAudioFormatProperty_AvailableEncodeNumberChannels		= 'avnc',
	kAudioFormatProperty_ASBDFromMPEGPacket				= 'admp',


//=============================================================================
//	The following properties concern the AudioChannelLayout struct (speaker layouts)
//=============================================================================
	kAudioFormatProperty_BitmapForLayoutTag				= 'bmtg',
	kAudioFormatProperty_MatrixMixMap					= 'mmap',
    kAudioFormatProperty_ChannelMap						= 'chmp',
	kAudioFormatProperty_NumberOfChannelsForLayout		= 'nchm',
	kAudioFormatProperty_AreChannelLayoutsEquivalent	= 'cheq',
    kAudioFormatProperty_ChannelLayoutHash              = 'chha',
	kAudioFormatProperty_ValidateChannelLayout			= 'vacl',
	kAudioFormatProperty_ChannelLayoutForTag			= 'cmpl',
	kAudioFormatProperty_TagForChannelLayout			= 'cmpt',
	kAudioFormatProperty_ChannelLayoutName				= 'lonm',
	kAudioFormatProperty_ChannelLayoutSimpleName		= 'lsnm',
	kAudioFormatProperty_ChannelLayoutForBitmap			= 'cmpb',
	kAudioFormatProperty_ChannelName					= 'cnam',
	kAudioFormatProperty_ChannelShortName				= 'csnm',

	kAudioFormatProperty_TagsForNumberOfChannels		= 'tagc',				
	kAudioFormatProperty_PanningMatrix					= 'panm',
	kAudioFormatProperty_BalanceFade					= 'balf',

//=============================================================================
//	The following properties concern the ID3 Tags
//=============================================================================

	kAudioFormatProperty_ID3TagSize						= 'id3s',
	kAudioFormatProperty_ID3TagToDictionary				= 'id3d'
};

#if TARGET_OS_IPHONE

CF_ENUM(AudioFormatPropertyID) {
	kAudioFormatProperty_HardwareCodecCapabilities		= 'hwcc',
} __attribute__((deprecated));

/*!
	@enum           AudioCodecComponentType
 
	@discussion     Collection of audio codec component types.
					(On Mac OS X these declarations are in AudioToolbox/AudioCodec.h).
 
	@constant		kAudioDecoderComponentType
					A codec that translates data in some other format into linear PCM.
					The component subtype specifies the format ID of the other format.
	@constant		kAudioEncoderComponentType
					A codec that translates linear PCM data into some other format
					The component subtype specifies the format ID of the other format
*/
CF_ENUM(UInt32)
{
	kAudioDecoderComponentType								= 'adec',	
	kAudioEncoderComponentType								= 'aenc',	
};

/*!
	@enum			AudioCodecComponentManufacturer

	@discussion		Audio codec component manufacturer codes. On iPhoneOS, a codec's
					manufacturer can be used to distinguish between hardware and
					software codecs.

	@constant		kAppleSoftwareAudioCodecManufacturer
					Apple software audio codecs.
	@constant		kAppleHardwareAudioCodecManufacturer
					Apple hardware audio codecs.
*/
CF_ENUM(UInt32)
{
	kAppleSoftwareAudioCodecManufacturer					= 'appl',
	kAppleHardwareAudioCodecManufacturer					= 'aphw'
};

#endif


//=============================================================================
//	Routines
//=============================================================================

/*!
    @function	AudioFormatGetPropertyInfo
    @abstract   Retrieve information about the given property
    @param      inPropertyID		an AudioFormatPropertyID constant.
    @param      inSpecifierSize		The size of the specifier data.
    @param      inSpecifier			A specifier is a buffer of data used as an input argument to some of the properties.
    @param      outPropertyDataSize	The size in bytes of the current value of the property. In order to get the property value,
									you will need a buffer of this size.
    @result     returns noErr if successful.
*/
extern OSStatus
AudioFormatGetPropertyInfo(	AudioFormatPropertyID	inPropertyID,
							UInt32					inSpecifierSize,
							const void * __nullable	inSpecifier,
							UInt32 *				outPropertyDataSize)	API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function	AudioFormatGetProperty
    @abstract   Retrieve the indicated property data
    @param      inPropertyID		an AudioFormatPropertyID constant.
    @param      inSpecifierSize		The size of the specifier data.
    @param      inSpecifier			A specifier is a buffer of data used as an input argument to some of the properties.
    @param      ioPropertyDataSize	on input the size of the outPropertyData buffer. On output the number of bytes written to the buffer.
    @param      outPropertyData		the buffer in which to write the property data. If outPropertyData is NULL and ioPropertyDataSize is
									not, the amount that would have been written will be reported.
    @result     returns noErr if successful.
*/
extern OSStatus
AudioFormatGetProperty(	AudioFormatPropertyID	inPropertyID,
						UInt32					inSpecifierSize,
						const void * __nullable	inSpecifier,
						UInt32 * __nullable		ioPropertyDataSize,
						void * __nullable		outPropertyData)			API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));


//-----------------------------------------------------------------------------
//  AudioFormat Error Codes
//-----------------------------------------------------------------------------

CF_ENUM(OSStatus)
{
        kAudioFormatUnspecifiedError						= 'what',	// 0x77686174, 2003329396
        kAudioFormatUnsupportedPropertyError 				= 'prop',	// 0x70726F70, 1886547824
        kAudioFormatBadPropertySizeError 					= '!siz',	// 0x2173697A, 561211770
        kAudioFormatBadSpecifierSizeError 					= '!spc',	// 0x21737063, 561213539
        kAudioFormatUnsupportedDataFormatError 				= 'fmt?',	// 0x666D743F, 1718449215
        kAudioFormatUnknownFormatError 						= '!fmt'	// 0x21666D74, 560360820
};


#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioFormat_h
#else
#include <AudioToolboxCore/AudioFormat.h>
#endif
// ==========  AudioToolbox.framework/Headers/CAFFile.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/CAFFile.h>)
/*!
	@file		CAFFile.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2004-2015 by Apple, Inc., all rights reserved.
	@abstract	The data structures contained within a CAF (Core Audio Format) file.
*/

#ifndef AudioToolbox_CAFFile_h
#define AudioToolbox_CAFFile_h

#include <CoreAudioTypes/CoreAudioTypes.h>


#define ATTRIBUTE_PACKED __attribute__((__packed__))


// In a CAF File all of these types' byte order is big endian.
// When reading or writing these values the program will need to flip byte order to native endian

// CAF File Header
CF_ENUM(UInt32) {
	kCAF_FileType				= 'caff',
	kCAF_FileVersion_Initial	= 1
};

// CAF Chunk Types	
CF_ENUM(UInt32) {
	kCAF_StreamDescriptionChunkID   = 'desc',
	kCAF_AudioDataChunkID			= 'data',
	kCAF_ChannelLayoutChunkID		= 'chan',
	kCAF_FillerChunkID				= 'free',
	kCAF_MarkerChunkID				= 'mark',
	kCAF_RegionChunkID				= 'regn',
	kCAF_InstrumentChunkID			= 'inst',
	kCAF_MagicCookieID				= 'kuki',
	kCAF_InfoStringsChunkID			= 'info',
	kCAF_EditCommentsChunkID		= 'edct',
	kCAF_PacketTableChunkID			= 'pakt',
	kCAF_StringsChunkID				= 'strg',
	kCAF_UUIDChunkID				= 'uuid',
	kCAF_PeakChunkID				= 'peak',
	kCAF_OverviewChunkID			= 'ovvw',
	kCAF_MIDIChunkID				= 'midi',
	kCAF_UMIDChunkID				= 'umid',
	kCAF_FormatListID				= 'ldsc',
	kCAF_iXMLChunkID				= 'iXML'
};


struct CAFFileHeader
{
        UInt32          mFileType;			// 'caff'
		UInt16			mFileVersion;		//initial revision set to 1
		UInt16			mFileFlags;			//initial revision set to 0
} ATTRIBUTE_PACKED;
typedef struct CAFFileHeader CAFFileHeader;


struct CAFChunkHeader
{
        UInt32          mChunkType; // four char code
        SInt64          mChunkSize;  // size in bytes of the chunk data (not including this header).
									// mChunkSize is SInt64 not UInt64 because negative values for 
									// the data size can have a special meaning
} ATTRIBUTE_PACKED;

typedef struct CAFChunkHeader CAFChunkHeader;

struct CAF_UUID_ChunkHeader
{
        CAFChunkHeader   mHeader;
        UInt8            mUUID[16];
} ATTRIBUTE_PACKED;
typedef struct CAF_UUID_ChunkHeader CAF_UUID_ChunkHeader;


// these are the flags if the format ID is 'lpcm'
// <CoreAudioTypes/CoreAudioTypes.h> declares some of the format constants 
// that can be used as Data Formats in a CAF file
typedef CF_OPTIONS(UInt32, CAFFormatFlags)
{
    kCAFLinearPCMFormatFlagIsFloat				= (1L << 0),
    kCAFLinearPCMFormatFlagIsLittleEndian		= (1L << 1)
};

// Every file MUST have this chunk. It MUST be the first chunk in the file
struct CAFAudioDescription
{
        Float64 mSampleRate;
        UInt32  mFormatID;
        CAFFormatFlags  mFormatFlags;
        UInt32  mBytesPerPacket;
        UInt32  mFramesPerPacket;
        UInt32  mChannelsPerFrame;
        UInt32  mBitsPerChannel;
} ATTRIBUTE_PACKED;
typedef struct CAFAudioDescription  CAFAudioDescription;


// 'ldsc'  format list chunk.
// for data formats like AAC SBR which can be decompressed to multiple formats, this chunk contains a list of
// CAFAudioFormatListItem describing those formats. The list is ordered from best to worst by number of channels 
// and sample rate in that order. mChannelLayoutTag is an AudioChannelLayoutTag as defined in CoreAudioTypes.h

struct CAFAudioFormatListItem
{
	CAFAudioDescription mFormat;
	UInt32 				mChannelLayoutTag;
} ATTRIBUTE_PACKED;

// 'chan'  Optional chunk.
// struct AudioChannelLayout  as defined in CoreAudioTypes.h.

// 'free'
// this is a padding chunk for reserving space in the file. content is meaningless.

// 'kuki'
// this is the magic cookie chunk. bag of bytes.

// 'data'    Every file MUST have this chunk.
// actual audio data can be any format as described by the 'asbd' chunk.

// if mChunkSize is < 0 then this is the last chunk in the file and the actual length 
// should be determined from the file size. 
// The motivation for this is to allow writing the files without seeking to update size fields after every 
// write in order to keep the file legal.
// The program can put a -1 in the mChunkSize field and 
// update it only once at the end of recording. 
// If the program were to crash during recording then the file is still well defined.

// 'pakt' Required if either/or mBytesPerPacket or mFramesPerPacket in the Format Description are zero
// For formats that are packetized and have variable sized packets. 
// The table is stored as an array of one or two variable length integers. 
// (a) size in bytes of the data of a given packet.
// (b) number of frames in a given packet.
// These sizes are encoded as variable length integers

// The packet description entries are either one or two values depending on the format.
// There are three possibilities
// (1)
// If the format has variable bytes per packets (desc.mBytesPerPacket == 0) and constant frames per packet
// (desc.mFramesPerPacket != 0) then the packet table contains single entries representing the bytes in a given packet
// (2)
// If the format is a constant bit rate (desc.mBytesPerPacket != 0) but variable frames per packet
// (desc.mFramesPerPacket == 0) then the packet table entries contains single entries 
// representing the number of frames in a given packet
// (3)
// If the format has variable frames per packet (asbd.mFramesPerPacket == 0) and variable bytes per packet
// (desc.mBytesPerPacket == 0) then the packet table entries are a duple of two values. The first value
// is the number of bytes in a given packet, the second value is the number of frames in a given packet

struct CAFPacketTableHeader
{
        SInt64  mNumberPackets;
        SInt64  mNumberValidFrames;
        SInt32  mPrimingFrames;
        SInt32  mRemainderFrames;
		
		UInt8   mPacketDescriptions[1]; // this is a variable length array of mNumberPackets elements
} ATTRIBUTE_PACKED;
typedef struct CAFPacketTableHeader CAFPacketTableHeader;

struct CAFDataChunk
{
		UInt32 mEditCount;
		UInt8 mData[1]; // this is a variable length data field based off the size of the data chunk
} ATTRIBUTE_PACKED;
typedef struct CAFDataChunk CAFDataChunk;

// markers types
CF_ENUM(UInt32) {
	kCAFMarkerType_Generic					= 0,
	kCAFMarkerType_ProgramStart				= 'pbeg',
	kCAFMarkerType_ProgramEnd				= 'pend',
	kCAFMarkerType_TrackStart				= 'tbeg',
	kCAFMarkerType_TrackEnd					= 'tend',
	kCAFMarkerType_Index					= 'indx',
	kCAFMarkerType_RegionStart				= 'rbeg',
	kCAFMarkerType_RegionEnd				= 'rend',
	kCAFMarkerType_RegionSyncPoint			= 'rsyc',
	kCAFMarkerType_SelectionStart			= 'sbeg',
	kCAFMarkerType_SelectionEnd				= 'send',
	kCAFMarkerType_EditSourceBegin			= 'cbeg',
	kCAFMarkerType_EditSourceEnd			= 'cend',
	kCAFMarkerType_EditDestinationBegin		= 'dbeg',
	kCAFMarkerType_EditDestinationEnd		= 'dend',
	kCAFMarkerType_SustainLoopStart			= 'slbg',
	kCAFMarkerType_SustainLoopEnd			= 'slen',
	kCAFMarkerType_ReleaseLoopStart			= 'rlbg',
	kCAFMarkerType_ReleaseLoopEnd			= 'rlen',
	kCAFMarkerType_SavedPlayPosition		= 'sply',
	kCAFMarkerType_Tempo					= 'tmpo',
	kCAFMarkerType_TimeSignature			= 'tsig',
	kCAFMarkerType_KeySignature				= 'ksig'
};

CF_ENUM(UInt32)
{
    kCAF_SMPTE_TimeTypeNone		 = 0,
    kCAF_SMPTE_TimeType24        = 1,
    kCAF_SMPTE_TimeType25        = 2,
    kCAF_SMPTE_TimeType30Drop    = 3,
    kCAF_SMPTE_TimeType30        = 4,
    kCAF_SMPTE_TimeType2997      = 5,
    kCAF_SMPTE_TimeType2997Drop  = 6,
    kCAF_SMPTE_TimeType60        = 7,
    kCAF_SMPTE_TimeType5994      = 8,
    kCAF_SMPTE_TimeType60Drop    = 9,
    kCAF_SMPTE_TimeType5994Drop  = 10,
    kCAF_SMPTE_TimeType50        = 11,
    kCAF_SMPTE_TimeType2398      = 12
};

struct CAF_SMPTE_Time
{
	SInt8 mHours;
	SInt8 mMinutes;
	SInt8 mSeconds;
	SInt8 mFrames;
	UInt32 mSubFrameSampleOffset;
} ATTRIBUTE_PACKED;
typedef struct CAF_SMPTE_Time CAF_SMPTE_Time;

struct CAFMarker
{
        UInt32               mType;
        Float64              mFramePosition;
        UInt32               mMarkerID;
        CAF_SMPTE_Time       mSMPTETime;
        UInt32               mChannel;
} ATTRIBUTE_PACKED;
typedef struct CAFMarker CAFMarker;

struct CAFMarkerChunk
{
        UInt32          mSMPTE_TimeType;
        UInt32          mNumberMarkers;
        CAFMarker       mMarkers[1]; // this is a variable length array of mNumberMarkers elements
} ATTRIBUTE_PACKED;
typedef struct CAFMarkerChunk CAFMarkerChunk;

#define kCAFMarkerChunkHdrSize		offsetof(CAFMarkerChunk, mMarkers)

typedef CF_OPTIONS(UInt32, CAFRegionFlags) {
	kCAFRegionFlag_LoopEnable = 1,
	kCAFRegionFlag_PlayForward = 2,
	kCAFRegionFlag_PlayBackward = 4
};

struct CAFRegion
{
        UInt32          mRegionID;               
        CAFRegionFlags  mFlags;
        UInt32          mNumberMarkers;
        CAFMarker       mMarkers[1]; // this is a variable length array of mNumberMarkers elements
} ATTRIBUTE_PACKED;
typedef struct CAFRegion CAFRegion;

/* because AudioFileRegions are variable length, you cannot access them as an array. Use NextAudioFileRegion to walk the list. */
#define NextCAFRegion(inCAFRegionPtr) \
        ((CAFRegion*)((char*)(inCAFRegionPtr) + offsetof(CAFRegion, mMarkers) + ((inCAFRegionPtr)->mNumberMarkers)*sizeof(CAFMarker)))


struct CAFRegionChunk
{
        UInt32          mSMPTE_TimeType;
        UInt32          mNumberRegions;
        CAFRegion       mRegions[1];  // this is a variable length array of mNumberRegions elements
} ATTRIBUTE_PACKED;
typedef struct CAFRegionChunk CAFRegionChunk;

#define kCAFRegionChunkHdrSize		offsetof(CAFRegionChunk, mRegions)

struct CAFInstrumentChunk
{
        Float32         mBaseNote;
        UInt8           mMIDILowNote;
        UInt8           mMIDIHighNote;
        UInt8           mMIDILowVelocity;
        UInt8           mMIDIHighVelocity;
        Float32         mdBGain;
        UInt32          mStartRegionID;               
        UInt32          mSustainRegionID;               
        UInt32          mReleaseRegionID;               
        UInt32          mInstrumentID;
} ATTRIBUTE_PACKED;
typedef struct CAFInstrumentChunk CAFInstrumentChunk;



struct CAFStringID {
        UInt32         mStringID;
        SInt64         mStringStartByteOffset;
} ATTRIBUTE_PACKED;
typedef struct CAFStringID CAFStringID;

struct CAFStrings
{
        UInt32         mNumEntries;
		CAFStringID    mStringsIDs[1]; // this is a variable length array of mNumEntries elements
// this struct is only fictionally described due to the variable length fields
//		UInt8          mStrings[ variable num elements ]; // null terminated UTF8 strings
} ATTRIBUTE_PACKED;
typedef struct CAFStrings CAFStrings;


struct CAFInfoStrings
{
        UInt32		mNumEntries;

// These are only fictionally defined in the struct due to the variable length fields.
//      struct {
//              UInt8   mKey[ variable num elements ];			// null terminated UTF8 string
//              UInt8   mValue[ variable num elements ];		// null terminated UTF8 string
//      } mStrings[ variable num elements ];
} ATTRIBUTE_PACKED;
typedef struct CAFInfoStrings CAFInfoStrings;


struct CAFPositionPeak
{
        Float32       mValue;
        UInt64        mFrameNumber;
} ATTRIBUTE_PACKED;
typedef struct CAFPositionPeak CAFPositionPeak;

struct CAFPeakChunk
{
	UInt32 mEditCount;
	CAFPositionPeak mPeaks[1]; // this is a variable length array of peak elements (calculated from the size of the chunk)
} ATTRIBUTE_PACKED;
typedef struct CAFPeakChunk CAFPeakChunk;


struct CAFOverviewSample
{
        SInt16       mMinValue;
        SInt16       mMaxValue;
} ATTRIBUTE_PACKED;
typedef struct CAFOverviewSample CAFOverviewSample;

struct CAFOverviewChunk
{
        UInt32                   mEditCount;
        UInt32                   mNumFramesPerOVWSample;
        CAFOverviewSample        mData[1]; // data is of variable size, calculated from the sizeo of the chunk.
} ATTRIBUTE_PACKED;
typedef struct CAFOverviewChunk CAFOverviewChunk;

struct CAFUMIDChunk
{
	UInt8 mBytes[64];
} ATTRIBUTE_PACKED;
typedef struct CAFUMIDChunk CAFUMIDChunk;


////////////////////////////////////////////////////////////////////////////////////////////////

#endif // AudioToolbox_CAFFile_h
#else
#include <AudioToolboxCore/CAFFile.h>
#endif
// ==========  AudioToolbox.framework/Headers/AudioUnit.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AudioUnit.h>)
/*!
	@file		AudioUnit.h
 	@framework	AudioToolbox.framework
 	@copyright	(c) 2002-2015 Apple, Inc. All rights reserved.

	@brief		Former umbrella header for AudioUnit framework; now part of AudioToolbox.
*/

#ifndef _AudioToolbox_AudioUnit_h
#define _AudioToolbox_AudioUnit_h

#include <TargetConditionals.h>
#ifndef AUDIO_UNIT_VERSION
#define AUDIO_UNIT_VERSION 1070
#endif

#include <AudioToolbox/AudioComponent.h>
#include <AudioToolbox/AUComponent.h>
#include <AudioToolbox/AudioOutputUnit.h>
#include <AudioToolbox/AudioUnitProperties.h>
#include <AudioToolbox/AudioUnitParameters.h>
#include <AudioToolbox/MusicDevice.h>

#ifdef __OBJC2__
	#import <AudioToolbox/AUAudioUnit.h>
	#import <AudioToolbox/AUAudioUnitImplementation.h>
	#import <AudioToolbox/AUParameters.h>
#endif

#if !TARGET_OS_IPHONE
	#include <AudioToolbox/AudioCodec.h>
#endif

#endif /* _AudioToolbox_AudioUnit_h */
#else
#include <AudioToolboxCore/AudioUnit.h>
#endif
// ==========  AudioToolbox.framework/Headers/CAShow.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/CAShow.h>)
/*!
	@file		CAShow.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2002-2018 by Apple, Inc., all rights reserved.
	@abstract	Interfaces to log the internal state of various AudioToolbox objects.
*/

#ifndef AudioToolbox_CAShow_h
#define AudioToolbox_CAShow_h

#include <Availability.h>
#include <os/base.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Print the internal state of an object to os_log.
OS_EXPORT void CAShow(void *inObject) 
											API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// Print the internal state of an object to the supplied FILE*.
OS_EXPORT void CAShowFile(void *inObject, FILE *inFile)
											API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

#ifdef __cplusplus
}
#endif

#endif /* AudioToolbox_CAShow_h */
#else
#include <AudioToolboxCore/CAShow.h>
#endif
// ==========  AudioToolbox.framework/Headers/AudioToolbox.h
/*!
	@file		AudioToolbox.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2002-2018 by Apple, Inc., all rights reserved.
	@abstract	Umbrella header for AudioToolbox framework.
*/


#ifndef AudioToolbox_AudioToolbox_h
#define AudioToolbox_AudioToolbox_h

#define AUDIO_TOOLBOX_VERSION 1060

#include <Availability.h>
#include <TargetConditionals.h>

#include <AudioToolbox/AudioCodec.h>
#include <AudioToolbox/AUComponent.h>
#include <AudioToolbox/AUGraph.h>
#include <AudioToolbox/AudioComponent.h>
#include <AudioToolbox/AudioConverter.h>
#include <AudioToolbox/AudioFile.h>
#include <AudioToolbox/AudioFileStream.h>
#include <AudioToolbox/AudioFormat.h>
#include <AudioToolbox/AudioOutputUnit.h>
#include <AudioToolbox/AudioQueue.h>
#include <AudioToolbox/AudioServices.h>
#include <AudioToolbox/AudioUnitParameters.h>
#include <AudioToolbox/AudioUnitProperties.h>
#include <AudioToolbox/CAFFile.h>
#include <AudioToolbox/CAShow.h>
#include <AudioToolbox/ExtendedAudioFile.h>
#include <AudioToolbox/MusicDevice.h>
#include <AudioToolbox/MusicPlayer.h>

#if !TARGET_OS_IPHONE
	// OS X only
	#include <AudioToolbox/AudioFileComponent.h>
	#include <AudioToolbox/AudioUnitUtilities.h>
	#include <AudioToolbox/AUMIDIController.h>
	#include <AudioToolbox/CoreAudioClock.h>
#endif

#ifdef __OBJC2__
	// iOS (all architectures), OS X 64-bit only
	#import <AudioToolbox/AUAudioUnit.h>
	#import <AudioToolbox/AUAudioUnitImplementation.h>
	#import <AudioToolbox/AUParameters.h>
#endif

/*!	@mainpage

	@section section_intro			Introduction

	The AudioUnit framework contains a set of related API's dealing with:
	
	- Audio components, providing various types of plug-in functionality.
	- Audio Units, audio processing plug-ins.
	- Audio codecs, plug-ins which decode and encode compressed audio.
	
	@section section_component		Audio Components
	
	See AudioComponent.h for API's to find and use audio components, as well as information
	on how audio components are packaged and built.
	
	In addition, `<AVFoundation/AVAudioUnitComponent.h>` provides a higher-level interface for
	finding audio unit components.
	
	See @ref AUExtensionPackaging and AUAudioUnitImplementation.h for information on creating
	version 3 audio units.
	
	@section section_audiounit		Audio Units
*/

#include <stdio.h>

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

#if !TARGET_OS_IPHONE
// this will return the name of a sound bank from a sound bank file
// the name should be released by the caller
struct FSRef;
OS_EXPORT OSStatus GetNameFromSoundBank (const struct FSRef *inSoundBankRef, CFStringRef __nullable * __nonnull outName)
											API_DEPRECATED("no longer supported", macos(10.2, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
#endif

/*!
    @function		CopyNameFromSoundBank
	 
    @discussion		This will return the name of a sound bank from a DLS or SF2 bank.
					The name should be released by the caller.

    @param			inURL
						The URL for the sound bank.
    @param			outName
						A pointer to a CFStringRef to be created and returned by the function.
    @result			returns noErr if successful.
*/

OS_EXPORT OSStatus
CopyNameFromSoundBank (CFURLRef inURL, CFStringRef __nullable * __nonnull outName)
											API_AVAILABLE(macos(10.5), ios(7.0), watchos(2.0), tvos(9.0));

/*!
    @function		CopyInstrumentInfoFromSoundBank
	 
    @discussion		This will return a CFArray of CFDictionaries, one per instrument found in the DLS or SF2 bank.
					Each dictionary will contain four items accessed via CFStringRef versions of the keys kInstrumentInfoKey_MSB,
 					kInstrumentInfoKey_LSB, kInstrumentInfoKey_Program, and kInstrumentInfoKey_Name.
 						MSB: An NSNumberRef for the most-significant byte of the bank number.  GM melodic banks will return 120 (0x78).
 							 GM percussion banks will return 121 (0x79).  Custom banks will return their literal value.
						LSB: An NSNumberRef for the least-significant byte of the bank number.  All GM banks will return
							 the bank variation number (0-127).
 						Program Number: An NSNumberRef for the program number (0-127) of an instrument within a particular bank.
 						Name: A CFStringRef containing the name of the instrument.
 
					Using these MSB, LSB, and Program values will guarantee that the correct instrument is loaded by the DLS synth
					or Sampler Audio Unit.
					The CFArray should be released by the caller.

    @param			inURL
	 					The URL for the sound bank.
    @param			outInstrumentInfo
						A pointer to a CFArrayRef to be created and returned by the function.
    @result			returns noErr if successful.
*/

OS_EXPORT OSStatus
CopyInstrumentInfoFromSoundBank (CFURLRef inURL, CFArrayRef __nullable * __nonnull outInstrumentInfo)
														API_AVAILABLE(macos(10.8), ios(7.0), watchos(2.0), tvos(9.0));
	
#define kInstrumentInfoKey_Name		"name"
#define kInstrumentInfoKey_MSB		"MSB"
#define kInstrumentInfoKey_LSB		"LSB"
#define kInstrumentInfoKey_Program	"program"

#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioToolbox_h
// ==========  AudioToolbox.framework/Headers/AudioFile.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AudioFile.h>)
/*!
	@file		AudioFile.h
	@framework	AudioToolbox.framework
	@copyright	(c) 1985-2015 by Apple, Inc., all rights reserved.
	@abstract	API's to read and write audio files in the filesystem or in memory.
*/

#ifndef AudioToolbox_AudioFile_h
#define AudioToolbox_AudioFile_h

//=============================================================================
//	Includes
//=============================================================================

#include <Availability.h>
#include <CoreAudioTypes/CoreAudioTypes.h>
#include <CoreFoundation/CoreFoundation.h>

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

/*!
	@typedef	AudioFileTypeID
	@abstract	Identifier for an audio file type.
*/
typedef UInt32 AudioFileTypeID;

/*!
    @enum Audio File Types
    @abstract   Constants for the built-in audio file types.
    @discussion These constants are used to indicate the type of file to be written, or as a hint to
					what type of file to expect from data provided.
    @constant   kAudioFileAIFFType
					Audio Interchange File Format (AIFF)
    @constant   kAudioFileAIFCType
					Audio Interchange File Format Compressed (AIFF-C)
    @constant   kAudioFileWAVEType
					Microsoft WAVE
    @constant   kAudioFileRF64Type
                    File Format specified in EBU Tech 3306
    @constant   kAudioFileSoundDesigner2Type
					Sound Designer II
    @constant   kAudioFileNextType
					NeXT / Sun
    @constant   kAudioFileMP3Type
					MPEG Audio Layer 3 (.mp3)
    @constant   kAudioFileMP2Type
					MPEG Audio Layer 2 (.mp2)
    @constant   kAudioFileMP1Type
					MPEG Audio Layer 1 (.mp1)
    @constant   kAudioFileAC3Type
					AC-3
    @constant   kAudioFileAAC_ADTSType
					Advanced Audio Coding (AAC) Audio Data Transport Stream (ADTS)
    @constant   kAudioFileMPEG4Type
    @constant   kAudioFileM4AType
    @constant   kAudioFileM4BType
    @constant   kAudioFileCAFType
                    CoreAudio File Format
    @constant   kAudioFile3GPType
    @constant   kAudioFile3GP2Type
    @constant   kAudioFileAMRType
    @constant   kAudioFileFLACType
                    Free Lossless Audio Codec
    @constant   kAudioFileLATMInLOASType
                    Low-overhead audio stream with low-overhead audio transport multiplex, per ISO/IEC 14496-3.
                    Support is limited to AudioSyncStream using AudioMuxElement with mux config present.
*/
CF_ENUM(AudioFileTypeID) {
        kAudioFileAIFFType				= 'AIFF',
        kAudioFileAIFCType				= 'AIFC',
        kAudioFileWAVEType				= 'WAVE',
        kAudioFileRF64Type              = 'RF64',
        kAudioFileSoundDesigner2Type	= 'Sd2f',
        kAudioFileNextType				= 'NeXT',
        kAudioFileMP3Type				= 'MPG3',	// mpeg layer 3
        kAudioFileMP2Type				= 'MPG2',	// mpeg layer 2
        kAudioFileMP1Type				= 'MPG1',	// mpeg layer 1
		kAudioFileAC3Type				= 'ac-3',
        kAudioFileAAC_ADTSType			= 'adts',
        kAudioFileMPEG4Type             = 'mp4f',
        kAudioFileM4AType               = 'm4af',
        kAudioFileM4BType               = 'm4bf',
		kAudioFileCAFType				= 'caff',
		kAudioFile3GPType				= '3gpp',
		kAudioFile3GP2Type				= '3gp2',		
		kAudioFileAMRType				= 'amrf',
		kAudioFileFLACType				= 'flac',
		kAudioFileLATMInLOASType		= 'loas'
};

/*!
    @enum AudioFile error codes
    @abstract   These are the error codes returned from the AudioFile API.
    @constant   kAudioFileUnspecifiedError 
		An unspecified error has occurred.
    @constant   kAudioFileUnsupportedFileTypeError 
		The file type is not supported.
    @constant   kAudioFileUnsupportedDataFormatError 
		The data format is not supported by this file type.
    @constant   kAudioFileUnsupportedPropertyError 
		The property is not supported.
    @constant   kAudioFileBadPropertySizeError 
		The size of the property data was not correct.
    @constant   kAudioFilePermissionsError 
		The operation violated the file permissions. For example, trying to write to a file opened with kAudioFileReadPermission.
    @constant   kAudioFileNotOptimizedError 
		There are chunks following the audio data chunk that prevent extending the audio data chunk. 
		The file must be optimized in order to write more audio data.
    @constant   kAudioFileInvalidChunkError 
		The chunk does not exist in the file or is not supported by the file. 
    @constant   kAudioFileDoesNotAllow64BitDataSizeError 
		The a file offset was too large for the file type. AIFF and WAVE have a 32 bit file size limit. 
    @constant   kAudioFileInvalidPacketOffsetError 
		A packet offset was past the end of the file, or not at the end of the file when writing a VBR format, 
		or a corrupt packet size was read when building the packet table. 
    @constant   kAudioFileInvalidPacketDependencyError
		Either the packet dependency info that's necessary for the audio format has not been provided,
		or the provided packet dependency info indicates dependency on a packet that's unavailable.
    @constant   kAudioFileInvalidFileError 
		The file is malformed, or otherwise not a valid instance of an audio file of its type. 
    @constant   kAudioFileOperationNotSupportedError 
		The operation cannot be performed. For example, setting kAudioFilePropertyAudioDataByteCount to increase 
		the size of the audio data in a file is not a supported operation. Write the data instead.
    @constant   kAudioFileNotOpenError 
		The file is closed.
	@constant   kAudioFileEndOfFileError 
		End of file.
	@constant   kAudioFilePositionError 
		Invalid file position.
	@constant   kAudioFileFileNotFoundError 
		File not found.
 */
CF_ENUM(OSStatus) {
        kAudioFileUnspecifiedError						= 'wht?',		// 0x7768743F, 2003334207
        kAudioFileUnsupportedFileTypeError 				= 'typ?',		// 0x7479703F, 1954115647
        kAudioFileUnsupportedDataFormatError 			= 'fmt?',		// 0x666D743F, 1718449215
        kAudioFileUnsupportedPropertyError 				= 'pty?',		// 0x7074793F, 1886681407
        kAudioFileBadPropertySizeError 					= '!siz',		// 0x2173697A,  561211770
        kAudioFilePermissionsError	 					= 'prm?',		// 0x70726D3F, 1886547263
        kAudioFileNotOptimizedError						= 'optm',		// 0x6F70746D, 1869640813
        // file format specific error codes
        kAudioFileInvalidChunkError						= 'chk?',		// 0x63686B3F, 1667787583
        kAudioFileDoesNotAllow64BitDataSizeError		= 'off?',		// 0x6F66663F, 1868981823
        kAudioFileInvalidPacketOffsetError				= 'pck?',		// 0x70636B3F, 1885563711
        kAudioFileInvalidPacketDependencyError			= 'dep?',		// 0x6465703F, 1684369471
        kAudioFileInvalidFileError						= 'dta?',		// 0x6474613F, 1685348671
		kAudioFileOperationNotSupportedError			= 0x6F703F3F, 	// 'op??', integer used because of trigraph
		// general file error codes
		kAudioFileNotOpenError							= -38,
		kAudioFileEndOfFileError						= -39,
		kAudioFilePositionError							= -40,
		kAudioFileFileNotFoundError						= -43
};

/*!
    @enum AudioFileFlags
    @abstract   These are flags that can be used with the CreateURL API call
    @constant   kAudioFileFlags_EraseFile 
		If set, then the CreateURL call will erase the contents of an existing file
		If not set, then the CreateURL call will fail if the file already exists
    @constant   kAudioFileFlags_DontPageAlignAudioData 
		Normally, newly created and optimized files will have padding added in order to page align 
		the data to 4KB boundaries. This makes reading the data more efficient. 
		When disk space is a concern, this flag can be set so that the padding will not be added.
*/
typedef CF_OPTIONS(UInt32, AudioFileFlags) {
	kAudioFileFlags_EraseFile = 1,
	kAudioFileFlags_DontPageAlignAudioData = 2
};

typedef CF_ENUM(SInt8, AudioFilePermissions) {
	kAudioFileReadPermission      = 0x01,
	kAudioFileWritePermission     = 0x02,
	kAudioFileReadWritePermission = 0x03
};

//=============================================================================
//	Types specific to the Audio File API
//=============================================================================

/*!
    @typedef	AudioFileID
    @abstract   An opaque reference to an AudioFile object.
*/
typedef	struct OpaqueAudioFileID	*AudioFileID;
/*!
    @typedef	AudioFilePropertyID
    @abstract   A constant for an AudioFile property.
*/
typedef UInt32			AudioFilePropertyID;

/*!
    @enum		AudioFileLoopDirection
    @abstract   These constants describe the playback direction of a looped segment of a file.
    @constant   kAudioFileLoopDirection_NoLooping
					The segment is not looped.
    @constant   kAudioFileLoopDirection_Forward
					play segment forward.
    @constant   kAudioFileLoopDirection_Backward
					play segment backward.
    @constant   kAudioFileLoopDirection_ForwardAndBackward
					play segment forward and backward.
*/
CF_ENUM(UInt32) {
	kAudioFileLoopDirection_NoLooping = 0,
	kAudioFileLoopDirection_Forward = 1,
	kAudioFileLoopDirection_ForwardAndBackward = 2,
	kAudioFileLoopDirection_Backward = 3
};

//=============================================================================
//	Markers, Regions
//=============================================================================


/*!
    @struct		AudioFile_SMPTE_Time
    @abstract   A struct for describing a SMPTE time.
    @var        mHours						The hours.
    @var        mMinutes					The minutes.
    @var        mSeconds					The seconds.
    @var        mFrames						The frames.
    @var        mSubFrameSampleOffset		The sample offset within a frame.
*/
struct AudioFile_SMPTE_Time
{
	SInt8 mHours;
	UInt8 mMinutes;
	UInt8 mSeconds;
	UInt8 mFrames;
	UInt32 mSubFrameSampleOffset;
};
typedef struct AudioFile_SMPTE_Time AudioFile_SMPTE_Time;


/*!
    @enum		AudioFileMarkerType
    @abstract   constants for types of markers within a file. Used in the mType field of AudioFileMarker.
    @constant   kAudioFileMarkerType_Generic		A generic marker. See CAFFile.h for marker types specific to CAF files.
*/
CF_ENUM(UInt32) {
	kAudioFileMarkerType_Generic			= 0,
};


/*!
    @struct		AudioFileMarker
    @abstract   A marker annotates a position in an audio file with additional information.
    @discussion (description)
    @var        mFramePosition	The frame in the file counting from the start of the audio data.
    @var        mName			The name of this marker.
    @var        mMarkerID		A unique ID for this marker.
    @var        mSMPTETime		The SMPTE time for this marker.
    @var        mType			The marker type.
    @var        mReserved		A reserved field. Set to zero.
    @var        mChannel		The channel number that the marker refers to. Set to zero if marker applies to all channels.
*/
struct AudioFileMarker
{
	Float64 mFramePosition;
	
	CFStringRef	__nullable	mName;
	SInt32					mMarkerID;

	AudioFile_SMPTE_Time	mSMPTETime;
	UInt32					mType;
	UInt16					mReserved;
	UInt16					mChannel;
};
typedef struct AudioFileMarker AudioFileMarker;

/*!
    @struct		AudioFileMarkerList
    @abstract   A list of AudioFileMarker.
    @var        mSMPTE_TimeType
					This defines the SMPTE timing scheme used in the marker list. See CAFFile.h for the values used here.
    @var        mNumberMarkers
					The number of markers in the mMarkers list.
    @var        mMarkers
					A list of AudioFileMarker.
*/
struct AudioFileMarkerList
{
	UInt32				mSMPTE_TimeType;
	UInt32				mNumberMarkers;
	AudioFileMarker		mMarkers[1]; // this is a variable length array of mNumberMarkers elements
};
typedef struct AudioFileMarkerList AudioFileMarkerList;

/*!
    @function	NumBytesToNumAudioFileMarkers
    @abstract   Converts a size in bytes to the number of AudioFileMarkers that can be contained in that number of bytes.
    @discussion This can be used for the kAudioFilePropertyMarkerList property when calculating the number of 
				markers that will be returned. 
    @param      inNumBytes 
					a number of bytes.
    @result     the number of AudioFileMarkers that can be contained in that number of bytes.
*/
#ifdef CF_INLINE
CF_INLINE size_t NumBytesToNumAudioFileMarkers(size_t inNumBytes)
{
	return (inNumBytes<offsetof(AudioFileMarkerList, mMarkers[0]) ? 0 : (inNumBytes - offsetof(AudioFileMarkerList, mMarkers[0])) / sizeof(AudioFileMarker));
}
#else
#define NumBytesToNumAudioFileMarkers(inNumBytes) \
	((inNumBytes)<offsetof(AudioFileMarkerList, mMarkers[0])?0:((inNumBytes) - offsetof(AudioFileMarkerList, mMarkers[0])) / sizeof(AudioFileMarker))
#endif

/*!
    @function	NumAudioFileMarkersToNumBytes
    @abstract   Converts a number of AudioFileMarkers to a size in bytes.
    @discussion This can be used for the kAudioFilePropertyMarkerList property when calculating the size required to 
				contain a number of AudioFileMarkers. 
    @param      inNumMarkers 
					a number of AudioFileMarkers.
    @result     the size in bytes required to contain that number of AudioFileMarkers.
*/
#ifdef CF_INLINE
CF_INLINE size_t NumAudioFileMarkersToNumBytes(size_t inNumMarkers)
{
	return (offsetof(AudioFileMarkerList, mMarkers) + (inNumMarkers) * sizeof(AudioFileMarker));
}
#else
#define NumAudioFileMarkersToNumBytes(inNumMarkers) \
	(offsetof(AudioFileMarkerList, mMarkers) + (inNumMarkers) * sizeof(AudioFileMarker))
#endif

/*!
    @enum		AudioFileRegionFlags
    @abstract   These are flags for an AudioFileRegion that specify a playback direction.
    @discussion One or multiple of these flags can be set. For example, if both kAudioFileRegionFlag_LoopEnable and 
				kAudioFileRegionFlag_PlayForward are set, then the region will play as a forward loop. If only 
				kAudioFileRegionFlag_PlayForward is set, then the region will be played forward once.
    @constant   kAudioFileRegionFlag_LoopEnable
					If this flag is set, the region will be looped. One or both of the following must also be set.
    @constant   kAudioFileRegionFlag_PlayForward
					If this flag is set, the region will be played forward.
    @constant   kAudioFileRegionFlag_PlayBackward
					If this flag is set, the region will be played backward.
*/
typedef CF_OPTIONS(UInt32, AudioFileRegionFlags) {
	kAudioFileRegionFlag_LoopEnable = 1,
	kAudioFileRegionFlag_PlayForward = 2,
	kAudioFileRegionFlag_PlayBackward = 4
};

/*!
    @struct		AudioFileRegion
    @abstract   An AudioFileRegion specifies a segment of audio data.
    @discussion Generally a region consists of at least two markers marking the beginning and end of the segment.
				There may also be other markers defining other meta information such as sync point.
    @var        mRegionID 
					each region must have a unique ID.
    @var        mName 
					The name of the region.
    @var        mFlags 
					AudioFileRegionFlags.
    @var        mNumberMarkers 
					The number of markers in the mMarkers array.
    @var        mMarkers 
					A variable length array of AudioFileMarkers.
*/
struct AudioFileRegion
{
	UInt32					mRegionID;
	CFStringRef				mName;
	AudioFileRegionFlags	mFlags;
	UInt32					mNumberMarkers;
	AudioFileMarker			mMarkers[1]; // this is a variable length array of mNumberMarkers elements
};
typedef struct AudioFileRegion AudioFileRegion;


/*!
    @struct		AudioFileRegionList
    @abstract   A list of the AudioFileRegions in a file.
    @discussion This is the struct used by the kAudioFilePropertyRegionList property.
    @var        mSMPTE_TimeType
					This defines the SMPTE timing scheme used in the file. See CAFFile.h for the values used here.
    @var        mNumberRegions
					The number of regions in the mRegions list.
    @var        mRegions
					A list of AudioFileRegions. Note that AudioFileMarkers are variable length, so this list cannot 
					be accessed as an array. Use the NextAudioFileRegion macro for traversing the list instead.
*/
struct AudioFileRegionList
{
	UInt32				mSMPTE_TimeType;
	UInt32				mNumberRegions;
	AudioFileRegion		mRegions[1]; // this is a variable length array of mNumberRegions elements
};
typedef struct AudioFileRegionList AudioFileRegionList;

/*!
    @function	NextAudioFileRegion
    @abstract   convenience macro for traversing the region list.
    @discussion because AudioFileRegions are variable length, you cannot access them as an array. Use NextAudioFileRegion 
				to walk the list.
    @param      inAFRegionPtr 
					a pointer to the current region.
    @result     a pointer to the region after the current region. This does not protect you from walking off the end of the list, 
				so obey mNumberRegions.
*/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wcast-qual"
#pragma clang diagnostic ignored "-Wcast-align"
#ifdef CF_INLINE
CF_INLINE AudioFileRegion *NextAudioFileRegion(const AudioFileRegion *inAFRegionPtr)
{
	return ((AudioFileRegion*)((char*)inAFRegionPtr + offsetof(AudioFileRegion, mMarkers) + (inAFRegionPtr->mNumberMarkers)*sizeof(AudioFileMarker)));
}
#else
#define NextAudioFileRegion(inAFRegionPtr) \
        ((AudioFileRegion*)((char*)(inAFRegionPtr) + offsetof(AudioFileRegion, mMarkers) + ((inAFRegionPtr)->mNumberMarkers)*sizeof(AudioFileMarker)))
#endif
#pragma clang diagnostic pop

/*!
    @struct		AudioFramePacketTranslation
    @abstract   used for properties kAudioFilePropertyPacketToFrame and kAudioFilePropertyFrameToPacket
    @discussion See description of kAudioFilePropertyPacketToFrame and kAudioFilePropertyFrameToPacket
    @var        mFrame		a frame number.
    @var        mPacket		a packet number.
    @var        mFrameOffsetInPacket		a frame offset in a packet.
*/
struct AudioFramePacketTranslation
{
	SInt64 mFrame;
	SInt64 mPacket;
	UInt32 mFrameOffsetInPacket;
};
typedef struct AudioFramePacketTranslation AudioFramePacketTranslation;


/*!
    @enum		AudioBytePacketTranslation Flags
	
    @abstract   flags for the AudioBytePacketTranslation mFlags field
    @discussion		There is currently only one flag.
					
    @constant   kBytePacketTranslationFlag_IsEstimate
					If the set then the result value is an estimate.
*/
typedef CF_OPTIONS(UInt32, AudioBytePacketTranslationFlags) {
	kBytePacketTranslationFlag_IsEstimate = 1
};

/*!
    @struct		AudioBytePacketTranslation
    @abstract   used for properties kAudioFileByteToPacket and kAudioFilePacketToByte
    @discussion See description of kAudioFileByteToPacket and kAudioFilePacketToByte
    @var        mByte		a byte number.
    @var        mPacket		a packet number.
    @var        mByteOffsetInPacket		a byte offset in a packet.
    @var        mFlags		if kBytePacketTranslationFlag_IsEstimate is set, then the value is an estimate.
*/
struct AudioBytePacketTranslation
{
	SInt64 mByte;
	SInt64 mPacket;
	UInt32 mByteOffsetInPacket;
	AudioBytePacketTranslationFlags mFlags;
};
typedef struct AudioBytePacketTranslation AudioBytePacketTranslation;


/*!
    @struct		AudioFilePacketTableInfo
    @abstract   This contains information about the number of valid frames in a file and where they begin and end.
    @discussion	Some data formats may have packets whose contents are not completely valid, but represent priming or remainder 
				frames that are not meant to be played. For example a file with 100 packets of AAC is nominally 1024 * 100 = 102400 frames
				of data. However the first 2112 frames of that may be priming frames and there may be some 
				number of remainder frames added to pad out to a full packet of 1024 frames. The priming and remainder frames should be 
				discarded. The total number of packets in the file times the frames per packet (or counting each packet's frames 
				individually for a variable frames per packet format) minus mPrimingFrames, minus mRemainderFrames, should 
				equal mNumberValidFrames.
    @var        mNumberValidFrames the number of valid frames in the file.
    @var        mPrimingFrames the number of invalid frames at the beginning of the file.
    @var        mRemainderFrames the number of invalid frames at the end of the file.
*/
struct AudioFilePacketTableInfo
{
        SInt64  mNumberValidFrames;
        SInt32  mPrimingFrames;
        SInt32  mRemainderFrames;
};
typedef struct AudioFilePacketTableInfo AudioFilePacketTableInfo;


/*!
    @struct	AudioPacketRangeByteCountTranslation
    @abstract   used for property kAudioFilePropertyPacketRangeByteCountUpperBound
    @discussion See description of kAudioFilePropertyPacketRangeByteCountUpperBound
    @var        mPacket					a packet number.
    @var        mPacketCount			a packet count.
    @var        mByteCountUpperBound	an upper bound for the total size of the specified packets.
*/
struct AudioPacketRangeByteCountTranslation
{
	SInt64 mPacket;
	SInt64 mPacketCount;
	SInt64 mByteCountUpperBound;
};
typedef struct AudioPacketRangeByteCountTranslation AudioPacketRangeByteCountTranslation;


/*!
    @struct		AudioPacketRollDistanceTranslation
    @abstract   used for property kAudioFilePropertyPacketToRollDistance
    @discussion See descriptions of kAudioFilePropertyPacketToRollDistance and kAudioFilePropertyRestrictsRandomAccess
    @var        mPacket         a packet number
    @var        mRollDistance   a count of packets that must be decoded prior to the packet with the specified number in order to achieve the best practice for the decoding of that packet
*/
struct AudioPacketRollDistanceTranslation
{
	SInt64 mPacket;
	SInt64 mRollDistance;
};
typedef struct AudioPacketRollDistanceTranslation AudioPacketRollDistanceTranslation;


/*!
    @struct		AudioIndependentPacketTranslation
    @abstract   used for property kAudioFilePropertyPreviousIndependentPacket and kAudioFilePropertyNextIndependentPacket
    @discussion See descriptions of kAudioFilePropertyPreviousIndependentPacket and kAudioFilePropertyNextIndependentPacket
    @var        mPacket                         a packet number
    @var        mIndependentlyDecodablePacket   a packet number not equal to mPacket of an independent packet
*/
struct AudioIndependentPacketTranslation
{
	SInt64 mPacket;
	SInt64 mIndependentlyDecodablePacket;
};
typedef struct AudioIndependentPacketTranslation AudioIndependentPacketTranslation;


/*!
    @struct		AudioPacketDependencyInfoTranslation
    @abstract   used for property kAudioFilePropertyPacketToDependencyInfo
    @discussion See descriptions of kAudioFilePropertyPacketToDependencyInfo and kAudioFilePropertyRestrictsRandomAccess
    @var        mPacket                     a packet number
    @var        mIsIndependentlyDecodable   1 means that the specified packet is independently decodable; 0 means it's not
    @var        mNumberPrerollPackets       if the packet is independently decodable, the count of packets that must be decoded after the packet with the specified number in order to refresh the decoder
*/
struct AudioPacketDependencyInfoTranslation
{
	SInt64 mPacket;
	UInt32 mIsIndependentlyDecodable;
	UInt32 mNumberPrerollPackets;
};
typedef struct AudioPacketDependencyInfoTranslation AudioPacketDependencyInfoTranslation;


//=============================================================================
//	Info String Keys
//=============================================================================

// Get key values from the InfoDictionary by making CFStrings from the following constants

#define kAFInfoDictionary_Album							"album"
#define kAFInfoDictionary_ApproximateDurationInSeconds  "approximate duration in seconds"
#define kAFInfoDictionary_Artist                        "artist"
#define kAFInfoDictionary_ChannelLayout					"channel layout"
#define kAFInfoDictionary_Comments						"comments"
#define kAFInfoDictionary_Composer						"composer"
#define kAFInfoDictionary_Copyright						"copyright"
#define kAFInfoDictionary_EncodingApplication           "encoding application"
#define kAFInfoDictionary_Genre							"genre"
#define kAFInfoDictionary_ISRC							"ISRC"					// International Standard Recording Code
#define kAFInfoDictionary_KeySignature					"key signature"
#define kAFInfoDictionary_Lyricist						"lyricist"
#define kAFInfoDictionary_NominalBitRate                "nominal bit rate"
#define kAFInfoDictionary_RecordedDate					"recorded date"
#define kAFInfoDictionary_SourceBitDepth				"source bit depth"
#define kAFInfoDictionary_SourceEncoder					"source encoder"
#define kAFInfoDictionary_SubTitle						"subtitle"
#define kAFInfoDictionary_Tempo							"tempo"
#define kAFInfoDictionary_TimeSignature					"time signature"
#define kAFInfoDictionary_Title							"title"
#define kAFInfoDictionary_TrackNumber                   "track number"
#define kAFInfoDictionary_Year							"year"

//=============================================================================
//	Routines
//=============================================================================

/*!
    @function	AudioFileCreateWithURL
    @abstract   creates a new audio file (or initialises an existing file)
    @discussion	creates a new (or initialises an existing) audio file specified by the URL.
					Upon success, an AudioFileID is returned which can be used for subsequent calls 
					to the AudioFile APIs.
    @param inFileRef		an CFURLRef fully specifying the path of the file to create/initialise
    @param inFileType		an AudioFileTypeID indicating the type of audio file to create.
    @param inFormat			an AudioStreamBasicDescription describing the data format that will be
							added to the audio file.
    @param inFlags			relevant flags for creating/opening the file. 
								if kAudioFileFlags_EraseFile is set, it will erase an existing file
								 if not set, then the Create call will fail if the URL is an existing file
    @param outAudioFile		if successful, an AudioFileID that can be used for subsequent AudioFile calls.
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileCreateWithURL (CFURLRef						inFileRef,
                    AudioFileTypeID						inFileType,
                    const AudioStreamBasicDescription	*inFormat,
                    AudioFileFlags						inFlags,
                    AudioFileID	__nullable * __nonnull	outAudioFile)		API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function				AudioFileOpenURL
    @abstract				Open an existing audio file.
    @discussion				Open an existing audio file for reading or reading and writing.
    @param inFileRef		the CFURLRef of an existing audio file.
    @param inPermissions	use the permission constants
    @param inFileTypeHint	For files which have no filename extension and whose type cannot be easily or
							uniquely determined from the data (ADTS,AC3), this hint can be used to indicate the file type. 
							Otherwise you can pass zero for this. The hint is only used on OS versions 10.3.1 or greater.
							For OS versions prior to that, opening files of the above description will fail.
    @param outAudioFile		upon success, an AudioFileID that can be used for subsequent
							AudioFile calls.
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileOpenURL (	CFURLRef							inFileRef,
					AudioFilePermissions				inPermissions,
					AudioFileTypeID						inFileTypeHint,
					AudioFileID	__nullable * __nonnull	outAudioFile)					API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @typedef	AudioFile_ReadProc
    @abstract   A callback for reading data. used with AudioFileOpenWithCallbacks or AudioFileInitializeWithCallbacks.
    @discussion a function that will be called when AudioFile needs to read data.
    @param      inClientData	A pointer to the client data as set in the inClientData parameter to AudioFileXXXWithCallbacks.
    @param      inPosition		An offset into the data from which to read.
    @param      requestCount	The number of bytes to read.
    @param      buffer			The buffer in which to put the data read.
    @param      actualCount		The callback should set this to the number of bytes successfully read.
    @result						The callback should return noErr on success, or an appropriate error code on failure.
*/
typedef OSStatus (*AudioFile_ReadProc)(
								void *		inClientData,
								SInt64		inPosition, 
								UInt32		requestCount,
								void *		buffer, 
								UInt32 *	actualCount);

/*!
    @typedef	AudioFile_WriteProc
    @abstract   A callback for writing data. used with AudioFileOpenWithCallbacks or AudioFileInitializeWithCallbacks.
    @discussion a function that will be called when AudioFile needs to write data.
    @param      inClientData	A pointer to the client data as set in the inClientData parameter to AudioFileXXXWithCallbacks.
    @param      inPosition		An offset into the data from which to read.
    @param      requestCount	The number of bytes to write.
    @param      buffer			The buffer containing the data to write.
    @param      actualCount		The callback should set this to the number of bytes successfully written.
    @result						The callback should return noErr on success, or an appropriate error code on failure.
*/
typedef OSStatus (*AudioFile_WriteProc)(
								void * 		inClientData,
								SInt64		inPosition, 
								UInt32		requestCount, 
								const void *buffer, 
								UInt32    * actualCount);
								
/*!
    @typedef	AudioFile_GetSizeProc
    @abstract   A callback for getting the size of the file data. used with AudioFileOpenWithCallbacks or AudioFileInitializeWithCallbacks.
    @discussion a function that will be called when AudioFile needs to determine the size of the file data. This size is for all of the 
				data in the file, not just the audio data.
    @param      inClientData	A pointer to the client data as set in the inClientData parameter to AudioFileXXXWithCallbacks.
    @result						The callback should return the size of the data.
*/
typedef SInt64 (*AudioFile_GetSizeProc)(
								void * 		inClientData);

/*!
    @typedef	AudioFile_SetSizeProc
    @abstract   A callback for setting the size of the file data. used with AudioFileOpenWithCallbacks or AudioFileInitializeWithCallbacks.
    @discussion a function that will be called when AudioFile needs to set the size of the file data. This size is for all of the 
				data in the file, not just the audio data. This will only be called if the file is written to.
    @param      inClientData	A pointer to the client data as set in the inClientData parameter to AudioFileXXXWithCallbacks.
    @result						The callback should return the size of the data.
*/
typedef OSStatus (*AudioFile_SetSizeProc)(
								void *		inClientData,
								SInt64		inSize);

/*!
    @function	AudioFileInitializeWithCallbacks
    @abstract   Wipe clean an existing file. You provide callbacks that the AudioFile API
				will use to get the data.
    @param inClientData		a constant that will be passed to your callbacks.
	@param inReadFunc		a function that will be called when AudioFile needs to read data.
	@param inWriteFunc		a function that will be called when AudioFile needs to write data.
	@param inGetSizeFunc	a function that will be called when AudioFile needs to know the file size.
	@param inSetSizeFunc	a function that will be called when AudioFile needs to set the file size.
	
    @param inFileType 		an AudioFileTypeID indicating the type of audio file to which to initialize the file. 
    @param inFormat 		an AudioStreamBasicDescription describing the data format that will be
							added to the audio file.
    @param inFlags			flags for creating/opening the file. Currently zero.
    @param outAudioFile		upon success, an AudioFileID that can be used for subsequent
							AudioFile calls.
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileInitializeWithCallbacks (	
						void *								inClientData, 
						AudioFile_ReadProc					inReadFunc, 
						AudioFile_WriteProc					inWriteFunc, 
						AudioFile_GetSizeProc				inGetSizeFunc,
						AudioFile_SetSizeProc				inSetSizeFunc,
                        AudioFileTypeID						inFileType,
                        const AudioStreamBasicDescription	*inFormat,
                        AudioFileFlags						inFlags,
                        AudioFileID	__nullable * __nonnull	outAudioFile)	API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));


/*!
    @function	AudioFileOpenWithCallbacks
    @abstract   Open an existing file. You provide callbacks that the AudioFile API
				will use to get the data.
    @param inClientData					a constant that will be passed to your callbacks.
	@param inReadFunc					a function that will be called when AudioFile needs to read data.
	@param inWriteFunc					a function that will be called when AudioFile needs to write data.
	@param inGetSizeFunc				a function that will be called when AudioFile needs to know the total file size.
	@param inSetSizeFunc				a function that will be called when AudioFile needs to set the file size.
	
    @param inFileTypeHint	For files which have no filename extension and whose type cannot be easily or
							uniquely determined from the data (ADTS,AC3), this hint can be used to indicate the file type. 
							Otherwise you can pass zero for this. The hint is only used on OS versions 10.3.1 or greater.
							For OS versions prior to that, opening files of the above description will fail.
    @param outAudioFile		upon success, an AudioFileID that can be used for subsequent
							AudioFile calls.
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileOpenWithCallbacks (
				void *								inClientData,
				AudioFile_ReadProc					inReadFunc,
				AudioFile_WriteProc __nullable		inWriteFunc,
				AudioFile_GetSizeProc				inGetSizeFunc,
				AudioFile_SetSizeProc __nullable	inSetSizeFunc,
                AudioFileTypeID						inFileTypeHint,
                AudioFileID	__nullable * __nonnull	outAudioFile)				API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));
				

/*!
    @function	AudioFileClose
    @abstract   Close an existing audio file.
    @param      inAudioFile		an AudioFileID.
    @result						returns noErr if successful.
*/
extern OSStatus
AudioFileClose	(AudioFileID		inAudioFile)							API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function	AudioFileOptimize
    @abstract   Move the audio data to the end of the file and other internal optimizations of the file structure.
	@discussion			Optimize the file so additional audio data can be appended to 
                        the existing data. Generally, this will place the audio data at 
                        the end of the file so additional writes can be placed to the 
                        file end. This can be a potentially expensive and time-consuming operation 
                        and should not be used during time critical operations. There is 
                        a kAudioFilePropertyIsOptimized property for checking on the optimized state 
                        of the file.
    @param      inAudioFile		an AudioFileID.
    @result						returns noErr if successful.
*/
extern OSStatus	
AudioFileOptimize (AudioFileID  	inAudioFile)							API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function	AudioFileReadBytes
    @abstract   Read bytes of audio data from the audio file. 
				
    @discussion				Returns kAudioFileEndOfFileError when read encounters end of file.
    @param inAudioFile		an AudioFileID.
    @param inUseCache 		true if it is desired to cache the data upon read, else false
    @param inStartingByte	the byte offset of the audio data desired to be returned
    @param ioNumBytes 		on input, the number of bytes to read, on output, the number of
							bytes actually read.
    @param outBuffer 		outBuffer should be a void * to user allocated memory large enough for the requested bytes. 
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileReadBytes (	AudioFileID  	inAudioFile,
                        Boolean			inUseCache,
                        SInt64			inStartingByte, 
                        UInt32			*ioNumBytes, 
                        void			*outBuffer)							API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function				AudioFileWriteBytes
    @abstract				Write bytes of audio data to the audio file.
    @param inAudioFile		an AudioFileID.
    @param inUseCache 		true if it is desired to cache the data upon write, else false
    @param inStartingByte	the byte offset where the audio data should be written
    @param ioNumBytes 		on input, the number of bytes to write, on output, the number of
							bytes actually written.
    @param inBuffer 		inBuffer should be a void * containing the bytes to be written 
    @result					returns noErr if successful.
*/
extern OSStatus	
AudioFileWriteBytes (	AudioFileID  	inAudioFile,  
                        Boolean			inUseCache,
                        SInt64			inStartingByte, 
                        UInt32			*ioNumBytes, 
                        const void		*inBuffer)							API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function	AudioFileReadPacketData
    @abstract   Read packets of audio data from the audio file.
    @discussion AudioFileReadPacketData reads as many of the requested number of packets
				as will fit in the buffer size given by ioNumPackets.
				Unlike the deprecated AudioFileReadPackets, ioNumPackets must be initialized.
				If the byte size of the number packets requested is 
				less than the buffer size, ioNumBytes will be reduced.
				If the buffer is too small for the number of packets 
				requested, ioNumPackets and ioNumBytes will be reduced 
				to the number of packets that can be accommodated and their byte size.
				Returns kAudioFileEndOfFileError when read encounters end of file.
				For all uncompressed formats, packets == frames.

    @param inAudioFile				an AudioFileID.
    @param inUseCache 				true if it is desired to cache the data upon read, else false
    @param ioNumBytes				on input the size of outBuffer in bytes. 
									on output, the number of bytes actually returned.
    @param outPacketDescriptions 	An array of packet descriptions describing the packets being returned. 
									The size of the array must be greater or equal to the number of packets requested. 
									On return the packet description will be filled out with the packet offsets and sizes.
									Packet descriptions are ignored for CBR data.   
    @param inStartingPacket 		The packet index of the first packet desired to be returned
    @param ioNumPackets 			on input, the number of packets to read, on output, the number of
									packets actually read.
    @param outBuffer 				outBuffer should be a pointer to user allocated memory.
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileReadPacketData (	AudioFileID  					inAudioFile, 
                       		Boolean							inUseCache,
                       		UInt32 *						ioNumBytes,
                       		AudioStreamPacketDescription * __nullable outPacketDescriptions,
                       		SInt64							inStartingPacket, 
                       		UInt32 * 						ioNumPackets,
                       		void * __nullable				outBuffer)			API_AVAILABLE(macos(10.6), ios(2.2), watchos(2.0), tvos(9.0));

/*!
    @function	AudioFileReadPackets
    @abstract   Read packets of audio data from the audio file.
    @discussion AudioFileReadPackets is DEPRECATED. Use AudioFileReadPacketData instead.
				READ THE HEADER DOC FOR AudioFileReadPacketData. It is not a drop-in replacement.
				In particular, for AudioFileReadPacketData ioNumBytes must be initialized to the buffer size.
				AudioFileReadPackets assumes you have allocated your buffer to ioNumPackets times the maximum packet size.
				For many compressed formats this will only use a portion of the buffer since the ratio of the maximum 
				packet size to the typical packet size can be large. Use AudioFileReadPacketData instead.
	
    @param inAudioFile				an AudioFileID.
    @param inUseCache 				true if it is desired to cache the data upon read, else false
    @param outNumBytes				on output, the number of bytes actually returned
    @param outPacketDescriptions 	on output, an array of packet descriptions describing
									the packets being returned. NULL may be passed for this
									parameter. Nothing will be returned for linear pcm data.   
    @param inStartingPacket 		the packet index of the first packet desired to be returned
    @param ioNumPackets 			on input, the number of packets to read, on output, the number of
									packets actually read.
    @param outBuffer 				outBuffer should be a pointer to user allocated memory of size: 
									number of packets requested times file's maximum (or upper bound on)
									packet size.
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileReadPackets (	AudioFileID  					inAudioFile, 
                        Boolean							inUseCache,
                        UInt32 *						outNumBytes,
                        AudioStreamPacketDescription * __nullable outPacketDescriptions,
                        SInt64							inStartingPacket, 
                        UInt32 * 						ioNumPackets,
                        void * __nullable				outBuffer)			API_DEPRECATED("no longer supported", macos(10.2, 10.10), ios(2.0, 8.0)) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;


/*!
    @function	AudioFileWritePackets
    @abstract   Write packets of audio data to the audio file.
    @discussion For all uncompressed formats, packets == frames.
    @param inAudioFile				an AudioFileID.
    @param inUseCache 				true if it is desired to cache the data upon write, else false
    @param inNumBytes				the number of bytes being provided for write
    @param inPacketDescriptions 	an array of packet descriptions describing the packets being 
									provided. Not all formats require packet descriptions to be 
									provided. NULL may be passed if no descriptions are required.   
    @param inStartingPacket 		the packet index of where the first packet provided should be placed.
    @param ioNumPackets 			on input, the number of packets to write, on output, the number of
									packets actually written.
    @param inBuffer 				a void * to user allocated memory containing the packets to write.
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileWritePackets (	AudioFileID							inAudioFile,  
                        Boolean								inUseCache,
                        UInt32								inNumBytes,
                        const AudioStreamPacketDescription * __nullable inPacketDescriptions,
                        SInt64								inStartingPacket, 
                        UInt32								*ioNumPackets, 
                        const void							*inBuffer)			API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));


/*!
    @function	AudioFileCountUserData
    @abstract   Get the number of user data items with a certain ID in the file
    @discussion		"User Data" refers to chunks in AIFF, CAF and WAVE files, or resources 
					in Sound Designer II files, and possibly other things in other files.
					For simplicity, referred to below as "chunks".
    @param      inAudioFile			an AudioFileID.
    @param      inUserDataID		the four char code of the chunk.
    @param      outNumberItems		on output, if successful, number of chunks of this type in the file.
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileCountUserData (	AudioFileID			inAudioFile, 
							UInt32				inUserDataID, 
							UInt32				*outNumberItems)			API_AVAILABLE(macos(10.4), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function	AudioFileGetUserDataSize
    @abstract   Get the size of user data in a file
    @param      inAudioFile			an AudioFileID.
    @param      inUserDataID		the four char code of the chunk.
    @param      inIndex				an index specifying which chunk if there are more than one.
    @param      outUserDataSize		on output, if successful, the size of the user data chunk.
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileGetUserDataSize (	AudioFileID			inAudioFile, 
							UInt32				inUserDataID, 
							UInt32				inIndex, 
							UInt32				*outUserDataSize)			API_AVAILABLE(macos(10.4), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function	AudioFileGetUserData
    @abstract   Get the data of a chunk in a file.
    @param      inAudioFile			an AudioFileID.
    @param      inUserDataID		the four char code of the chunk.
    @param      inIndex				an index specifying which chunk if there are more than one.
	@param		ioUserDataSize		the size of the buffer on input, size of bytes copied to buffer on output 
    @param      outUserData			a pointer to a buffer in which to copy the chunk data.
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileGetUserData (	AudioFileID			inAudioFile, 
						UInt32				inUserDataID, 
						UInt32				inIndex, 
						UInt32				*ioUserDataSize, 
						void				*outUserData)					API_AVAILABLE(macos(10.4), ios(2.0), watchos(2.0), tvos(9.0));

/*!
    @function	AudioFileSetUserData
    @abstract   Set the data of a chunk in a file.
    @param      inAudioFile			an AudioFileID.
    @param      inUserDataID		the four char code of the chunk.
    @param      inIndex				an index specifying which chunk if there are more than one.
	@param		inUserDataSize		on input the size of the data to copy, on output, size of bytes copied from the buffer  
    @param      inUserData			a pointer to a buffer from which to copy the chunk data 
									(only the contents of the chunk, not including the chunk header).
    @result							returns noErr if successful.
*/
extern OSStatus	
AudioFileSetUserData ( AudioFileID			inAudioFile, 
						UInt32				inUserDataID, 
						UInt32				inIndex, 
						UInt32				inUserDataSize, 
						const void			*inUserData)					API_AVAILABLE(macos(10.4), ios(2.0), watchos(2.0), tvos(9.0));


/*!
    @function	AudioFileRemoveUserData
    @abstract   Remove a user chunk in a file.
    @param      inAudioFile			an AudioFileID.
    @param      inUserDataID		the four char code of the chunk.
    @param      inIndex				an index specifying which chunk if there are more than one.
    @result							returns noErr if successful.
*/

extern OSStatus	
AudioFileRemoveUserData ( AudioFileID		inAudioFile, 
						UInt32				inUserDataID, 
						UInt32				inIndex)						API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));


//=============================================================================
//	Audio File Properties
//=============================================================================

/*!
    @enum		Audio File Properties
    @abstract   constants for AudioFile get/set property calls
    @constant   kAudioFilePropertyFileFormat 
					An AudioFileTypeID that identifies the format of the file
    @constant   kAudioFilePropertyDataFormat 
					An AudioStreamBasicDescription describing the format of the audio data
    @constant   kAudioFilePropertyFormatList 
					In order to support formats such as AAC SBR where an encoded data stream can be decoded to 
					multiple destination formats, this property returns an array of AudioFormatListItems (see AudioFormat.h) of those formats.
					The default behavior is to return the an AudioFormatListItem that has the same AudioStreamBasicDescription 
					that kAudioFilePropertyDataFormat returns.
    @constant   kAudioFilePropertyIsOptimized 
					A UInt32 indicating whether an Audio File has been optimized.
					Optimized means it is ready to start having sound data written to it. 
					A value of 0 indicates the file needs to be optimized.
					A value of 1 indicates the file is currently optimized.
    @constant   kAudioFilePropertyMagicCookieData 
					A void * pointing to memory set up by the caller.
					Some file types require that a magic cookie be provided before packets can be written
					to the file, so this property should be set before calling 
					AudioFileWriteBytes()/AudioFileWritePackets() if a magic cookie exists.
    @constant   kAudioFilePropertyAudioDataByteCount 
					a UInt64 that indicates the number of bytes of audio data contained in the file
    @constant   kAudioFilePropertyAudioDataPacketCount 
					a UInt64 that indicates the number of packets of audio data contained in the file
    @constant   kAudioFilePropertyMaximumPacketSize 
					a UInt32 that indicates the maximum size of a packet for the data contained in the file
    @constant   kAudioFilePropertyDataOffset 
					a SInt64 that indicates the byte offset in the file of the audio data.
    @constant   kAudioFilePropertyChannelLayout 
					An AudioChannelLayout struct.
    @constant   kAudioFilePropertyDeferSizeUpdates 
					A UInt32. If 1, then updating the files sizes in the header is not done for every write, 
					but deferred until the file is read, optimized or closed. This is more efficient, but less safe
					since, if the application crashes before the size is updated, the file may not be readable.
					The default value is one, it doesn't update the header.
    @constant   kAudioFilePropertyDataFormatName 
					This is deprecated. Use kAudioFormatProperty_FormatName in AudioFormat.h instead.
    @constant   kAudioFilePropertyMarkerList 
					access the list of markers defined in the file. returns an AudioFileMarkerList.
					The CFStringRefs in the returned structs must be released by the client.
					(available in 10.2.4 and later)
    @constant   kAudioFilePropertyRegionList 
					access the list of regions defined in the file. returns an Array of AudioFileRegions.
					The CFStringRefs in the returned structs must be released by the client.
					(available in 10.2.4 and later)
    @constant   kAudioFilePropertyPacketToFrame 
					pass a AudioFramePacketTranslation with mPacket filled out and get mFrame back. mFrameOffsetInPacket is ignored.
    @constant   kAudioFilePropertyFrameToPacket 
					pass a AudioFramePacketTranslation with mFrame filled out and get mPacket and mFrameOffsetInPacket back.
					
    @constant   kAudioFilePropertyRestrictsRandomAccess
					A UInt32 indicating whether an Audio File contains packets that cannot be used as random access points.
					A value of 0 indicates that any packet can be used as a random access point, i.e. that a decoder can start decoding with any packet.
					A value of 1 indicates that some packets cannot be used as random access points, i.e. that kAudioFilePropertyPacketToRollDistance must be employed in order to identify an appropriate initial packet for decoding.
    @constant   kAudioFilePropertyPacketToRollDistance
					Pass an AudioPacketRollDistanceTranslation with mPacket filled out and get mRollDistance back.
					The roll distance indicates the count of packets that must be decoded prior to the packet with the specified number in order to achieve the best practice for the decoding of that packet.
					For file types for which a minimal roll distance is prohibitively expensive to determine per packet, the value returned may be derived from an upper bound for all packet roll distances.
					If the value of kAudioFilePropertyRestrictsRandomAccess is 1, either kAudioFilePropertyPacketToRollDistance
					or kAudioFilePropertyPacketToDependencyInfo must be used in order to identify an appropriate random access point.
					If the value of kAudioFilePropertyRestrictsRandomAccess is 0, kAudioFilePropertyPacketToRollDistance can be used in
					order to identify the best available random access point, which may be prior to the specified packet even if the specified
					packet can be used as a random access point.
    @constant   kAudioFilePropertyPreviousIndependentPacket
    @constant   kAudioFilePropertyNextIndependentPacket
					Pass an AudioIndependentPacketTranslation with mPacket filled out and get mIndependentlyDecodablePacket back.
					A value of -1 means that no independent packet is present in the stream in the direction of interest. Otherwise,
					for kAudioFilePropertyPreviousIndependentPacket, mIndependentlyDecodablePacket will be less than mPacket, and
					for kAudioFilePropertyNextIndependentPacket, mIndependentlyDecodablePacket will be greater than mPacket.
    @constant   kAudioFilePropertyPacketToDependencyInfo
					Pass an AudioPacketDependencyInfoTranslation with mPacket filled out and get mIsIndependentlyDecodable
					and mPrerollPacketCount back.
					A value of 0 for mIsIndependentlyDecodable indicates that the specified packet is not independently decodable.
					A value of 1 for mIsIndependentlyDecodable indicates that the specified packet is independently decodable.
					For independently decodable packets, mPrerollPacketCount indicates the count of packets that must be decoded
					after the packet with the specified number in order to refresh the decoder.
					If the value of kAudioFilePropertyRestrictsRandomAccess is 1, either kAudioFilePropertyPacketToRollDistance or
					kAudioFilePropertyPacketToDependencyInfo must be used in order to identify an appropriate random access point.

	@constant	kAudioFilePropertyPacketToByte
					pass an AudioBytePacketTranslation struct with mPacket filled out and get mByte back.
					mByteOffsetInPacket is ignored. If the mByte value is an estimate then 
					kBytePacketTranslationFlag_IsEstimate will be set in the mFlags field.
	@constant	kAudioFilePropertyByteToPacket
					pass an AudioBytePacketTranslation struct with mByte filled out and get mPacket and
					mByteOffsetInPacket back. If the mPacket value is an estimate then 
					kBytePacketTranslationFlag_IsEstimate will be set in the mFlags field.
					
    @constant   kAudioFilePropertyChunkIDs 
					returns an array of OSType four char codes for each kind of chunk in the file.
    @constant   kAudioFilePropertyInfoDictionary 
					returns a CFDictionary filled with information about the data contained in the file. 
					See dictionary key constants already defined for info string types. 
					AudioFileComponents are free to add keys to the dictionaries that they return for this property...
					caller is responsible for releasing the CFObject
    @constant   kAudioFilePropertyPacketTableInfo 
					Gets or sets an AudioFilePacketTableInfo struct for the file types that support it.
					When setting, the sum of mNumberValidFrames, mPrimingFrames and mRemainderFrames must be the same as the total
					number of frames in all packets. If not you will get a kAudio_ParamError. The best way to ensure this is to get the value of
					the property and make sure the sum of the three values you set has the same sum as the three values you got.
	@constant	kAudioFilePropertyPacketSizeUpperBound
					a UInt32 for the theoretical maximum packet size in the file (without actually scanning
					the whole file to find the largest packet, as may happen with kAudioFilePropertyMaximumPacketSize).
    @constant   kAudioFilePropertyPacketRangeByteCountUpperBound
					Pass an AudioPacketRangeByteCountTranslation with mPacket and mPacketCount filled out
					and get mByteCountUpperBound back. The value of mByteCountUpperBound can be used to allocate a buffer
					for use with AudioFileReadPacketData in order to accommodate the entire packet range.
					May require scanning in order to obtain the requested information, but even if so, no scanning will occur
					beyond the last packet in the specified range.
					For file formats in which packets are directly accessible and stored both contiguously and byte-aligned,
					the returned upper bound will be equal to the total size of the packets in the range. Otherwise the
					upper bound may reflect per-packet storage overhead.
	@constant	kAudioFilePropertyReserveDuration
					The value is a Float64 of the duration in seconds of data that is expected to be written.
					Setting this property before any data has been written reserves space in the file header for a packet table 
					and/or other information so that it can appear before the audio data. Otherwise the packet table may get written at the 
					end of the file, preventing the file from being streamable.
	@constant	kAudioFilePropertyEstimatedDuration
					The value is a Float64 representing an estimated duration in seconds. If duration can be calculated without scanning the entire file,
					or all the audio data packets have been scanned, the value will accurately reflect the duration of the audio data. 
	@constant	kAudioFilePropertyBitRate
					Returns the bit rate for the audio data as a UInt32. For some formats this will be approximate.
	@constant	kAudioFilePropertyID3Tag
					A void * pointing to memory set up by the caller to contain a fully formatted ID3 tag (get/set v2.2, v2.3, or v2.4, v1 get only).
					The ID3 tag is not manipulated in anyway either for read or write. 
					When setting, this property must be called before calling AudioFileWritePackets.
	@constant	kAudioFilePropertySourceBitDepth
					For encoded data this property returns the bit depth of the source as an SInt32, if known.
					The bit depth is expressed as a negative number if the source was floating point, e.g. -32 for float, -64 for double.
	@constant	kAudioFilePropertyAlbumArtwork
					returns a CFDataRef filled with the Album Art or NULL. 
					The caller is responsible for releasing a non-NULL CFDataRef.
					In order to parse the contents of the data, CGImageSourceCreateWithData may be used.
    @constant	kAudioFilePropertyAudioTrackCount
                    a UInt32 that indicates the number of audio tracks contained in the file. (get property only)
    @constant	kAudioFilePropertyUseAudioTrack
                    a UInt32 that indicates the number of audio tracks contained in the file. (set property only)
 */
CF_ENUM(AudioFilePropertyID)
{
	kAudioFilePropertyFileFormat			=	'ffmt',
	kAudioFilePropertyDataFormat			=	'dfmt',
	kAudioFilePropertyIsOptimized			=	'optm',
	kAudioFilePropertyMagicCookieData		=	'mgic',
	kAudioFilePropertyAudioDataByteCount	=	'bcnt',
	kAudioFilePropertyAudioDataPacketCount	=	'pcnt',
	kAudioFilePropertyMaximumPacketSize		=	'psze',
	kAudioFilePropertyDataOffset			=	'doff',
	kAudioFilePropertyChannelLayout			=	'cmap',
	kAudioFilePropertyDeferSizeUpdates		=	'dszu',
	kAudioFilePropertyDataFormatName		=	'fnme',
	kAudioFilePropertyMarkerList			=	'mkls',
	kAudioFilePropertyRegionList			=	'rgls',
	kAudioFilePropertyPacketToFrame			=	'pkfr',
	kAudioFilePropertyFrameToPacket			=	'frpk',
	kAudioFilePropertyRestrictsRandomAccess	=	'rrap',
	kAudioFilePropertyPacketToRollDistance	=	'pkrl',
	kAudioFilePropertyPreviousIndependentPacket	= 'pind',
	kAudioFilePropertyNextIndependentPacket	=	'nind',
	kAudioFilePropertyPacketToDependencyInfo =	'pkdp',
	kAudioFilePropertyPacketToByte			=	'pkby',
	kAudioFilePropertyByteToPacket			=	'bypk',
	kAudioFilePropertyChunkIDs				=	'chid',
	kAudioFilePropertyInfoDictionary        =	'info',
	kAudioFilePropertyPacketTableInfo		=	'pnfo',
	kAudioFilePropertyFormatList			=	'flst',
	kAudioFilePropertyPacketSizeUpperBound  =	'pkub',
	kAudioFilePropertyPacketRangeByteCountUpperBound = 'prub',
	kAudioFilePropertyReserveDuration		=	'rsrv',
	kAudioFilePropertyEstimatedDuration		=	'edur',
	kAudioFilePropertyBitRate				=	'brat',
	kAudioFilePropertyID3Tag				=	'id3t',
	kAudioFilePropertySourceBitDepth		=	'sbtd',
	kAudioFilePropertyAlbumArtwork			=	'aart',
    kAudioFilePropertyAudioTrackCount       =   'atct',
	kAudioFilePropertyUseAudioTrack			=	'uatk'
};


/*!
    @function	AudioFileGetPropertyInfo
    @abstract   Get information about the size of a property of an AudioFile  and whether it can be set.
    @param      inAudioFile			an AudioFileID.
    @param      inPropertyID		an AudioFileProperty constant.
    @param      outDataSize			the size in bytes of the current value of the property. In order to get the property value, 
									you will need a buffer of this size.
    @param      isWritable			will be set to 1 if writable, or 0 if read only.
    @result							returns noErr if successful.
*/
extern OSStatus
AudioFileGetPropertyInfo(		AudioFileID				inAudioFile,
                                AudioFilePropertyID		inPropertyID,
                                UInt32 * __nullable		outDataSize,
                                UInt32 * __nullable		isWritable)			API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));
                                
/*!
    @function	AudioFileGetProperty
    @abstract   Copies the value for a property of an AudioFile into a buffer.
    @param      inAudioFile			an AudioFileID.
    @param      inPropertyID		an AudioFileProperty constant.
    @param      ioDataSize			on input the size of the outPropertyData buffer. On output the number of bytes written to the buffer.
    @param      outPropertyData		the buffer in which to write the property data.
    @result							returns noErr if successful.
*/
extern OSStatus
AudioFileGetProperty(	AudioFileID				inAudioFile,
                        AudioFilePropertyID		inPropertyID,
                        UInt32					*ioDataSize,
                        void					*outPropertyData)			API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));
                        
/*!
    @function	AudioFileSetProperty
    @abstract   Sets the value for a property of an AudioFile .
    @param      inAudioFile			an AudioFileID.
    @param      inPropertyID		an AudioFileProperty constant.
    @param      inDataSize			the size of the property data.
    @param      inPropertyData		the buffer containing the property data.
    @result							returns noErr if successful.
*/
extern OSStatus
AudioFileSetProperty(	AudioFileID				inAudioFile,
                        AudioFilePropertyID		inPropertyID,
                        UInt32					inDataSize,
                        const void				*inPropertyData)			API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));



//=============================================================================
//	Audio File Global Info Properties
//=============================================================================

/*!
    @enum		Audio File Global Info Properties
    @abstract   constants for AudioFileGetGlobalInfo properties
    @constant   kAudioFileGlobalInfo_ReadableTypes
					No specifier needed. Must be set to NULL.
					Returns an array of UInt32 containing the file types 
					(i.e. AIFF, WAVE, etc) that can be opened for reading.
    @constant   kAudioFileGlobalInfo_WritableTypes
					No specifier needed. Must be set to NULL.
					Returns an array of UInt32 containing the file types 
					(i.e. AIFF, WAVE, etc) that can be opened for writing.
    @constant   kAudioFileGlobalInfo_FileTypeName
					Specifier is a pointer to a AudioFileTypeID containing a file type.
					Returns a CFString containing the name for the file type. 
    @constant   kAudioFileGlobalInfo_AvailableFormatIDs
					Specifier is a pointer to a AudioFileTypeID containing a file type.
					Returns a array of format IDs for formats that can be read. 
    @constant   kAudioFileGlobalInfo_AvailableStreamDescriptionsForFormat
					Specifier is a pointer to a AudioFileTypeAndFormatID struct defined below.
					Returns an array of AudioStreamBasicDescriptions which have all of the 
					formats for a particular file type and format ID. The AudioStreamBasicDescriptions
					have the following fields filled in: mFormatID, mFormatFlags, mBitsPerChannel
					writing new files.
					
					
    @constant   kAudioFileGlobalInfo_AllExtensions
					No specifier needed. Must be set to NULL.
					Returns a CFArray of CFStrings containing all file extensions 
					that are recognized. The array be used when creating an NSOpenPanel.

    @constant   kAudioFileGlobalInfo_AllHFSTypeCodes
					No specifier needed. Must be set to NULL.
					Returns an array of HFSTypeCode's containing all HFSTypeCodes
					that are recognized.

    @constant   kAudioFileGlobalInfo_AllUTIs
					No specifier needed. Must be set to NULL.
					Returns a CFArray of CFString of all Universal Type Identifiers
					that are recognized by AudioFile. 
					The caller is responsible for releasing the CFArray.

    @constant   kAudioFileGlobalInfo_AllMIMETypes
					No specifier needed. Must be set to NULL.
					Returns a CFArray of CFString of all MIME types
					that are recognized by AudioFile. 
					The caller is responsible for releasing the CFArray.


    @constant   kAudioFileGlobalInfo_ExtensionsForType
					Specifier is a pointer to a AudioFileTypeID containing a file type.
					Returns a CFArray of CFStrings containing the file extensions 
					that are recognized for this file type. 

    @constant   kAudioFileGlobalInfo_HFSTypeCodesForType
					Specifier is a pointer to an AudioFileTypeID.
					Returns an array of HFSTypeCodes corresponding to that file type.
					The first type in the array is the preferred one for use when

    @constant   kAudioFileGlobalInfo_UTIsForType
					Specifier is a pointer to an AudioFileTypeID.
					Returns a CFArray of CFString of all Universal Type Identifiers
					that are recognized by the file type. 
					The caller is responsible for releasing the CFArray.

    @constant   kAudioFileGlobalInfo_MIMETypesForType
					Specifier is a pointer to an AudioFileTypeID.
					Returns a CFArray of CFString of all MIME types
					that are recognized by the file type. 
					The caller is responsible for releasing the CFArray.

	these are inverses of the above:

    @constant   kAudioFileGlobalInfo_TypesForExtension
					Specifier is a CFStringRef containing a file extension.
					Returns an array of all AudioFileTypeIDs that support the extension. 
	
    @constant   kAudioFileGlobalInfo_TypesForHFSTypeCode
					Specifier is an HFSTypeCode.
					Returns an array of all AudioFileTypeIDs that support the HFSTypeCode. 

    @constant   kAudioFileGlobalInfo_TypesForUTI
					Specifier is a CFStringRef containing a Universal Type Identifier.
					Returns an array of all AudioFileTypeIDs that support the UTI. 

    @constant   kAudioFileGlobalInfo_TypesForMIMEType
					Specifier is a CFStringRef containing a MIME Type.
					Returns an array of all AudioFileTypeIDs that support the MIME type. 

*/
CF_ENUM(AudioFilePropertyID)
{
	kAudioFileGlobalInfo_ReadableTypes							= 'afrf',
	kAudioFileGlobalInfo_WritableTypes							= 'afwf',
	kAudioFileGlobalInfo_FileTypeName							= 'ftnm',
	kAudioFileGlobalInfo_AvailableStreamDescriptionsForFormat	= 'sdid',
	kAudioFileGlobalInfo_AvailableFormatIDs						= 'fmid',

	kAudioFileGlobalInfo_AllExtensions							= 'alxt',
	kAudioFileGlobalInfo_AllHFSTypeCodes						= 'ahfs',
	kAudioFileGlobalInfo_AllUTIs								= 'auti',
	kAudioFileGlobalInfo_AllMIMETypes							= 'amim',

	kAudioFileGlobalInfo_ExtensionsForType						= 'fext',
	kAudioFileGlobalInfo_HFSTypeCodesForType					= 'fhfs',
	kAudioFileGlobalInfo_UTIsForType							= 'futi',
	kAudioFileGlobalInfo_MIMETypesForType						= 'fmim',
	
	kAudioFileGlobalInfo_TypesForMIMEType						= 'tmim',
	kAudioFileGlobalInfo_TypesForUTI							= 'tuti',
	kAudioFileGlobalInfo_TypesForHFSTypeCode					= 'thfs',
	kAudioFileGlobalInfo_TypesForExtension						= 'text'
};


/*!
    @struct		AudioFileTypeAndFormatID
    @abstract   This is used as a specifier for kAudioFileGlobalInfo_AvailableStreamDescriptions
    @discussion This struct is used to specify a desired audio file type and data format ID  so
				that a list of stream descriptions of available formats can be obtained.
    @var        mFileType
					a four char code for the file type such as kAudioFileAIFFType, kAudioFileCAFType, etc.
    @var        mFormatID
					a four char code for the format ID such as kAudioFormatLinearPCM, kAudioFormatMPEG4AAC, etc.
*/
struct AudioFileTypeAndFormatID
{
	AudioFileTypeID  mFileType;
	UInt32			mFormatID;
};
typedef struct AudioFileTypeAndFormatID AudioFileTypeAndFormatID;


/*!
    @function	AudioFileGetGlobalInfoSize
    @abstract   Get the size of a global property.
    @param      inPropertyID		an AudioFileGlobalInfo property constant.
    @param      inSpecifierSize		The size of the specifier data.
    @param      inSpecifier			A specifier is a buffer of data used as an input argument to some of the global info properties.
    @param      outDataSize			the size in bytes of the current value of the property. In order to get the property value, 
									you will need a buffer of this size.
    @result							returns noErr if successful.
*/
extern OSStatus
AudioFileGetGlobalInfoSize(		AudioFilePropertyID		inPropertyID,
                                UInt32					inSpecifierSize,
                                void * __nullable		inSpecifier,
                                UInt32					*outDataSize)		API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));
                                
/*!
    @function	AudioFileGetGlobalInfo
    @abstract   Copies the value for a global property into a buffer.
    @param      inPropertyID		an AudioFileGlobalInfo property constant.
    @param      inSpecifierSize		The size of the specifier data.
    @param      inSpecifier			A specifier is a buffer of data used as an input argument to some of the global info properties.
    @param      ioDataSize			on input the size of the outPropertyData buffer. On output the number of bytes written to the buffer.
    @param      outPropertyData		the buffer in which to write the property data.
    @result							returns noErr if successful.
*/
extern OSStatus
AudioFileGetGlobalInfo(			AudioFilePropertyID		inPropertyID,
								UInt32					inSpecifierSize,
                                void * __nullable		inSpecifier,
                    		    UInt32					*ioDataSize,
                    		    void					*outPropertyData)	API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));

#pragma mark - Deprecated
	
#if !TARGET_OS_IPHONE
struct FSRef;
/*!
    @function	AudioFileCreate
    @abstract   creates a new audio file
    @discussion	creates a new audio file located in the parent directory 
                      provided. Upon success, an AudioFileID is returned which can
                      be used for subsequent calls to the AudioFile APIs.
    @param inParentRef		an FSRef to the directory where  the new file should be created.
    @param inFileName		a CFStringRef containing the name of the file to be created.
    @param inFileType		an AudioFileTypeID indicating the type of audio file to create.
    @param inFormat			an AudioStreamBasicDescription describing the data format that will be
							added to the audio file.
    @param inFlags			relevant flags for creating/opening the file. 
    @param outNewFileRef	if successful, the FSRef of the newly created file.
    @param outAudioFile		if successful, an AudioFileID that can be used for subsequent AudioFile calls.
    @result					returns noErr if successful.
	@deprecated				in Mac OS X 10.6, see AudioFileCreateWithURL
*/
extern OSStatus	
AudioFileCreate (	const struct FSRef					*inParentRef, 
                    CFStringRef							inFileName,
                    AudioFileTypeID						inFileType,
                    const AudioStreamBasicDescription	*inFormat,
                    AudioFileFlags						inFlags,
                    struct FSRef						*outNewFileRef,
                    AudioFileID	__nullable * __nonnull	outAudioFile)		API_DEPRECATED("no longer supported", macos(10.2, 10.6)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
    @function				AudioFileInitialize
    @abstract				Write over an existing audio file.
    @discussion				Use AudioFileInitialize to wipe clean an existing audio file
							and prepare it to be populated with new data.
    @param inFileRef		the FSRef of an existing audio file.
    @param inFileType		an AudioFileTypeID indicating the type of audio file to initialize the file to. 
    @param inFormat			an AudioStreamBasicDescription describing the data format that will be
							added to the audio file.
    @param inFlags			flags for creating/opening the file. Currently zero.
    @param outAudioFile		upon success, an AudioFileID that can be used for subsequent
							AudioFile calls.
    @result					returns noErr if successful.
	@deprecated				in Mac OS X 10.6, see AudioFileCreateWithURL
*/
extern OSStatus	
AudioFileInitialize (	const struct FSRef					*inFileRef,
                        AudioFileTypeID						inFileType,
                        const AudioStreamBasicDescription	*inFormat,
                        AudioFileFlags						inFlags,
                        AudioFileID	__nullable * __nonnull	outAudioFile)	API_DEPRECATED("no longer supported", macos(10.2, 10.6)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
    @function				AudioFileOpen
    @abstract				Open an existing audio file.
    @discussion				Open an existing audio file for reading or reading and writing.
    @param inFileRef		the FSRef of an existing audio file.
    @param inPermissions	use the permission constants
    @param inFileTypeHint	For files which have no filename extension and whose type cannot be easily or
							uniquely determined from the data (ADTS,AC3), this hint can be used to indicate the file type. 
							Otherwise you can pass zero for this. The hint is only used on OS versions 10.3.1 or greater.
							For OS versions prior to that, opening files of the above description will fail.
    @param outAudioFile		upon success, an AudioFileID that can be used for subsequent
							AudioFile calls.
    @result					returns noErr if successful.
	@deprecated				in Mac OS X 10.6, see AudioFileOpenURL
*/
extern OSStatus	
AudioFileOpen (	const struct FSRef		*inFileRef,
                AudioFilePermissions	inPermissions,
                AudioFileTypeID			inFileTypeHint,
                AudioFileID	__nullable * __nonnull	outAudioFile)			API_DEPRECATED("no longer supported", macos(10.2, 10.6)) API_UNAVAILABLE(ios, watchos, tvos);

#endif
	
#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioFile_h
#else
#include <AudioToolboxCore/AudioFile.h>
#endif
// ==========  AudioToolbox.framework/Headers/AUParameters.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AUParameters.h>)
/*!
	@file		AUParameters.h
 	@framework	AudioToolbox.framework
 	@copyright	(c) 2015 Apple, Inc. All rights reserved.

	@brief		Objects representing an AUAudioUnit's tree of parameters.
*/

#ifndef AudioToolbox_AUParameters_h
#define AudioToolbox_AUParameters_h
#ifdef __OBJC2__

#import <AudioToolbox/AUComponent.h>
#import <AudioToolbox/AudioUnitProperties.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AUParameter;

// =================================================================================================
// typedefs

/*!	@typedef	AUValue
	@brief		A value of an audio unit parameter.
*/
typedef float AUValue;

/*!	@typedef	AUParameterAddress
	@brief		Numeric identifier for audio unit parameter.
	@discussion
		Note that parameter addresses are not necessarily persistent, unless the individual audio
		unit documents a promise to maintain its addressing scheme. Hosts should bind to parameters'
		key paths.
*/
typedef uint64_t AUParameterAddress;

/*!	@enum		AUParameterAutomationEventType
	@brief		Identifies the different types of parameter automation events.
	
	@discussion
		Audio Units may generate parameter changes from their user interfaces. Hosts may attach
		significance to the beginning and end of a UI gesture (typically touching and releasing
		a fader). These gestures are conveyed through these types of automation events.
	
	@constant AUParameterAutomationEventTypeValue
		The event contains an updated value for the parameter.
	@constant AUParameterAutomationEventTypeTouch
		The event marks an initial "touch" gesture on a UI element.
	@constant AUParameterAutomationEventTypeRelease
		The event marks a final "release" gesture on a UI element.
*/
typedef NS_ENUM(uint32_t, AUParameterAutomationEventType) {
	AUParameterAutomationEventTypeValue = 0,
	AUParameterAutomationEventTypeTouch = 1,
	AUParameterAutomationEventTypeRelease = 2
};

/*!	@typedef	AURecordedParameterEvent
	@brief		An event recording the changing of a parameter at a particular host time.
*/
typedef struct AURecordedParameterEvent {
	uint64_t hostTime;				///< The host time at which the event occurred.
	AUParameterAddress address;		///< The address of the parameter whose value changed.
	AUValue value;					///< The value of the parameter at that time.
} AURecordedParameterEvent;

/*!	@typedef	AUParameterAutomationEvent
	@brief		An event recording the changing of a parameter, possibly including events
				such as touch and release gestures, at a particular host time.
*/
typedef struct AUParameterAutomationEvent {
	uint64_t hostTime;				///< The host time at which the event occurred.
	AUParameterAddress address;		///< The address of the parameter whose value changed.
	AUValue value;					///< The value of the parameter at that time.
	AUParameterAutomationEventType eventType; ///< The type of the event.
	uint64_t reserved;
} AUParameterAutomationEvent;

/*!	@typedef	AUParameterObserver
	@brief		A block called to signal that the value of a parameter has changed.
	@discussion	
		See the discussion of -[AUParameterNode tokenByAddingParameterObserver:].
	@param address
		The address of the parameter whose value changed.
	@param value
		The current value of the parameter.
*/
typedef void (^AUParameterObserver)(AUParameterAddress address, AUValue value);

/*!	@typedef	AUParameterRecordingObserver
	@brief		A block called to record parameter changes as automation events.
	@discussion
		See the discussion of -[AUParameterNode tokenByAddingParameterRecordingObserver:].
	@param numberEvents
		The number of events being delivered.
	@param events
		The events being delivered.
*/
typedef void (^AUParameterRecordingObserver)(NSInteger numberEvents, const AURecordedParameterEvent *events);

/*!	@typedef	AUParameterAutomationObserver
	@brief		A block called to record parameter changes as automation events.
	@discussion
		See the discussion of -[AUParameterNode tokenByAddingParameterAutomationObserver:].
	@param numberEvents
		The number of events being delivered.
	@param events
		The events being delivered.
*/
typedef void (^AUParameterAutomationObserver)(NSInteger numberEvents, const AUParameterAutomationEvent *events);

/*!	@typedef	AUParameterObserverToken
	@brief		A token representing an installed AUParameterObserver, AUParameterRecordingObserver,
				or AUParameterAutomationObserver.
*/
typedef void *AUParameterObserverToken;

// =================================================================================================

/*!	@class		AUParameterNode
	@brief		A node in an audio unit's tree of parameters.
	@discussion
		Nodes are instances of either AUParameterGroup or AUParameter.
*/
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface AUParameterNode : NSObject

/*!	@property	identifier
	@brief		A non-localized, permanent name for a parameter or group.
	@discussion
		The identifier must be unique for all child nodes under any given parent. From release to
		release, an audio unit must not change its parameters' identifiers; this will invalidate any
		hosts' documents that refer to the parameters.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *identifier;

/*!	@property	keyPath
	@brief		Generated by concatenating the identifiers of a node's parents with its own.
	@discussion
		Unless an audio unit specifically documents that its parameter addresses are stable and
		persistent, hosts, when recording parameter values, should bind to the keyPath.

		The individual node identifiers in a key path are separated by periods. (".")
		
		Passing a node's keyPath to -[tree valueForKeyPath:] should return the same node.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *keyPath;

/*!	@property	displayName
	@brief		A localized name to display for the parameter.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *displayName;

/*!	@method		displayNameWithLength:
	@brief		A version of displayName possibly abbreviated to the given desired length, in characters.
	@discussion
		The default implementation simply returns displayName.
*/
- (NSString *)displayNameWithLength:(NSInteger)maximumLength;

/*!	@method	tokenByAddingParameterObserver:
	@brief	Add an observer for a parameter or all parameters in a group/tree.
	@discussion
		An audio unit view can use an AUParameterObserver to be notified of changes
		to a single parameter, or to all parameters in a group/tree.
		
		These callbacks are throttled so as to limit the rate of redundant notifications
		in the case of frequent changes to a single parameter.
		
		This block is called in an arbitrary thread context. It is responsible for thread-safety.
		It must not make any calls to add or remove other observers, including itself;
		this will deadlock.
		
		An audio unit's implementation should interact with the parameter object via
		implementorValueObserver and implementorValueProvider.
	@param observer
		A block to call after the value of a parameter has changed.
	@return
		A token which can be passed to removeParameterObserver: or to -[AUParameter setValue:originator:]
*/
- (AUParameterObserverToken)tokenByAddingParameterObserver:(AUParameterObserver)observer;

/*!	@method tokenByAddingParameterRecordingObserver:
	@brief	Add a recording observer for a parameter or all parameters in a group/tree.
	@discussion
		This is a variant of tokenByAddingParameterAutomationObserver where the callback receives
		AURecordedParameterEvents instead of AUParameterAutomationEvents.
		
		This will be deprecated in favor of tokenByAddingParameterAutomationObserver in a future
		release.
*/
- (AUParameterObserverToken)tokenByAddingParameterRecordingObserver:(AUParameterRecordingObserver)observer;

/*!	@method tokenByAddingParameterAutomationObserver:
	@brief	Add a recording observer for a parameter or all parameters in a group/tree.
	@discussion
		An audio unit host can use an AUParameterAutomationObserver or AUParameterRecordingObserver
		to capture a series of changes to a parameter value, including the timing of the events, as
		generated by a UI gesture in a view, for example.
		
		Unlike AUParameterObserver, these callbacks are not throttled.
		
		This block is called in an arbitrary thread context. It is responsible for thread-safety.
		It must not make any calls to add or remove other observers, including itself;
		this will deadlock.
		
		An audio unit's engine should interact with the parameter object via
		implementorValueObserver and implementorValueProvider.
	@param observer
		A block to call to record the changing of a parameter value.
	@return
		A token which can be passed to removeParameterObserver: or to -[AUParameter
		setValue:originator:]
*/
- (AUParameterObserverToken)tokenByAddingParameterAutomationObserver:(AUParameterAutomationObserver)observer API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!	@method removeParameterObserver:
	@brief	Remove an observer created with tokenByAddingParameterObserver,
		tokenByAddingParameterRecordingObserver, or tokenByAddingParameterAutomationObserver.
	@discussion
		This call will remove the callback corresponding to the supplied token. Note that this
		will block until any callbacks currently in flight have completed.
*/
- (void)removeParameterObserver:(AUParameterObserverToken)token;

@end

// =================================================================================================

/*!	@class	AUParameterGroup
	@brief	A group of related parameters.
	@discussion
		A parameter group is KVC-compliant for its children; e.g. valueForKey:@"volume" will
		return a child parameter whose identifier is "volume".
*/
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface AUParameterGroup : AUParameterNode <NSSecureCoding>

/// The group's child nodes (AUParameterGroupNode).
@property (NS_NONATOMIC_IOSONLY, readonly) NSArray<AUParameterNode *> *children;

/// Returns a flat array of all parameters in the group, including those in child groups.
@property (NS_NONATOMIC_IOSONLY, readonly) NSArray<AUParameter *> *allParameters;

@end

// =================================================================================================

/*!	@class	AUParameterTree
	@brief	The top level group node, representing all of an audio unit's parameters.
	@discussion
		An audio unit's parameters are organized into a tree containing groups and parameters.
		Groups may be nested.
		
		The tree is KVO-compliant. For example, if the tree contains a group named "LFO" ,
		containing a parameter named rate, then "LFO.rate" refers to that parameter object, and
		"LFO.rate.value" refers to that parameter's value.

		An audio unit may choose to dynamically rearrange the tree. When doing so, it must
		issue a KVO notification on the audio unit's parameterTree property. The tree's elements are
		mostly immutable (except for values and implementor hooks); the only way to modify them
		is to publish a new tree.
*/
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface AUParameterTree : AUParameterGroup <NSSecureCoding>

/*!	@method	parameterWithAddress:
	@brief	Search a tree for a parameter with a specific address.
	@return
		The parameter corresponding to the supplied address, or nil if no such parameter exists.
*/
- (AUParameter *__nullable)parameterWithAddress:(AUParameterAddress)address;

/*!	@method	parameterWithID:scope:element:
	@brief	Search a tree for a specific v2 audio unit parameter.
	@discussion
		V2 audio units publish parameters identified by a parameter ID, scope, and element.
		A host that knows that it is dealing with a v2 unit can locate parameters using this method,
		for example, for the Apple-supplied system audio units.
	@return
		The parameter corresponding to the supplied ID/scope/element, or nil if no such parameter
		exists, or if the audio unit is not a v2 unit.
*/
- (AUParameter *__nullable)parameterWithID:(AudioUnitParameterID)paramID scope:(AudioUnitScope)scope element:(AudioUnitElement)element;

@end

// =================================================================================================
// AUParameter

/*!	@class	AUParameter
	@brief	A node representing a single parameter.
*/
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface AUParameter : AUParameterNode <NSSecureCoding>

/// The parameter's minimum value.
@property (NS_NONATOMIC_IOSONLY, readonly) AUValue minValue;

/// The parameter's maximum value.
@property (NS_NONATOMIC_IOSONLY, readonly) AUValue maxValue;

/// The parameter's unit of measurement.
@property (NS_NONATOMIC_IOSONLY, readonly) AudioUnitParameterUnit unit;

/// A localized name for the parameter's unit. Supplied by the AU if kAudioUnitParameterUnit_CustomUnit; else by the framework.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSString *unitName;

/// Various details of the parameter.
@property (NS_NONATOMIC_IOSONLY, readonly) AudioUnitParameterOptions flags;

/// The parameter's address.
@property (NS_NONATOMIC_IOSONLY, readonly) AUParameterAddress address;

/// For parameters with kAudioUnitParameterUnit_Indexed, localized strings corresponding
///	to the values.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSArray<NSString *> *valueStrings;

/*!	@brief		Parameters whose values may change as a side effect of this parameter's value
				changing.
	@discussion
		Each array value is an NSNumber representing AUParameterAddress.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSArray<NSNumber *> *dependentParameters;

/// The parameter's current value.
@property (NS_NONATOMIC_IOSONLY) AUValue value;

/// Set the parameter's value, avoiding redundant notifications to the originator.
- (void)setValue:(AUValue)value originator:(AUParameterObserverToken __nullable)originator;

/// Convenience for setValue:originator:atHostTime:eventType:
- (void)setValue:(AUValue)value originator:(AUParameterObserverToken __nullable)originator atHostTime:(uint64_t)hostTime;

/*!	@brief	Set the parameter's value, preserving the host time of the gesture that initiated the
			change, and associating an event type such as touch/release.
	@discussion
		In general, this method should only be called from a user interface. It initiates a change
		to a parameter in a way that captures the gesture such that it can be recorded later --
		any AUParameterAutomationObservers will receive the host time and event type associated
		with the parameter change.

		From an audio playback engine, a host should schedule automated parameter changes through
		AUAudioUnit's scheduleParameterBlock.
*/
- (void)setValue:(AUValue)value originator:(AUParameterObserverToken __nullable)originator atHostTime:(uint64_t)hostTime eventType:(AUParameterAutomationEventType)eventType API_AVAILABLE(macos(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/*!	@brief Get a textual representation of a value for the parameter. Use value==nil to use the
		   current value. Bridged to the v2 property kAudioUnitProperty_ParameterStringFromValue.
	@discussion
		This is currently only supported for parameters whose flags include
		kAudioUnitParameterFlag_ValuesHaveStrings.
*/
- (NSString *)stringFromValue:(const AUValue *__nullable)value;

/*!	@brief Convert a textual representation of a value to a numeric one.
	@discussion
		This is currently only supported for parameters whose flags include
		kAudioUnitParameterFlag_ValuesHaveStrings.
*/
- (AUValue)valueFromString:(NSString *)string;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
#endif // AudioToolbox_AUParameters_h
#else
#include <AudioToolboxCore/AUParameters.h>
#endif
// ==========  AudioToolbox.framework/Headers/AudioSession.h
/*==================================================================================================
 File:       AudioToolbox/AudioSession.h
 
 Contains:   API for audio session services.
 
 Copyright:  (c) 2006 - 2013 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/
#if !defined(__AudioSession_h__)
#define __AudioSession_h__

//==================================================================================================

/*!
 @header AudioSession
 This header describes the API for audio session services.
 Note: As of iOS 7, this entire API has been deprecated in favor of AVAudioSession, part of the AVFoundation framework.
 */

//==================================================================================================
#pragma mark    Includes

#include <TargetConditionals.h>
#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
#if !TARGET_OS_IPHONE
#include <CoreAudio/AudioHardware.h>
#endif
#include <CoreFoundation/CoreFoundation.h>
#else
#include <AudioHardware.h>
#include <CFRunLoop.h>
#include <CFString.h>
#include <CFURL.h>
#endif

//==================================================================================================

#if defined(__cplusplus)
extern "C"
{
#endif

	//==================================================================================================
#pragma mark -
#pragma mark    AudioSession Error Constants
	
	/*!
	 @enum           AudioSession error codes
	 @abstract       Error codes returned from the AudioSession portion of the API.
	 @constant       kAudioSessionNoError
	 No error has occurred
	 @constant       kAudioSessionNotInitialized 
	 This error is returned when the AudioSessionInitialize function
	 was not called prior to calling any other AudioSession function.
	 @constant       kAudioSessionAlreadyInitialized 
	 This error is returned when you call AudioSessionInitialize more than once.
	 @constant       kAudioSessionInitializationError 
	 This error indicates an AudioSession initialization error.
	 @constant       kAudioSessionUnsupportedPropertyError 
	 The property is not supported.  This error code can also be used to 
	 indicate that a bad property value was passed in a SetProperty call,
	 an attempt was made to set a read-only property, an attempt was made to
	 read a write-only property, an attempt was made to read a property that
	 is only available by way of a property listener, or an attempt was made 
	 to set a listener on a property for which listeners are not supported.
	 @constant       kAudioSessionBadPropertySizeError 
	 The size of the property data was not correct.
	 @constant       kAudioSessionNotActiveError 
	 The operation failed because the AudioSession is not active.
	 Calling AudioSessionSetActive(true) first will fix this error in most cases.
	 @constant       kAudioSessionNoCategorySet
	 The requested operation failed because it requires that the session have had an
	 audio category explicitly set, and none was set.
	 @constant       kAudioSessionIncompatibleCategory
	 The requested operation failed because the AudioSession has an incompatible
	 category (e.g. attempting to play or record when the category is AudioProcessing) or
	 the session is not active.
	 @constant       kAudioSessionUnspecifiedError
	 An audio session unspecified error has occurred.
	 */
	enum
	{
		kAudioSessionNoError                                =  0,
		kAudioSessionNotInitialized                         = '!ini',
		kAudioSessionAlreadyInitialized                     = 'init',
		kAudioSessionInitializationError                    = 'ini?',
		kAudioSessionUnsupportedPropertyError               = 'pty?',
		kAudioSessionBadPropertySizeError                   = '!siz',
		kAudioSessionNotActiveError                         = '!act',
		kAudioServicesNoHardwareError                       = 'nohw',
		kAudioSessionNoCategorySet                          = '?cat',
		kAudioSessionIncompatibleCategory                   = '!cat',
		kAudioSessionUnspecifiedError                       = 'what'
	};
	
	//==================================================================================================
#pragma mark -
#pragma mark    AudioSession Types
	
	/*!
	 @typedef        AudioSessionPropertyID
	 @abstract       Type used for specifying an AudioSession property.
	 */
	typedef UInt32      AudioSessionPropertyID;
	
	//==================================================================================================
#pragma mark -
#pragma mark    AudioSession Interruption States
	
	/*!
	 @enum           AudioSession interruptions states
	 @abstract       These are used with the AudioSessionInterruptionListener to indicate
	 if an interruption begins or ends.
	 @constant       kAudioSessionBeginInterruption
	 Indicates that this AudioSession has just been interrupted.
	 @constant       kAudioSessionEndInterruption 
	 Indicates the end of an interruption.
	 */
	enum {
		kAudioSessionBeginInterruption  = 1,
		kAudioSessionEndInterruption    = 0
	};
	
	//==================================================================================================
#pragma mark -
#pragma mark    AudioSession Audio Categories
	
	/*!
	 @enum           AudioSession audio categories states
	 @abstract       These are used with as values for the kAudioSessionProperty_AudioCategory property
	 to indicate the audio category of the AudioSession.
	 @constant       kAudioSessionCategory_AmbientSound 
	 Use this category for background sounds such as rain, car engine noise, etc.  
	 Mixes with other music.
	 @constant       kAudioSessionCategory_SoloAmbientSound 
	 Use this category for background sounds.  Other music will stop playing.
	 @constant       kAudioSessionCategory_MediaPlayback 
	 Use this category for music tracks.
	 @constant       kAudioSessionCategory_RecordAudio 
	 Use this category when recording audio.
	 @constant       kAudioSessionCategory_PlayAndRecord 
	 Use this category when recording and playing back audio.
	 @constant       kAudioSessionCategory_AudioProcessing
	 Use this category when using a hardware codec or signal processor while
	 not playing or recording audio.
	 */
	enum {
		kAudioSessionCategory_AmbientSound               = 'ambi',
		kAudioSessionCategory_SoloAmbientSound           = 'solo',
		kAudioSessionCategory_MediaPlayback              = 'medi',
		kAudioSessionCategory_RecordAudio                = 'reca',
		kAudioSessionCategory_PlayAndRecord              = 'plar',
		kAudioSessionCategory_AudioProcessing            = 'proc'
	};
	
#pragma mark    AudioSession Audio Category Routing Overrides
	
	/*!
	 @enum           AudioSession audio category routing overrides
	 @abstract       These are used with as values for the kAudioSessionProperty_OverrideAudioRoute property.
	 @constant       kAudioSessionOverrideAudioRoute_None
	 No override.  Return audio routing to the default state for the current audio category.
	 @constant       kAudioSessionOverrideAudioRoute_Speaker 
	 Route audio output to speaker.  Use this override with the kAudioSessionCategory_PlayAndRecord
	 category, which by default routes the output to the receiver.
	 */
	enum {
		kAudioSessionOverrideAudioRoute_None    = 0,
		kAudioSessionOverrideAudioRoute_Speaker = 'spkr'
	};
	
	//==================================================================================================
#pragma mark    AudioSession reason codes for route change
	
	/*!
	 @enum           AudioSession reason codes for route change
	 @abstract       These are codes used when the kAudioSessionProperty_AudioRoute property changes
	 @constant       kAudioSessionRouteChangeReason_Unknown
	 The reason is unknown.
	 @constant       kAudioSessionRouteChangeReason_NewDeviceAvailable
	 A new device became available (e.g. headphones have been plugged in).
	 @constant       kAudioSessionRouteChangeReason_OldDeviceUnavailable
	 The old device became unavailable (e.g. headphones have been unplugged).
	 @constant       kAudioSessionRouteChangeReason_CategoryChange
	 The audio category has changed (e.g. kAudioSessionCategory_MediaPlayback
	 has been changed to kAudioSessionCategory_PlayAndRecord).
	 @constant       kAudioSessionRouteChangeReason_Override
	 The route has been overridden (e.g. category is kAudioSessionCategory_PlayAndRecord
	 and the output has been changed from the receiver, which is the default, to the speaker).
	 @constant       kAudioSessionRouteChangeReason_WakeFromSleep
	 The device woke from sleep.
	 @constant       kAudioSessionRouteChangeReason_NoSuitableRouteForCategory
	 Returned when there is no route for the current category (for instance RecordCategory 
	 but no input device)
	 @constant		 kAudioSessionRouteChangeReason_RouteConfigurationChange
	 Indicates that the set of input and/our output ports has not changed, but some aspect of their 
	 configuration has changed.  For example, a port's selected data source has changed.
	 */
	enum {
		kAudioSessionRouteChangeReason_Unknown = 0,
		kAudioSessionRouteChangeReason_NewDeviceAvailable = 1,
		kAudioSessionRouteChangeReason_OldDeviceUnavailable = 2,
		kAudioSessionRouteChangeReason_CategoryChange = 3,
		kAudioSessionRouteChangeReason_Override = 4,
		kAudioSessionRouteChangeReason_WakeFromSleep = 6,
		kAudioSessionRouteChangeReason_NoSuitableRouteForCategory = 7,
		kAudioSessionRouteChangeReason_RouteConfigurationChange = 8
	};
	
	// see documentation for kAudioSessionProperty_AudioRouteChange
	// Note: the string refers to "OutputDevice" for historical reasons.  Audio routes may contain zero or more inputs and 
	//      zero or more outputs.
#define kAudioSession_AudioRouteChangeKey_Reason    "OutputDeviceDidChange_Reason"
    
	// CFString version of kAudioSession_AudioRouteChangeKey_Reason.  This is more convenient to use than the raw string version.
	// Available in iOS 5.0 or greater          
	extern const CFStringRef kAudioSession_RouteChangeKey_Reason                API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
	// CFDictionary keys for kAudioSessionProperty_AudioRouteChange
	// Available in iOS 5.0 or greater      
	extern const CFStringRef   kAudioSession_AudioRouteChangeKey_PreviousRouteDescription  API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef   kAudioSession_AudioRouteChangeKey_CurrentRouteDescription   API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
	// CFDictionary keys for kAudioSessionProperty_AudioRouteDescription    
	// Available in iOS 5.0 or greater    
	extern const CFStringRef   kAudioSession_AudioRouteKey_Inputs   API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef   kAudioSession_AudioRouteKey_Outputs  API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
	// key(s) for the CFDictionary associated with each entry of the CFArrays returned by kAudioSession_AudioRouteKey_Inputs
	// and kAudioSession_AudioRouteKey_Outputs.  
	// Available in iOS 5.0 or greater        
	extern const CFStringRef   kAudioSession_AudioRouteKey_Type     API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
    
    
	/*!
	 @enum           AudioSession route input types
	 @abstract       These are the strings used with the kAudioSession_AudioRouteKey_Type key for the CFDictionary associated 
	 with kAudioSession_AudioRouteKey_Inputs.
	 Available in iOS 5.0 or greater      
	 @constant       kAudioSessionInputRoute_LineIn
	 A line in input 
	 @constant       kAudioSessionInputRoute_BuiltInMic
	 A built-in microphone input.  (Note that some devices like early iPods do not have this input)
	 @constant       kAudioSessionInputRoute_HeadsetMic
	 A microphone that is part of a headset (combined microphone and headphones)
	 @constant       kAudioSessionInputRoute_BluetoothHFP
	 A microphone that is part of a Bluetooth Hands-Free Profile device
	 @constant       kAudioSessionInputRoute_USBAudio
	 A Universal Serial Bus input
	 */    
	extern const CFStringRef   kAudioSessionInputRoute_LineIn       API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef   kAudioSessionInputRoute_BuiltInMic   API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef   kAudioSessionInputRoute_HeadsetMic   API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef   kAudioSessionInputRoute_BluetoothHFP API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef   kAudioSessionInputRoute_USBAudio     API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
    
	/*!
	 @enum           AudioSession route output types
	 @abstract       These are strings used with the kAudioSession_AudioRouteKey_Type key for the CFDictionary associated 
	 with kAudioSession_AudioRouteKey_Outputs. 
	 Available in iOS 5.0 or greater       
	 @constant       kAudioSessionOutputRoute_LineOut
	 A line out output
	 @constant       kAudioSessionOutputRoute_Headphones
	 Speakers in a headset (mic and headphones) or simple headphones
	 @constant       kAudioSessionOutputRoute_BluetoothHFP
	 Speakers that are part of a Bluetooth Hands-Free Profile device
	 @constant       kAudioSessionOutputRoute_BluetoothA2DP
	 Speakers in a Bluetooth A2DP device
	 @constant       kAudioSessionOutputRoute_BuiltInReceiver
	 The speaker you hold to your ear when on a phone call
	 @constant       kAudioSessionOutputRoute_BuiltInSpeaker
	 The built-in speaker
	 @constant       kAudioSessionOutputRoute_USBAudio
	 Speaker(s) in a Universal Serial Bus device
	 @constant       kAudioSessionOutputRoute_HDMI
	 Output via High-Definition Multimedia Interface
	 @constant       kAudioSessionOutputRoute_AirPlay
	 Output on a remote Air Play device
	 */
	extern const CFStringRef kAudioSessionOutputRoute_LineOut           API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef kAudioSessionOutputRoute_Headphones        API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef kAudioSessionOutputRoute_BluetoothHFP      API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef kAudioSessionOutputRoute_BluetoothA2DP     API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef kAudioSessionOutputRoute_BuiltInReceiver   API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef kAudioSessionOutputRoute_BuiltInSpeaker    API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef kAudioSessionOutputRoute_USBAudio          API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef kAudioSessionOutputRoute_HDMI              API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef kAudioSessionOutputRoute_AirPlay           API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
    
	// CFDictionary keys for kAudioSessionProperty_InputSources
	extern const CFStringRef   kAudioSession_InputSourceKey_ID            API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef   kAudioSession_InputSourceKey_Description   API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
	// CFDictionary keys for kAudioSessionProperty_OutputDestinations
	extern const CFStringRef   kAudioSession_OutputDestinationKey_ID            API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	extern const CFStringRef   kAudioSession_OutputDestinationKey_Description   API_DEPRECATED("no longer supported", ios(5.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
    
    
	//==================================================================================================
#pragma mark    AudioSession interruption types for end interruption events
	
	/*!
     @enum          AudioSession Interruption types
     @abstract      When an app's AudioSessionInterruptionListener is called at the end of an interruption event,
	 the app may query to see if it should resume audio or not.  The interruption type can be 
	 obtained through the kAudioSessionProperty_InterruptionType, available in iOS 4.0 and
	 greater.
     @constant      kAudioSessionInterruptionType_ShouldResume 
	 Indicates that the interruption was one where it is appropriate to resume playback
	 at the conclusion of the interruption.  (e.g.: a phone call was rejected)
     @constant      kAudioSessionInterruptionType_ShouldNotResume
	 Indicates that the interruption was one where it is not appropriate to resume playback
	 at the conclusion of the interruption.  (e.g.: interruption due to iPod playback)
	 */
	enum {  // typedef UInt32 AudioSessionInterruptionType
		kAudioSessionInterruptionType_ShouldResume                      = 'irsm',
		kAudioSessionInterruptionType_ShouldNotResume                   = '!rsm'
	};
	typedef UInt32 AudioSessionInterruptionType;	    
	
	//==================================================================================================
#pragma mark    AudioSession mode values
	/*!
     @enum          AudioSession Modes
     @abstract      Modes modify the audio category in order to introduce behavior that is tailored to the specific
	 use of audio within an application.  Available in iOS 5.0 and greater.
     @constant      kAudioSessionMode_Default 
	 The default mode.
     @constant      kAudioSessionMode_VoiceChat
	 Only valid with kAudioSessionCategory_PlayAndRecord.  Appropriate for Voice Over IP
	 (VOIP) applications.  Reduces the number of allowable audio routes to be only those
	 that are appropriate for VOIP applications and may engage appropriate system-supplied
	 signal processing.  Has the side effect of setting 
	 kAudioSessionProperty_OverrideCategoryEnableBluetoothInput to true.
     @constant      kAudioSessionMode_VideoRecording     
	 Only valid with kAudioSessionCategory_PlayAndRecord or kAudioSessionCategory_RecordAudio.
	 Modifies the audio routing options and may engage appropriate system-supplied signal processing.
     @constant      kAudioSessionMode_Measurement
	 Appropriate for applications that wish to minimize the effect of system-supplied signal
	 processing for input and/or output audio signals.
     @constant      kAudioSessionMode_GameChat
	 Set by Game Kit on behalf of an application that uses a GKVoiceChat object; valid 
	 only with the kAudioSessionCategory_PlayAndRecord category.
	 Do not set this mode directly. If you need similar behavior and are not using
	 a GKVoiceChat object, use the kAudioSessionMode_VoiceChat mode.
	 */
	enum { 
		kAudioSessionMode_Default               = 'dflt',
		kAudioSessionMode_VoiceChat             = 'vcct',
		kAudioSessionMode_VideoRecording        = 'vrcd',
		kAudioSessionMode_Measurement           = 'msmt',
		kAudioSessionMode_GameChat              = 'gmct'
	};
	
	//==================================================================================================
#pragma mark    AudioSession Properties
	
	/*!
	 @enum           AudioSession property codes
	 @abstract       These are the property codes used with the AudioSession API.
	 @constant       kAudioSessionProperty_PreferredHardwareSampleRate
	 A Float64 indicating the preferred hardware sample rate for the AudioSession.
	 The actual sample rate may be different
	 @constant       kAudioSessionProperty_PreferredHardwareIOBufferDuration 
	 A Float32 indicating the preferred hardware IO buffer duration in seconds.
	 The actual IO buffer duration may be different
	 @constant       kAudioSessionProperty_AudioCategory 
	 A UInt32 value indicating the audio category for the AudioSession (see constants above).
	 @constant       kAudioSessionProperty_AudioRouteChange 
	 The value for this property is ONLY provided with the property changed callback. You 
	 cannot get the value of this property (or set it).
	 The property changed callback provides a CFDictionaryRef with keyed values:
	 Key = kAudioSession_AudioRouteChangeKey_Reason; value is a CFNumberRef with one of the 
	 reasons listed above.
	 Key = kAudioSession_AudioRouteChangeKey_PreviousRouteDescription; value is a CFDictionaryRef containing
	 information about the previous route.  This dictionary is of exactly the same format as the 
	 dictionary associated with kAudioSessionProperty_AudioRouteDescription.  Available in iOS 5.0 or 
	 greater.
	 Key = kAudioSession_AudioRouteChangeKey_CurrentRouteDescription; value is a CFDictionaryRef containing
	 information about the new route.  This dictionary is of exactly the same format as the 
	 dictionary associated with kAudioSessionProperty_AudioRouteDescription.  Available in iOS 5.0 or 
	 greater.
	 @constant       kAudioSessionProperty_CurrentHardwareSampleRate 
	 A Float64 indicating the current hardware sample rate
	 @constant       kAudioSessionProperty_CurrentHardwareInputNumberChannels 
	 A UInt32 indicating the current number of hardware input channels
	 @constant       kAudioSessionProperty_CurrentHardwareOutputNumberChannels 
	 A UInt32 indicating the current number of hardware output channels
	 @constant       kAudioSessionProperty_CurrentHardwareOutputVolume 
	 A Float32 indicating the current output volume
	 @constant       kAudioSessionProperty_CurrentHardwareInputLatency 
	 A Float32 indicating the current hardware input latency in seconds.
	 @constant       kAudioSessionProperty_CurrentHardwareOutputLatency 
	 A Float32 indicating the current hardware output latency in seconds.
	 @constant       kAudioSessionProperty_CurrentHardwareIOBufferDuration 
	 A Float32 indicating the current hardware IO buffer duration in seconds.
	 @constant       kAudioSessionProperty_OtherAudioIsPlaying 
	 A UInt32 with a value other than zero when someone else, typically the iPod application, 
	 is playing audio
	 @constant       kAudioSessionProperty_OverrideAudioRoute 
	 A UInt32 with one of two values: kAudioSessionOverrideAudioRoute_None or 
	 kAudioSessionOverrideAudioRoute_Speaker
	 @constant       kAudioSessionProperty_AudioInputAvailable 
	 A UInt32 with a value other than zero when audio input is available.
	 Use this property, rather than the device model, to determine if audio input is available.
	 A listener will notify you when audio input becomes available.  For instance, when a headset 
	 is attached to the second generation iPod Touch, audio input becomes available via the wired 
	 microphone. 
	 @constant       kAudioSessionProperty_ServerDied
	 Available with iOS 3.0 or greater
	 The value for this property is ONLY provided with the property changed callback. You cannot get the 
	 value of this property (or set it). The property changed callback notifies you that
	 the audio server has died.
	 @constant       kAudioSessionProperty_OtherMixableAudioShouldDuck
	 Available with iOS 3.0 or greater
	 If the current session category of an application allows mixing (iPod playback in the background 
	 for example), then that other audio will be ducked when the current application makes any sound. 
	 An example of this is the Nike app that does this as it provides periodic updates to its user (it 
	 ducks any iPod music currently being played while it provides its status).
	 This defaults to off (0). Note that the other audio will be ducked for as long as the current 
	 session is active. 
	 You will need to deactivate your audio session when you want full volume playback of the other audio.
	 If your category is the Playback category and you have this set to its default (non-mixable), setting
	 this value to on, will also make your category mixable with others
	 (kAudioSessionProperty_OverrideCategoryMixWithOthers will be set to true)
	 @constant       kAudioSessionProperty_OverrideCategoryMixWithOthers
	 Available with iOS 3.0 or greater
	 This allows an application to change the default behavior of some audio session categories with regards to 
	 whether other applications can play while your session is active. The two typical cases are:
	 (1) PlayAndRecord category
	 this will default to false, but can be set to true. This would allow iPod to play in the background 
	 while an app had both audio input and output enabled
	 (2) MediaPlayback category
	 this will default to false, but can be set to true. This would allow iPod to play in the background, 
	 but an app will still be able to play regardless of the setting of the ringer switch 
	 (3) Other categories
	 this defaults to false and cannot be changed (that is, the mix with others setting of these categories 
	 cannot be overridden 
	 An application must be prepared for setting this property to fail as behaviour may change in future releases. 
	 If an application changes their category, they should reassert the override (it is not sticky across 
	 category changes)
	 @constant       kAudioSessionProperty_OverrideCategoryDefaultToSpeaker
	 Available with iOS 3.1 or greater
	 This allows an application to change the default behaviour of some audio session categories with regards to 
	 the audio route. The current category behavior is:
	 (1) PlayAndRecord category
	 this will default to false, but can be set to true. this will route to Speaker (instead of Receiver) 
	 when no other audio route is connected.
	 (2) Other categories
	 this defaults to false and cannot be changed (that is, the default to speaker setting of these 
	 categories cannot be overridden 
	 An application must be prepared for setting this property to fail as behaviour may change in future releases. 
	 If an application changes their category, they should reassert the override (it is not sticky across category changes)
	 @constant       kAudioSessionProperty_OverrideCategoryEnableBluetoothInput
	 Available with iOS 3.1 or greater
	 This allows an application to change the default behaviour of some audio session categories with regards to showing 
	 bluetooth devices as available routes. The current category behavior is:
	 (1) PlayAndRecord category
	 this will default to false, but can be set to true. This will allow a paired bluetooth device to show up as 
	 an available route for input, while playing through the category-appropriate output
	 (2) Record category
	 this will default to false, but can be set to true. This will allow a paired bluetooth device to show up 
	 as an available route for input 
	 (3) Other categories
	 this defaults to false and cannot be changed (that is, enabling bluetooth for input in these categories is 
	 not allowed) 
	 An application must be prepared for setting this property to fail as behaviour may change in future releases. 
	 If an application changes their category, they should reassert the override (it is not sticky across category changes)
     @constant       kAudioSessionProperty_InterruptionType
	 Available with iOS 4.0 or greater
	 This is a read-only property that gives the type of the end interruption event.  Media playback apps (i.e., 
	 those apps that have a "play" button), may use this property as a guideline for when to resume playing after an 
	 interruption ends.  Apps without a "play" button, (e.g., games) should always resume audio playback when the 
	 interruption ends.  This property is only valid within the scope of the client app's AudioSessionInterruptionListener 
	 callback and only valid for the AudioSessionEndInterruption event.  Attempting to read the property at any other 
	 time is invalid.  
	 @constant       kAudioSessionProperty_Mode
	 Available with iOS 5.0 or greater
	 A UInt32 value that specifies the mode to be combined with the Audio Category.  See AudioSession mode 
	 values defined above.
	 @constant       kAudioSessionProperty_InputSources
	 Available with iOS 5.0 or greater
	 For use with certain accessories, such as some USB audio devices, that support input source selection.  
	 If the attached accessory supports source selection, provides a description of the available sources.
	 Not to be confused with kAudioSessionProperty_AudioRouteDescription, which provides a description
	 of the current audio route.  
	 A CFArray of CFDictionaries with the keys listed below.  If no input sources are 
	 available, a valid CFArray with 0 entries will be returned by a get operation.
	 Key = kAudioSession_InputSourceKey_ID; value is a CFNumberRef representing a system-defined identifier
	 for the input source.  This is the identifier to be used when setting the input source.  
	 Key = kAudioSession_InputSourceKey_Description; value is a CFStringRef description of the input source 
	 suitable for displaying in a user interface.  Examples: "Internal Mic", "External Mic", 
	 "Ext 48V Mic", "Instrument", "External Line Connector"
	 @constant       kAudioSessionProperty_OutputDestinations
	 Available with iOS 5.0 or greater
	 For use with certain accessories, such as some USB audio devices, that support output destination selection.  
	 If the attached accessory supports destination selection, provides a description of the available destinations.
	 Not to be confused with kAudioSessionProperty_AudioRouteDescription, which provides a description
	 of the current audio route. 
	 A CFArray of CFDictionaries with the keys listed below.  If no output destinations are 
	 available, a valid CFArray with 0 entries will be returned by a get operation.
	 Key = kAudioSession_OutputDestinationKey_ID; value is a CFNumberRef representing a system-defined identifier
	 for the output destination.  This is the identifier to be used when setting the destination.
	 Key = kAudioSession_OutputDestinationKey_Description; value is a CFStringRef description of the output 
	 destination suitable for displaying in a user interface. 
	 @constant       kAudioSessionProperty_InputSource
	 Available with iOS 5.0 or greater
	 For use with certain accessories, such as some USB audio devices, that support input source selection. 
	 A CFNumberRef value that specifies the input source to be selected.  The value must be one of the 
	 IDs provided by the kAudioSession_InputSourceKey_ID as part of the data associated with 
	 kAudioSessionProperty_InputSources.
	 @constant       kAudioSessionProperty_OutputDestination
	 Available with iOS 5.0 or greater
	 For use with certain accessories, such as some USB audio devices, that support output destination selection.
	 A CFNumberRef value that specifies the output destination to be selected.  The value must be one 
	 of the IDs provided by the kAudioSession_OutputDestinationKey_ID as part of the data associated with
	 kAudioSessionProperty_OutputDestinations.
	 @constant       kAudioSessionProperty_InputGainAvailable
	 Available with iOS 5.0 or greater
	 A UInt32 with a value other than zero when audio input gain is available.  Some inputs may not 
	 provide the ability to set the input gain, so check this value before attempting to set input gain.
	 @constant       kAudioSessionProperty_InputGainScalar
	 Available with iOS 5.0 or greater
	 A Float32 value defined over the range [0.0, 1.0], with 0.0 corresponding to the lowest analog 
	 gain setting and 1.0 corresponding to the highest analog gain setting.  Attempting to set values
	 outside of the defined range will result in the value being "clamped" to a valid input.  This is 
	 a global input gain setting that applies to the current input source for the entire system.  
	 When no applications are using the input gain control, the system will restore the default input
	 gain setting for the input source.  Note that some audio accessories, such as USB devices, may 
	 not have a default value.  This property is only valid if kAudioSessionProperty_InputGainAvailable
	 is true.  Note that route change events represent substantive changes to the audio system. Input 
	 gain settings are not guaranteed to persist across route changes. Application code should be aware
	 that route change events can (and likely will) cause a change to input gain settings, and so should
	 be prepared to reassess the state of input gain after the new route is established.
	 @constant       kAudioSessionProperty_AudioRouteDescription 
	 Available with iOS 5.0 or greater
	 A CFDictionaryRef with information about the current audio route; keyed values:
	 Key = kAudioSession_AudioRouteKey_Inputs; value is a CFArray of CFDictionaries with information about the 
	 inputs utilitized in the current audio route.  
	 Key = kAudioSession_AudioRouteKey_Outputs; value is a CFArray of CFDictionaries with information about the 
	 outputs utilitized in the current audio route.
	 Both kAudioSession_AudioRouteKey_Inputs and kAudioSession_AudioRouteKey_Outputs return a CFArray of
	 CFDictionaries with Key = kAudioSession_AudioRouteKey_Type; value is a CFString corresponding
	 to the input or output types documented above.
	 */
	enum { // typedef UInt32 AudioSessionPropertyID
		kAudioSessionProperty_PreferredHardwareSampleRate           = 'hwsr',   // Float64          (get/set)
		kAudioSessionProperty_PreferredHardwareIOBufferDuration     = 'iobd',   // Float32          (get/set)
		kAudioSessionProperty_AudioCategory                         = 'acat',   // UInt32           (get/set)
		kAudioSessionProperty_AudioRouteChange                      = 'roch',   // CFDictionaryRef  (property listener)
		kAudioSessionProperty_CurrentHardwareSampleRate             = 'chsr',   // Float64          (get only)
		kAudioSessionProperty_CurrentHardwareInputNumberChannels    = 'chic',   // UInt32           (get only/property listener)
		kAudioSessionProperty_CurrentHardwareOutputNumberChannels   = 'choc',   // UInt32           (get only/property listener)
		kAudioSessionProperty_CurrentHardwareOutputVolume           = 'chov',   // Float32          (get only/property listener)
		kAudioSessionProperty_CurrentHardwareInputLatency           = 'cilt',   // Float32          (get only)
		kAudioSessionProperty_CurrentHardwareOutputLatency          = 'colt',   // Float32          (get only)
		kAudioSessionProperty_CurrentHardwareIOBufferDuration       = 'chbd',   // Float32          (get only)
		kAudioSessionProperty_OtherAudioIsPlaying                   = 'othr',   // UInt32           (get only)
		kAudioSessionProperty_OverrideAudioRoute                    = 'ovrd',   // UInt32           (set only)
		kAudioSessionProperty_AudioInputAvailable                   = 'aiav',   // UInt32           (get only/property listener)
		kAudioSessionProperty_ServerDied                            = 'died',   // UInt32           (property listener)
		kAudioSessionProperty_OtherMixableAudioShouldDuck           = 'duck',   // UInt32           (get/set)
		kAudioSessionProperty_OverrideCategoryMixWithOthers         = 'cmix',   // UInt32           (get, some set)
		kAudioSessionProperty_OverrideCategoryDefaultToSpeaker      = 'cspk',   // UInt32           (get, some set)
		kAudioSessionProperty_OverrideCategoryEnableBluetoothInput  = 'cblu',   // UInt32           (get, some set)
		kAudioSessionProperty_InterruptionType                      = 'type',   // UInt32           (get only)
		kAudioSessionProperty_Mode                                  = 'mode',   // UInt32           (get/set)
		kAudioSessionProperty_InputSources                          = 'srcs',   // CFArrayRef       (get only/property listener)
		kAudioSessionProperty_OutputDestinations                    = 'dsts',   // CFArrayRef       (get only/property listener)
		kAudioSessionProperty_InputSource                           = 'isrc',   // CFNumberRef      (get/set)
		kAudioSessionProperty_OutputDestination                     = 'odst',   // CFNumberRef      (get/set)
		kAudioSessionProperty_InputGainAvailable                    = 'igav',   // UInt32           (get only/property listener)
		kAudioSessionProperty_InputGainScalar                       = 'igsc',   // Float32          (get/set/property listener)
		kAudioSessionProperty_AudioRouteDescription                 = 'crar'   // CFDictionaryRef  (get only)
	};
    
	//==================================================================================================
#pragma mark -
#pragma mark Callbacks
	/*!
	 @typedef        AudioSessionInterruptionListener
	 @abstract       A function to be called when an interruption begins or ends.
	 @discussion     AudioSessionInterruptionListener has to be provided by client applications in the
	 AudioSessionInitialize function.  It will be called when an interruption begins or ends.
	 @param          inClientData
	 The client user data to use when calling the listener.
	 @param          inInterruptionState
	 Indicates if the interruption begins (kAudioSessionBeginInterruption)
	 or ends (kAudioSessionEndInterruption)
	 */
	typedef void (*AudioSessionInterruptionListener)(
													 void *                  inClientData,
													 UInt32                  inInterruptionState);
	
	/*!
	 @typedef        AudioSessionPropertyListener
	 @abstract       A function to be executed when a property changes.
	 @discussion     AudioSessionPropertyListener may be provided by client application to be
	 called when a property changes.
	 @param          inClientData
	 The client user data to use when calling the listener.
	 @param          inID
	 The AudioSession property that changed
	 @param          inDataSize
	 The size of the payload
	 @param          inData
	 The payload of the property that changed (see data type for each property)
	 */
	typedef void (*AudioSessionPropertyListener)(
												 void *                  inClientData,
												 AudioSessionPropertyID	inID,
												 UInt32                  inDataSize,
												 const void *            inData);
	
	//==================================================================================================
#pragma mark -
#pragma mark    AudioSession Functions
	
	/*!
	 @functiongroup  AudioSession
	 */
	
	/*!
	 @function       AudioSessionInitialize
	 @abstract       Initialize the AudioSession.
	 @discussion     This function has to be called once before calling any other
	 AudioSession functions.
	 @param          inRunLoop
	 A CFRunLoopRef indicating the desired run loop the interruption routine should
	 be run on. Pass NULL to use the main run loop.
	 @param          inRunLoopMode
	 A CFStringRef indicating the run loop mode for the runloop where the
	 completion routine will be executed. Pass NULL to use kCFRunLoopDefaultMode.
	 @param          inInterruptionListener
	 An AudioSessionInterruptionListener to be called when the AudioSession
	 is interrupted.
	 @param          inClientData
	 The client user data to use when calling the interruption listener.
	 */
	extern OSStatus
	AudioSessionInitialize(             CFRunLoopRef                        inRunLoop, 
						   CFStringRef                         inRunLoopMode, 
						   AudioSessionInterruptionListener    inInterruptionListener, 
						   void                                *inClientData)              
	API_DEPRECATED("no longer supported", ios(2.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
	/*!
	 @function       AudioSessionSetActive
	 @abstract       Activate or deactivate the AudioSession.
	 @discussion     Call this function with active set to true to activate this AudioSession (interrupt
	 the currently active AudioSession).
	 Call this function with active set to false to deactivate this AudioSession (allow
	 another interrupted AudioSession to resume).
	 When active is true this call may fail if the currently active AudioSession has a higher priority.
	 @param          active
	 A Boolean indicating if you want to make this AudioSession active or inactive.
	 */
	extern OSStatus
	AudioSessionSetActive(              Boolean                             active)                     
	API_DEPRECATED("no longer supported", ios(2.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
	//==================================================================================================
#pragma mark    AudioSessionActivationFlags for AudioSessionSetActiveWithFlags
    
	/*!
	 @enum           Flags for AudioSessionSetActiveWithFlags
	 @abstract       These are valid bitmap flags that may be combined and passed to AudioSessionSetActiveWithFlags
	 to refine this routine's behavior.
	 @constant       kAudioSessionSetActiveFlag_NotifyOthersOnDeactivation
	 Notify an interrupted app that the interruption has ended and it may resume playback. Only
	 valid on session deactivation.
	 */
	enum {
		kAudioSessionSetActiveFlag_NotifyOthersOnDeactivation       = (1 << 0)  //  0x01
	};
    
	/*!
	 @function       AudioSessionSetActiveWithFlags
	 @abstract       Same functionality as AudioSessionSetActive, with an additional flags parameter for 
	 refining behavior.
	 @discussion     Call this function with active set to true to activate this AudioSession (interrupt
	 the currently active AudioSession).
	 Call this function with active set to false to deactivate this AudioSession (allow
	 another interrupted AudioSession to resume).
	 Pass in one or more flags to refine the behavior during activation or deactivation.
	 When active is true this call may fail if the currently active AudioSession has a 
	 higher priority.
	 @param          active
	 A Boolean indicating if you want to make this AudioSession active or inactive.
	 @param          inFlags
	 A bitmap containing one or more flags from the AudioSessionActivationFlags enum.
	 */
	extern OSStatus
	AudioSessionSetActiveWithFlags(     Boolean                             active,
								   UInt32                              inFlags)                    
	API_DEPRECATED("no longer supported", ios(4.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
	/*!
	 @function       AudioSessionGetProperty
	 @abstract       Get the value of a property.
	 @discussion     This function can be called to get the value for a property of the AudioSession.
	 Valid properties are listed in an enum above.
	 @param          inID
	 The AudioSessionPropertyID for which we want to get the value.
	 @param          ioDataSize
	 The size of the data payload.
	 On entry it should contain the size of the memory pointed to by outData.
	 On exit it will contain the actual size of the data.
	 @param          outData
	 The data for the property will be copied here.
	 @return         kAudioSessionNoError if the operation was successful.  If the property is a
	 write-only property or only available by way of property listeners, 
	 kAudioSessionUnsupportedPropertyError will be returned.  Other error codes 
	 listed under AudioSession Error Constants also apply to this function.
	 */
	extern OSStatus
	AudioSessionGetProperty(            AudioSessionPropertyID              inID,
							UInt32                              *ioDataSize,
							void                                *outData)                   
	API_DEPRECATED("no longer supported", ios(2.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
	/*!
	 @function       AudioSessionSetProperty
	 @abstract       Set the value of a property.
	 @discussion     This function can be called to set the value for a property of the AudioSession.
	 Valid properties are listed in an enum above.
	 @param          inID
	 The AudioSessionPropertyID for which we want to set the value.
	 @param          inDataSize
	 The size of the data payload.
	 @param          inData
	 The data for the property we want to set.
	 @return         kAudioSessionNoError if the operation was successful.  If the property is a
	 read-only property or an invalid property value is passed in, 
	 kAudioSessionUnsupportedPropertyError will be returned.  Other error codes 
	 listed under AudioSession Error Constants also apply to 
	 this function.
	 */
	extern OSStatus
	AudioSessionSetProperty(            AudioSessionPropertyID              inID,
							UInt32                              inDataSize,
							const void                          *inData)                    
	API_DEPRECATED("no longer supported", ios(2.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
	/*!
	 @function       AudioSessionGetPropertySize
	 @abstract       Get the size of the payload for a property.
	 @discussion     This function can be called to get the size for the payload of a property.
	 Valid properties are listed in an enum above.
	 @param          inID
	 The AudioSessionPropertyID for which we want to get the size of the payload.
	 @param          outDataSize
	 The size of the data payload will be copied here.
	 */
	extern OSStatus
	AudioSessionGetPropertySize(        AudioSessionPropertyID              inID,
								UInt32                              *outDataSize)               
	API_DEPRECATED("no longer supported", ios(2.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
	/*!
	 @function       AudioSessionAddPropertyListener
	 @abstract       Add a property listener.
	 @discussion     This function can be used to add a listener to be called when a property changes.
	 If a listener and user data already exist for this property, they will be replaced.
	 Valid properties are listed above.
	 @param          inID
	 The AudioSessionPropertyID for which we want to set a listener.
	 @param          inProc
	 The listener to be called when the property changes.
	 @param          inClientData
	 The client user data to use when calling the listener.
	 @return         kAudioSessionNoError if the operation was successful.  If the property does
	 not support listeners, kAudioSessionUnsupportedPropertyError will be returned.  
	 Other error codes listed under AudioSession Error Constants also apply to 
	 this function.
	 */
	extern OSStatus
	AudioSessionAddPropertyListener(    AudioSessionPropertyID              inID,
                                    AudioSessionPropertyListener        inProc,
                                    void                                *inClientData)              
	API_DEPRECATED("no longer supported", ios(2.0, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
	/*!
	 @function       AudioSessionRemovePropertyListener
	 @abstract       see AudioSessionRemovePropertyListenerWithUserData
	 @discussion     see AudioSessionRemovePropertyListenerWithUserData
	 */
	extern OSStatus
	AudioSessionRemovePropertyListener(	AudioSessionPropertyID          inID)                           
	API_DEPRECATED("no longer supported", ios(2.0, 2.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
	/*!
	 @function       AudioSessionRemovePropertyListener
	 @abstract       Remove a property listener.
	 @discussion     This function can be called to remove the listener for a property. The caller
	 provides the same proc and user data that was used to add the listener. This ensures
	 that there can be more than one listener established for a given property ID,
	 and each listener can be removed as requested.
	 Valid properties are listed above.
	 @param          inID
	 The AudioSessionPropertyID for which we want to remove the listener.
	 @param          inProc
	 The proc that was used to add the listener that needs to be removed.
	 @param          inClientData
	 The client data that was used to add the listener that needs to be removed.
	 @return         kAudioSessionNoError if the operation was successful.  If the property does
	 not support listeners, kAudioSessionUnsupportedPropertyError will be returned.  
	 Other error codes listed under AudioSession Error Constants also apply to 
	 this function.
	 */
	extern OSStatus
	AudioSessionRemovePropertyListenerWithUserData(	AudioSessionPropertyID          inID,
												   AudioSessionPropertyListener    inProc,
												   void                            *inClientData)              
	API_DEPRECATED("no longer supported", ios(2.1, 7.0)) API_UNAVAILABLE(macos) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
	
#pragma mark -
#pragma mark Deprecated
	
	/*!
	 @enum           AudioSession audio categories states
	 @abstract       These two session categories are deprecated in iOS 3.0 or later
	 @constant       kAudioSessionCategory_UserInterfaceSoundEffects
	 use kAudioSessionCategory_AmbientSound
	 @constant       kAudioSessionCategory_LiveAudio 
	 use kAudioSessionCategory_MediaPlayback
	 */
	enum {
		kAudioSessionCategory_UserInterfaceSoundEffects  = 'uifx',
		kAudioSessionCategory_LiveAudio                  = 'live'
	};
	
	/*!
	 @enum           AudioSession audio categories states
	 @abstract       Deprecated AudioSession properties
	 @constant       kAudioSessionProperty_AudioRoute 
	 Deprecated in iOS 5.0; Use kAudioSessionProperty_AudioRouteDescription 
	 */
	enum {
		kAudioSessionProperty_AudioRoute                            = 'rout',   // CFStringRef      (get only)        
	};
	
	// deprecated dictionary keys
    
	// Deprecated in iOS 5.0; Use kAudioSession_AudioRouteChangeKey_PreviousRouteDescription instead    
#define kAudioSession_AudioRouteChangeKey_OldRoute  "OutputDeviceDidChange_OldRoute"
	//==================================================================================================

#ifdef __cplusplus
}
#endif

#endif /* __AudioSession_h__ */

// ==========  AudioToolbox.framework/Headers/AudioUnitParameters.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AudioUnitParameters.h>)
/*!
	@file		AudioUnitParameters.h
 	@framework	AudioToolbox.framework
 	@copyright	(c) 2000-2015 Apple, Inc. All rights reserved.
	@abstract	Constants for the parameters of Apple audio units.
*/

#ifndef AudioUnit_AudioUnitParameters_h
#define AudioUnit_AudioUnitParameters_h

#include <AudioToolbox/AUComponent.h>

#pragma mark General Declarations

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following specifies the equivalent parameterID's for the Group scope for standard
MIDI Controllers. This list is not exhaustive. It represents the parameters, and their corresponding 
MIDI messages, that should be supported in Group scope by MIDI capable AUs.

Group scope parameter IDs from 0 < 512 are reserved for mapping MIDI controllers.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
CF_ENUM(AudioUnitParameterID) {
	kAUGroupParameterID_Volume					= 7,	// value 0 < 128
	kAUGroupParameterID_Sustain					= 64, 	// value 0-63 (off), 64-127 (on)
	kAUGroupParameterID_Sostenuto				= 66, 	// value 0-63 (off), 64-127 (on)
	kAUGroupParameterID_AllNotesOff				= 123,	// value ignored
	kAUGroupParameterID_ModWheel				= 1,	// value 0 < 128
	kAUGroupParameterID_PitchBend				= 0xE0,	// value -8192 - 8191
	kAUGroupParameterID_AllSoundOff				= 120,	// value ignored
	kAUGroupParameterID_ResetAllControllers		= 121,	// value ignored
	kAUGroupParameterID_Pan						= 10,	// value 0 < 128
	kAUGroupParameterID_Foot					= 4,	// value 0 < 128
	kAUGroupParameterID_ChannelPressure			= 0xD0,	// value 0 < 128
	kAUGroupParameterID_KeyPressure				= 0xA0,	// values 0 < 128
	kAUGroupParameterID_Expression				= 11,	// value 0 < 128
	kAUGroupParameterID_DataEntry				= 6,	// value 0 < 128

	kAUGroupParameterID_Volume_LSB				= kAUGroupParameterID_Volume + 32,		// value 0 < 128
	kAUGroupParameterID_ModWheel_LSB			= kAUGroupParameterID_ModWheel + 32,	// value 0 < 128
	kAUGroupParameterID_Pan_LSB					= kAUGroupParameterID_Pan + 32,			// value 0 < 128
	kAUGroupParameterID_Foot_LSB				= kAUGroupParameterID_Foot + 32,		// value 0 < 128
	kAUGroupParameterID_Expression_LSB			= kAUGroupParameterID_Expression + 32,	// value 0 < 128
	kAUGroupParameterID_DataEntry_LSB			= kAUGroupParameterID_DataEntry + 32,	// value 0 < 128
	
	kAUGroupParameterID_KeyPressure_FirstKey	= 256,	// value 0 < 128
	kAUGroupParameterID_KeyPressure_LastKey		= 383	// value 0 < 128
};
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Supporting the kAUGroupParameterID_KeyPressure parameter indicates to hosts that your audio unit
supports polyphonic "aftertouch" key pressure. 

Each of the 128 MIDI key numbers can have its own value for polyphonic aftertouch. To respond to 
aftertouch for a particular key, your audio unit needs to support an additional parameter 
specifically for that key. The aftertouch parameter ID for a given MIDI key is equal to the MIDI 
key number plus 256. For example, the aftertouch parameter ID for MIDI key #60 (middle C) is:

	60 + kAUGroupParameterID_KeyPressure_FirstKey = 316
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following sections specify the parameter IDs for the audio units included in Mac OS X.
Host applications can use these IDs to directly address these parameters without first discovering 
them through the AUParameterInfo mechanism (see the AudioUnitProperties.h header file)

Each parameter is preceeded by a comment that indicates scope, unit of measurement, minimum
value, maximum value, and default value.
    
See the AudioUnitProperties.h header file for additional information that a parameter may report

When displaying to the user information about a parameter, a host application should always
get the parameter information from the audio unit itself.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#if !TARGET_OS_IPHONE
// Parameters for all Panner AudioUnits
CF_ENUM(AudioUnitParameterID) {
        // Global, Linear, 0->1, 1
	kPannerParam_Gain = 0,			
	
        // Global, Degrees, -180->180, 0
	kPannerParam_Azimuth = 1,		
        // Global, Degrees, -90->90, 0
	kPannerParam_Elevation = 2,	
		
        // Global, Linear, 0->1, 1
	kPannerParam_Distance = 3,		// 0 .. 1
	
        // Global, Meters, 0.01->1000, 1
	kPannerParam_CoordScale = 4,	
        // Global, Meters, 0.01->1000, 1
	kPannerParam_RefDistance = 5,	
};
#endif // !TARGET_OS_IPHONE



#pragma mark Apple Specific

// Parameters for the AUSpatialMixer unit
CF_ENUM(AudioUnitParameterID) {
    // Input, Degrees, -180->180, 0
    kSpatialMixerParam_Azimuth		= 0,
    
    // Input, Degrees, -90->90, 0
    kSpatialMixerParam_Elevation		= 1,
    
    // Input, Metres, 0->10000, 0
    kSpatialMixerParam_Distance		= 2,
    
    // Input/Output, dB, -120->20, 0
    kSpatialMixerParam_Gain			= 3,
	
    // Input, rate scaler	0.5 -> 2.0, 1.0
    kSpatialMixerParam_PlaybackRate	= 4,
    
    // bus enable : 0 or 1, 1
    kSpatialMixerParam_Enable       = 5,
    
    // Minimum input gain constraint : 0.0 -> 10.0, 0.0
    kSpatialMixerParam_MinGain      = 6,
    
    // Maximum input gain constraint : 0.0 -> 10.0, 10.0
    kSpatialMixerParam_MaxGain      = 7,
	
    // Input, Dry/Wet equal-power blend, %	  0.0 -> 100.0, 30.0
    kSpatialMixerParam_ReverbBlend		= 8,
    
    // Global, dB,		-40.0 -> +40.0, 0.0
    kSpatialMixerParam_GlobalReverbGain	= 9,
	
    // Input, Lowpass filter attenuation at 5KHz :		decibels -100.0dB -> 0.0dB, 0.0dB
    // smaller values make both direct and reverb sound more muffled; a value of 0.0 indicates no filtering
    // Occlusion is a filter applied to the sound prior to the reverb send
    kSpatialMixerParam_OcclusionAttenuation	= 10,
	
    // Input, Lowpass filter attenuation at 5KHz :		decibels -100.0dB -> 0.0dB, 0.0dB
    // smaller values make direct sound more muffled; a value of 0.0 indicates no filtering
    // Obstruction is a filter applied to the "direct" part of the sound (so is post reverb send)
    kSpatialMixerParam_ObstructionAttenuation = 11
};
    
// Reverb parameters applicable to AUSpatialMixer
CF_ENUM(AudioUnitParameterID) {
    // Global, Hertz, 10.0 -> 20000.0, 800.0
	kReverbParam_FilterFrequency					= 14,
    
    // Global, Octaves, 0.05 -> 4.0, 3.0
	kReverbParam_FilterBandwidth					= 15,
    
    // Global, Decibels, -18.0 -> +18.0, 0.0
	kReverbParam_FilterGain							= 16,
    
    // Global, Indexed, 0->kNumAUNBandEQFilterTypes-1, 0
    kReverbParam_FilterType                         = 17,       // only available for AUSpatialMixer
    
    // Global, Boolean, 0->1, 1
    kReverbParam_FilterEnable                       = 18        // only available for AUSpatialMixer
};


// Parameters for the AUMixer3D unit
CF_ENUM(AudioUnitParameterID) {
        // Input, Degrees, -180->180, 0
    k3DMixerParam_Azimuth		= 0,
        
		// Input, Degrees, -90->90, 0
    k3DMixerParam_Elevation		= 1,
        
		// Input, Metres, 0->10000, 0
    k3DMixerParam_Distance		= 2,
        
		// Input/Output, dB, -120->20, 0
    k3DMixerParam_Gain			= 3,
	
		// Input, rate scaler	0.5 -> 2.0
    k3DMixerParam_PlaybackRate	= 4,
    
    // bus enable : 0.0 or 1.0
    k3DMixerParam_BusEnable API_AVAILABLE(macos(10.15), ios(13.0), tvos(9.0), watchos(6.0)) = 20,
    
    // Input/Output, dB, -120->20, 0
    k3DMixerParam_MinGainInDecibels API_AVAILABLE(macos(10.15), ios(13.0), tvos(9.0), watchos(6.0)) = 21,
    
    // Input/Output, dB, -120->20, 0
    k3DMixerParam_MaxGainInDecibels API_AVAILABLE(macos(10.15), ios(13.0), tvos(9.0), watchos(6.0)) = 22,

    // Input, Dry/Wet equal-power blend, %      0.0 -> 100.0
    k3DMixerParam_DryWetReverbBlend API_AVAILABLE(macos(10.15), ios(13.0), tvos(9.0), watchos(6.0)) = 23,
    
    // Global, dB,        -40.0 -> +40.0
    k3DMixerParam_GlobalReverbGainInDecibels API_AVAILABLE(macos(10.15), ios(13.0), tvos(9.0), watchos(6.0)) = 24,
    
    // Input, Lowpass filter attenuation at 5KHz :        decibels -100.0dB -> 0.0dB
    // smaller values make both direct and reverb sound more muffled; a value of 0.0 indicates no filtering
    // Occlusion is a filter applied to the sound prior to the reverb send
    k3DMixerParam_OcclusionAttenuationInDecibels API_AVAILABLE(macos(10.15), ios(13.0), tvos(9.0), watchos(6.0)) = 25,
    
    // Input, Lowpass filter attenuation at 5KHz :        decibels -100.0dB -> 0.0dB
    // smaller values make direct sound more muffled; a value of 0.0 indicates no filtering
    // Obstruction is a filter applied to the "direct" part of the sound (so is post reverb send)
    k3DMixerParam_ObstructionAttenuationInDecibels API_AVAILABLE(macos(10.15), ios(13.0), tvos(9.0), watchos(6.0)) = 26,
    
#if TARGET_OS_IPHONE && !TARGET_OS_UIKITFORMAC
		// iPhone specific 3D mixer parameters -- deprecated

		// bus enable : 0.0 or 1.0
    k3DMixerParam_Enable    API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_BusEnable", ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(macos)   = 5,

		// Minimum input gain constraint : 0.0 -> 1.0 (available on iphone only)
    k3DMixerParam_MinGain   API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_MinGainInDecibels", ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(macos)   = 6,

		// Maximum input gain constraint : 0.0 -> 1.0 (available on iphone only)
    k3DMixerParam_MaxGain   API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_MaxGainInDecibels", ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(macos)   = 7,
	
		// Input, Dry/Wet equal-power blend, %	  0.0 -> 100.0
    k3DMixerParam_ReverbBlend   API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_DryWetReverbBlend", ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(macos)   = 8,

		// Global, dB,		-40.0 -> +40.0
    k3DMixerParam_GlobalReverbGain  API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_GlobalReverbGainInDecibels", ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(macos) = 9,
	
		// Input, Lowpass filter attenuation at 5KHz :		decibels -100.0dB -> 0.0dB
		// smaller values make both direct and reverb sound more muffled; a value of 0.0 indicates no filtering
		// Occlusion is a filter applied to the sound prior to the reverb send
    k3DMixerParam_OcclusionAttenuation  API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_OcclusionAttenuationInDecibels", ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(macos)  = 10,
	
		// Input, Lowpass filter attenuation at 5KHz :		decibels -100.0dB -> 0.0dB
		// smaller values make direct sound more muffled; a value of 0.0 indicates no filtering
		// Obstruction is a filter applied to the "direct" part of the sound (so is post reverb send)
    k3DMixerParam_ObstructionAttenuation    API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_ObstructionAttenuationInDecibels", ios(2.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED), tvos(9.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(macos) = 11,
#endif

#if TARGET_OS_OSX
		// Desktop specific 3D mixer parameters -- deprecated
    
		// Input, Dry/Wet equal-power blend, %	  0.0 -> 100.0
    k3DMixerParam_ReverbBlend   API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_DryWetReverbBlend", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos) = 5,

		// Global, dB,		-40.0 -> +40.0
    k3DMixerParam_GlobalReverbGain  API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_GlobalReverbGainInDecibels", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos) = 6,
	
		// Input, Lowpass filter attenuation at 5KHz :		decibels -100.0dB -> 0.0dB
		// smaller values make both direct and reverb sound more muffled; a value of 0.0 indicates no filtering
		// Occlusion is a filter applied to the sound prior to the reverb send
    k3DMixerParam_OcclusionAttenuation  API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_OcclusionAttenuationInDecibels", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos) = 7,
	
		// Input, Lowpass filter attenuation at 5KHz :		decibels -100.0dB -> 0.0dB
		// smaller values make direct sound more muffled; a value of 0.0 indicates no filtering
		// Obstruction is a filter applied to the "direct" part of the sound (so is post reverb send)
    k3DMixerParam_ObstructionAttenuation  API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_ObstructionAttenuationInDecibels", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos) = 8,

		// Input/Output, dB, -120->20, 0
    k3DMixerParam_MinGain  API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_MinGainInDecibels", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos) = 9,
	
		// Input/Output, dB, -120->20, 0
    k3DMixerParam_MaxGain  API_DEPRECATED_WITH_REPLACEMENT("k3DMixerParam_MaxGainInDecibels", macos(10.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, tvos) = 10,
		
#endif
    
    // read-only
    //
    // For each of the following, use the parameter ID plus the channel number
    // to get the specific parameter ID for a given channel.
    // For example, k3DMixerParam_PostAveragePower indicates the left channel
    // while k3DMixerParam_PostAveragePower + 1 indicates the right channel.
    k3DMixerParam_PreAveragePower    = 1000,
    k3DMixerParam_PrePeakHoldLevel    = 2000,
    k3DMixerParam_PostAveragePower    = 3000,
    k3DMixerParam_PostPeakHoldLevel    = 4000
};


// Parameters for the AUMultiChannelMixer unit
// these are available for both desktop and iphone
CF_ENUM(AudioUnitParameterID) {
		// Global, Linear Gain, 0->1, 1. (the volume value can actually be any finite number, including negative.)
	kMultiChannelMixerParam_Volume 	= 0,
		// Global, Boolean, 0->1, 1
	kMultiChannelMixerParam_Enable 	= 1,
		// Global, Pan, -1->1, 0
	kMultiChannelMixerParam_Pan     = 2,			// -1 - 0 - 1, only valid when output is not mono
													// setting kAudioUnitProperty_MatrixLevels overrides any
													// previously set kMultiChannelMixerParam_Pan and vice versa

		// read-only, Input or Output scope.
	// these report level in dB, as do the other mixers
	kMultiChannelMixerParam_PreAveragePower		= 1000,
	kMultiChannelMixerParam_PrePeakHoldLevel	= 2000,
	kMultiChannelMixerParam_PostAveragePower	= 3000,
	kMultiChannelMixerParam_PostPeakHoldLevel	= 4000
};


// Parameters for the AUMatrixMixer unit
CF_ENUM(AudioUnitParameterID) {
	kMatrixMixerParam_Volume 	= 0,
	kMatrixMixerParam_Enable 	= 1,
	
		// read-only
	// these report level in dB, as do the other mixers
	kMatrixMixerParam_PreAveragePower	= 1000,
	kMatrixMixerParam_PrePeakHoldLevel	= 2000,
	kMatrixMixerParam_PostAveragePower	= 3000,
	kMatrixMixerParam_PostPeakHoldLevel	= 4000,

	// these report linear levels - for "expert" use only.
	kMatrixMixerParam_PreAveragePowerLinear			= 5000,
	kMatrixMixerParam_PrePeakHoldLevelLinear		= 6000,
	kMatrixMixerParam_PostAveragePowerLinear		= 7000,
	kMatrixMixerParam_PostPeakHoldLevelLinear		= 8000
};


// Output Units
// Parameters for the AudioDeviceOutput, DefaultOutputUnit, and SystemOutputUnit units
CF_ENUM(AudioUnitParameterID) {
		// Global, LinearGain, 0->1, 1
	kHALOutputParam_Volume 		= 14 
};

// Parameters for the AUTimePitch, AUTimePitch (offline), AUPitch units
CF_ENUM(AudioUnitParameterID) {
	kTimePitchParam_Rate						= 0,
#if !TARGET_OS_IPHONE
	kTimePitchParam_Pitch						= 1,
	kTimePitchParam_EffectBlend					= 2		// only for the AUPitch unit
#endif
};

// Parameters for AUNewTimePitch
CF_ENUM(AudioUnitParameterID) {
		// rate control.
		// Global, rate, 1/32 -> 32.0, 1.0
	kNewTimePitchParam_Rate							= 0,
	
		// pitch shift in cents.
		// Global, Cents, -2400 -> 2400, 1.0
	kNewTimePitchParam_Pitch						= 1,
	
		// Overlap is the number of overlapped spectral windows that are used to produce the output.
		// The value of overlap is directly proportional to CPU cost. More overlaps can make smooth
		// passages sound smoother. For percussive sound, a lower overlap may be better.
		// Global, generic, 3.0 -> 32.0, 8.0
	kNewTimePitchParam_Overlap						= 4,
	
		// Peak locking enforces phase coherence of spectral peaks.
		// Peak locking adds some expense but results in a less "phasey"
		// or reverberant sound, sometimes also called loss of presence.
		// However the flip side is that it can sound more stuttery for some content.
		// Global, Boolean, 0->1, 1
	kNewTimePitchParam_EnablePeakLocking			= 6
};

// Parameters for the AUSampler unit
CF_ENUM(AudioUnitParameterID) {
		// Global, dB, -90->12, 0
	kAUSamplerParam_Gain				= 900,

		// Global, Semitones, -24->24, 0
	kAUSamplerParam_CoarseTuning		= 901,

		// Global, Cents, -99->99, 0
	kAUSamplerParam_FineTuning			= 902,

		// Global, -1.0->1.0, 0
	kAUSamplerParam_Pan					= 903
};

// Effect units
// The values for some effect unit parameters depend on the audio unit's sample rate.
// For example, maximum values are typically the Nyquist frequency (indicated here as 
// SampleRate/2).

// Parameters for the AUBandpass unit
CF_ENUM(AudioUnitParameterID) {
		// Global, Hz, 20->(SampleRate/2), 5000
	kBandpassParam_CenterFrequency 			= 0,

		// Global, Cents, 100->12000, 600
	kBandpassParam_Bandwidth 				= 1
};

// Parameters for the AUHipass unit
CF_ENUM(AudioUnitParameterID) {
		// Global, Hz, 10->(SampleRate/2), 6900
	kHipassParam_CutoffFrequency 			= 0,
		
		// Global, dB, -20->40, 0
	kHipassParam_Resonance					= 1
};

// Parameters for the AULowpass unit
CF_ENUM(AudioUnitParameterID) {
		// Global, Hz, 10->(SampleRate/2), 6900
	kLowPassParam_CutoffFrequency 			= 0,
		
		// Global, dB, -20->40, 0
	kLowPassParam_Resonance 				= 1
};

// Parameters for the AUHighShelfFilter unit
CF_ENUM(AudioUnitParameterID) {
		// Global, Hz, 10000->(SampleRate/2), 10000
	kHighShelfParam_CutOffFrequency 		= 0,
		
		// Global, dB, -40->40, 0
	kHighShelfParam_Gain 					= 1
};

// Parameters for the AULowShelfFilter unit
CF_ENUM(AudioUnitParameterID) {
		// Global, Hz, 10->200, 80
	kAULowShelfParam_CutoffFrequency = 0,
		
		// Global, dB, -40->40, 0
	kAULowShelfParam_Gain = 1
};

// Parameters for the AUParametricEQ unit
CF_ENUM(AudioUnitParameterID) {
		// Global, Hz, 20->(SampleRate/2), 2000
    kParametricEQParam_CenterFreq = 0,
		
		// Global, Hz, 0.1->20, 1.0
    kParametricEQParam_Q = 1,
		
		// Global, dB, -20->20, 0
    kParametricEQParam_Gain = 2
};

// Parameters for the AUPeakLimiter unit
CF_ENUM(AudioUnitParameterID) {
		// Global, Secs, 0.001->0.03, 0.012
	kLimiterParam_AttackTime 			= 0,
		
		// Global, Secs, 0.001->0.06, 0.024
	kLimiterParam_DecayTime 			= 1,
		
		// Global, dB, -40->40, 0
	kLimiterParam_PreGain 				= 2
};

// Parameters for the AUDynamicsProcessor unit
// Note that the dynamics processor does not have fixed compression ratios.
// Instead, kDynamicsProcessorParam_HeadRoom adjusts the amount of compression.
// Lower kDynamicsProcessorParam_HeadRoom values results in higher compression.
// The compression ratio is automatically adjusted to not exceed kDynamicsProcessorParam_Threshold + kDynamicsProcessorParam_HeadRoom values.
    
CF_ENUM(AudioUnitParameterID) {
		// Global, dB, -40->20, -20
	kDynamicsProcessorParam_Threshold 			= 0,
		
		// Global, dB, 0.1->40.0, 5
	kDynamicsProcessorParam_HeadRoom	 		= 1,
		
		// Global, rate, 1->50.0, 2
	kDynamicsProcessorParam_ExpansionRatio		= 2,
		
		// Global, dB
	kDynamicsProcessorParam_ExpansionThreshold	= 3,
		
		// Global, secs, 0.0001->0.2, 0.001
	kDynamicsProcessorParam_AttackTime 			= 4,
		
		// Global, secs, 0.01->3, 0.05
	kDynamicsProcessorParam_ReleaseTime 		= 5,
		
		// Global, dB, -40->40, 0
	kDynamicsProcessorParam_MasterGain 			= 6,
	
		// Global, dB, read-only parameter
	kDynamicsProcessorParam_CompressionAmount 	= 1000,
	kDynamicsProcessorParam_InputAmplitude		= 2000,
	kDynamicsProcessorParam_OutputAmplitude 	= 3000
};


// Parameters for the AUVarispeed unit
CF_ENUM(AudioUnitParameterID) {
		// Global, Rate, 0.25 -> 4.0, 1.0
	kVarispeedParam_PlaybackRate				= 0,
		// Global, Cents, -2400 -> 2400, 0.0
	kVarispeedParam_PlaybackCents				= 1
};


// Parameters for the Distortion unit 
CF_ENUM(AudioUnitParameterID) {
		// Global, Milliseconds, 0.1 -> 500, 0.1
	kDistortionParam_Delay = 0,
		// Global, Rate, 0.1 -> 50, 1.0
	kDistortionParam_Decay = 1,
		// Global, Percent, 0 -> 100, 50
	kDistortionParam_DelayMix = 2,
	
		// Global, Percent, 0 -> 100
	kDistortionParam_Decimation = 3,
		// Global, Percent, 0 -> 100, 0
	kDistortionParam_Rounding = 4,
		// Global, Percent, 0 -> 100, 50
	kDistortionParam_DecimationMix = 5,
	
		// Global, Linear Gain, 0 -> 1, 1
	kDistortionParam_LinearTerm = 6,  
		// Global, Linear Gain, 0 -> 20, 0
	kDistortionParam_SquaredTerm = 7,	
		// Global, Linear Gain, 0 -> 20, 0
	kDistortionParam_CubicTerm = 8,  
		// Global, Percent, 0 -> 100, 50
	kDistortionParam_PolynomialMix = 9,
	
		// Global, Hertz, 0.5 -> 8000, 100
	kDistortionParam_RingModFreq1 = 10,
		// Global, Hertz, 0.5 -> 8000, 100
	kDistortionParam_RingModFreq2 = 11,
		// Global, Percent, 0 -> 100, 50
	kDistortionParam_RingModBalance = 12,
		// Global, Percent, 0 -> 100, 0
	kDistortionParam_RingModMix = 13,
				
		// Global, dB, -80 -> 20, -6
	kDistortionParam_SoftClipGain = 14,
		
		// Global, Percent, 0 -> 100, 50
	kDistortionParam_FinalMix = 15
};

// Parameters for the AUDelay unit
CF_ENUM(AudioUnitParameterID) {
		// Global, EqPow Crossfade, 0->100, 50
	kDelayParam_WetDryMix 				= 0,
		
		// Global, Secs, 0->2, 1
	kDelayParam_DelayTime				= 1,
		
		// Global, Percent, -100->100, 50
	kDelayParam_Feedback 				= 2,
		
		// Global, Hz, 10->(SampleRate/2), 15000
	kDelayParam_LopassCutoff	 		= 3
};

// Parameters for the AUNBandEQ unit
// Note that the parameter IDs listed correspond to band 0 (zero) of the unit. The parameter IDs for
// higher bands can be obtained by adding the zero-indexed band number to the corresponding band 0
// parameter ID up to the number of bands minus one, where the number of bands is described by the
// AUNBandEQ property kAUNBandEQProperty_NumberOfBands. For example, the parameter ID corresponding
// to the filter type of band 4 would be kAUNBandEQParam_FilterType + 3.
// kAUNBandEQParam_GlobalsGain is an overall gain and does not have a band.
CF_ENUM(AudioUnitParameterID) {
    // Global, dB, -96->24, 0
	kAUNBandEQParam_GlobalGain								= 0,
	
    // Global, Boolean, 0 or 1, 1
	kAUNBandEQParam_BypassBand								= 1000,
	
    // Global, Indexed, 0->kNumAUNBandEQFilterTypes-1, 0
	kAUNBandEQParam_FilterType								= 2000,
	
    // Global, Hz, 20->(SampleRate/2), 1000
	kAUNBandEQParam_Frequency								= 3000,
	
    // Global, dB, -96->24, 0
	kAUNBandEQParam_Gain									= 4000,
	
    // Global, octaves, 0.05->5.0, 0.5
	kAUNBandEQParam_Bandwidth								= 5000
};

/*!
 @enum			AUNBandEQ filter types
 @discussion		Constants available as values for the kAUNBandEQParam_FilterType parameter defined above
 
 @constant		kAUNBandEQFilterType_Parametric
 Parametric filter based on Butterworth analog prototype. Uses parameterization where
 the bandwidth is specifed as the relationship of the upper bandedge frequency to the
 lower bandedge frequency in octaves, where the upper and lower bandedge frequencies are
 the respective frequencies above and below the center frequency at which the gain is
 equal to half the peak gain.
 Applicable parameters:
 - kAUNBandEQParam_Frequency (center frequency)
 - kAUNBandEQParam_Gain (peak gain)
 - kAUNBandEQParam_Bandwidth
 
 @constant		kAUNBandEQFilterType_2ndOrderButterworthLowPass
 Simple Butterworth 2nd order low pass filter
 Applicable parameters:
 - kAUNBandEQParam_Frequency (-3 dB cutoff frequency)
 
 @constant		kAUNBandEQFilterType_2ndOrderButterworthHighPass
 Simple Butterworth 2nd order high pass filter
 Applicable parameters:
 - kAUNBandEQParam_Frequency (-3 dB cutoff frequency)
 
 @constant		kAUNBandEQFilterType_ResonantLowPass
 Low pass filter with resonance support (via bandwidth parameter)
 Applicable parameters:
 - kAUNBandEQParam_Frequency (-3 dB cutoff frequency)
 - kAUNBandEQParam_Bandwidth
 
 @constant		kAUNBandEQFilterType_ResonantHighPass
 High pass filter with resonance support (via bandwidth parameter)
 Applicable parameters:
 - kAUNBandEQParam_Frequency (-3 dB cutoff frequency)
 - kAUNBandEQParam_Bandwidth
 
 @constant		kAUNBandEQFilterType_BandPass
 Band pass filter
 Applicable parameters:
 - kAUNBandEQParam_Frequency (center frequency)
 - kAUNBandEQParam_Bandwidth
 
 @constant		kAUNBandEQFilterType_BandStop
 Band stop filter (aka "notch filter")
 Applicable parameters:
 - kAUNBandEQParam_Frequency (center frequency)
 - kAUNBandEQParam_Bandwidth
 
 @constant		kAUNBandEQFilterType_LowShelf
 Low shelf filter
 Applicable parameters:
 - kAUNBandEQParam_Frequency (center frequency)
 - kAUNBandEQParam_Gain (shelf gain)
 
 @constant		kAUNBandEQFilterType_HighShelf
 High shelf filter
 Applicable parameters:
 - kAUNBandEQParam_Frequency (center frequency)
 - kAUNBandEQParam_Gain (shelf gain)
 
 @constant		kAUNBandEQFilterType_ResonantLowShelf
 Low shelf filter with resonance support (via bandwidth parameter)
 Applicable parameters:
 - kAUNBandEQParam_Frequency (center frequency)
 - kAUNBandEQParam_Gain (shelf gain)
 - kAUNBandEQParam_Bandwidth
 
 @constant		kAUNBandEQFilterType_ResonantHighShelf
 High shelf filter with resonance support (via bandwidth parameter)
 Applicable parameters:
 - kAUNBandEQParam_Frequency (center frequency)
 - kAUNBandEQParam_Gain (shelf gain)
 - kAUNBandEQParam_Bandwidth
 
 */
CF_ENUM(long) {
	kAUNBandEQFilterType_Parametric 						= 0,
	kAUNBandEQFilterType_2ndOrderButterworthLowPass			= 1,
	kAUNBandEQFilterType_2ndOrderButterworthHighPass		= 2,
	kAUNBandEQFilterType_ResonantLowPass					= 3,
	kAUNBandEQFilterType_ResonantHighPass					= 4,
	kAUNBandEQFilterType_BandPass							= 5,
	kAUNBandEQFilterType_BandStop							= 6,
	kAUNBandEQFilterType_LowShelf							= 7,
	kAUNBandEQFilterType_HighShelf							= 8,
	kAUNBandEQFilterType_ResonantLowShelf					= 9,
	kAUNBandEQFilterType_ResonantHighShelf					= 10,
	
	kNumAUNBandEQFilterTypes								= 11
};


// Parameters for the AURoundTripAACParam unit
CF_ENUM(AudioUnitParameterID) {
		// Global, indexed : AAC, HE-AAC, HE-AACv2
	kRoundTripAACParam_Format				= 0,
	
		// Global, indexed
	kRoundTripAACParam_EncodingStrategy = 1,

		// Global, indexed
	kRoundTripAACParam_RateOrQuality = 2,

		// These are deprecated:
#if !TARGET_OS_IPHONE
	kRoundTripAACParam_BitRate				= 1,
	kRoundTripAACParam_Quality 				= 2,
	kRoundTripAACParam_CompressedFormatSampleRate = 3
#endif
};

#pragma mark Apple Specific - Desktop

#if !TARGET_OS_IPHONE

// Some parameters for the AUGraphicEQ unit
CF_ENUM(AudioUnitParameterID) {
		// Global, Indexed, currently either 10 or 31
	kGraphicEQParam_NumberOfBands 			= 10000
};

// Parameters for the AUMatrixReverb unit
CF_ENUM(AudioUnitParameterID) {
		// Global, EqPow CrossFade, 0->100, 100
	kReverbParam_DryWetMix 							= 0,
		
		// Global, EqPow CrossFade, 0->100, 50
	kReverbParam_SmallLargeMix						= 1,
		
		// Global, Secs, 0.005->0.020, 0.06
	kReverbParam_SmallSize							= 2,
		
		// Global, Secs, 0.4->10.0, 3.07
	kReverbParam_LargeSize							= 3,
		
		// Global, Secs, 0.001->0.03, 0.025
	kReverbParam_PreDelay							= 4,
		
		// Global, Secs, 0.001->0.1, 0.035
	kReverbParam_LargeDelay							= 5,
		
		// Global, Genr, 0->1, 0.28
	kReverbParam_SmallDensity						= 6,
		
		// Global, Genr, 0->1, 0.82
	kReverbParam_LargeDensity						= 7,
		
		// Global, Genr, 0->1, 0.3
	kReverbParam_LargeDelayRange					= 8,
		
		// Global, Genr, 0.1->1, 0.96
	kReverbParam_SmallBrightness					= 9,
		
		// Global, Genr, 0.1->1, 0.49
	kReverbParam_LargeBrightness					= 10,

		// Global, Genr, 0->1 0.5
	kReverbParam_SmallDelayRange					= 11,

		// Global, Hz, 0.001->2.0, 1.0
	kReverbParam_ModulationRate						= 12,

		// Global, Genr, 0.0 -> 1.0, 0.2
	kReverbParam_ModulationDepth					= 13,
};

// Parameters for the AUMultibandCompressor unit
CF_ENUM(AudioUnitParameterID) {
		// Global, dB, -40 -> 40, 0
	kMultibandCompressorParam_Pregain 			= 0,
		// Global, dB, -40 -> 40, 0
	kMultibandCompressorParam_Postgain 			= 1,
		// Global, Hertz, 20 -> (SampleRate/2), 120.0
	kMultibandCompressorParam_Crossover1 		= 2,
		// Global, Hertz, 20 -> (SampleRate/2), 700.0
	kMultibandCompressorParam_Crossover2 		= 3,
		// Global, Hertz, 20 -> (SampleRate/2), 3000.0
	kMultibandCompressorParam_Crossover3 		= 4,
		// Global, dB, -100.0 -> 0.0, -22.0
	kMultibandCompressorParam_Threshold1 		= 5,
		// Global, dB, -100.0 -> 0.0, -32.0
	kMultibandCompressorParam_Threshold2 		= 6,
		// Global, dB, -100.0 -> 0.0, -33.0
	kMultibandCompressorParam_Threshold3 		= 7,
		// Global, dB, -100.0 -> 0.0, -36.0
	kMultibandCompressorParam_Threshold4 		= 8,
		// Global, dB, 0.1 -> 40.0, 5.0
	kMultibandCompressorParam_Headroom1 		= 9,
		// Global, dB, 0.1 -> 40.0, 12.0
	kMultibandCompressorParam_Headroom2 		= 10,
		// Global, dB, 0.1 -> 40.0, 5.0
	kMultibandCompressorParam_Headroom3 		= 11,
		// Global, dB, 0.1 -> 40.0, 7.5
	kMultibandCompressorParam_Headroom4 		= 12,
		// Global, Secs, 0.001 -> 0.200, 0.080
	kMultibandCompressorParam_AttackTime 		= 13,
		// Global, Secs, 0.010 -> 3.0, 0.120
	kMultibandCompressorParam_ReleaseTime 		= 14,
		// Global, dB, -20 -> 20, 0
	kMultibandCompressorParam_EQ1 				= 15,
		// Global, dB, -20 -> 20, 0
	kMultibandCompressorParam_EQ2 				= 16,
		// Global, dB, -20 -> 20, 0
	kMultibandCompressorParam_EQ3 				= 17,
		// Global, dB, -20 -> 20, 0
	kMultibandCompressorParam_EQ4 				= 18,
	
	// read-only parameters
		// Global, dB, 0 -> 20
	kMultibandCompressorParam_CompressionAmount1 = 1000,
		// Global, dB, 0 -> 20
	kMultibandCompressorParam_CompressionAmount2 = 2000,
		// Global, dB, 0 -> 20
	kMultibandCompressorParam_CompressionAmount3 = 3000,
		// Global, dB, 0 -> 20
	kMultibandCompressorParam_CompressionAmount4 = 4000,

		// Global, dB, -120 -> 20
	kMultibandCompressorParam_InputAmplitude1 = 5000,
		// Global, dB, -120 -> 20
	kMultibandCompressorParam_InputAmplitude2 = 6000,
		// Global, dB, -120 -> 20
	kMultibandCompressorParam_InputAmplitude3 = 7000,
		// Global, dB, -120 -> 20
	kMultibandCompressorParam_InputAmplitude4 = 8000,

		// Global, dB, -120 -> 20
	kMultibandCompressorParam_OutputAmplitude1 = 9000,
		// Global, dB, -120 -> 20
	kMultibandCompressorParam_OutputAmplitude2 = 10000,
		// Global, dB, -120 -> 20
	kMultibandCompressorParam_OutputAmplitude3 = 11000,
		// Global, dB, -120 -> 20
	kMultibandCompressorParam_OutputAmplitude4 = 12000
};

// Parameters for the AUFilter unit
CF_ENUM(AudioUnitParameterID)
{
		// Global, indexed, 0 -> 1, 0
	kMultibandFilter_LowFilterType  = 0,
		// Global, Hertz, 10 -> (SampleRate/2), 100
	kMultibandFilter_LowFrequency   = 1,
		// Global, dB, -18 -> +18, 0
	kMultibandFilter_LowGain		= 2,

		// Global, Hertz, 10 -> (SampleRate/2), 100
	kMultibandFilter_CenterFreq1	= 3,
		// Global, dB, -18 -> +18, 0
	kMultibandFilter_CenterGain1	= 4,
		// Global, Octaves, 0.05 -> 3.0, 2.0
	kMultibandFilter_Bandwidth1		= 5,
	
		// Global, Hertz, 10 -> (SampleRate/2), 100
	kMultibandFilter_CenterFreq2	= 6,
		// Global, dB, -18 -> +18, 0
	kMultibandFilter_CenterGain2	= 7,
		// Global, Octaves, 0.05 -> 3.0, 2.0
	kMultibandFilter_Bandwidth2		= 8,
	
		// Global, Hertz, 10 -> (SampleRate/2), 100
	kMultibandFilter_CenterFreq3	= 9,
		// Global, dB, -18 -> +18, 0
	kMultibandFilter_CenterGain3	= 10,
		// Global, Octaves, 0.05 -> 3.0, 2.0
	kMultibandFilter_Bandwidth3		= 11,

		// Global, indexed, 0 -> 1, 0
	kMultibandFilter_HighFilterType	= 12,
		// Global, Hertz, 10 -> (SampleRate/2), 100
	kMultibandFilter_HighFrequency  = 13,
		// Global, dB, -18 -> +18, 0
	kMultibandFilter_HighGain		= 14
};

// Parameters for AURogerBeep
CF_ENUM(AudioUnitParameterID) {
		// Global, dB, -80 -> 0, -6
	kRogerBeepParam_InGateThreshold = 0,
		// Global, Milliseconds, 0 -> 1000, 1000
	kRogerBeepParam_InGateThresholdTime = 1,
		// Global, dB, -80 -> 0, -6
	kRogerBeepParam_OutGateThreshold = 2,
		// Global, Milliseconds, 0 -> 1000, 1000
	kRogerBeepParam_OutGateThresholdTime = 3,	
		// Global, indexed, 0 -> 2, 2
	kRogerBeepParam_Sensitivity = 4,	
		// Global, indexed, 0 -> 2, 0
	kRogerBeepParam_RogerType = 5,
		// Global, dB, -80 -> 20, -6
	kRogerBeepParam_RogerGain = 6
};

// Mixer Units

// Parameters for the Stereo Mixer unit
CF_ENUM(AudioUnitParameterID) {
		// Input/Output, Mixer Fader Curve, 0->1, 1
	kStereoMixerParam_Volume 	= 0,
		
		// Input, Pan, 0->1, 0.5
	kStereoMixerParam_Pan		= 1,
	
		// read-only
		//
		// For each of the following, use the parameter ID for the left channel
		// and the parameter ID plus one for the right channel.
		// For example, kStereoMixerParam_PostAveragePower indicates the left channel
		// while kStereiMixerParam_PostAveragePower + 1 indicates the right channel.
	kStereoMixerParam_PreAveragePower	= 1000,
	kStereoMixerParam_PrePeakHoldLevel	= 2000,
	kStereoMixerParam_PostAveragePower	= 3000,
	kStereoMixerParam_PostPeakHoldLevel	= 4000
};

// Parameters for the AUNetReceive unit
CF_ENUM(AudioUnitParameterID) {
		// Global, indexed, 0 -> 5, read only
	kAUNetReceiveParam_Status = 0,
	kAUNetReceiveParam_NumParameters = 1
};

// Parameters for the AUNetSend unit
CF_ENUM(AudioUnitParameterID) {
		// Global, indexed, 0 -> 5, read only
	kAUNetSendParam_Status = 0,
	kAUNetSendParam_NumParameters = 1
};


// Status values for the AUNetSend and AUNetReceive units
enum {
	kAUNetStatus_NotConnected = 0,
	kAUNetStatus_Connected = 1,
	kAUNetStatus_Overflow = 2,
	kAUNetStatus_Underflow = 3,
	kAUNetStatus_Connecting = 4,
	kAUNetStatus_Listening = 5
};

// Music Device
// Parameters for the DLSMusicDevice unit - defined and reported in the global scope
CF_ENUM(AudioUnitParameterID) {
		// Global, Cents, -1200, 1200, 0
	kMusicDeviceParam_Tuning 	= 0,

		// Global, dB, -120->40, 0
	kMusicDeviceParam_Volume	= 1,

		// Global, dB, -120->40, 0
	kMusicDeviceParam_ReverbVolume	= 2
};
// In Mac OS X v10.5, the DLSMusicDevice audio unit does not report parameters in the Group scope.
// However, parameter values can be set in Group scope that correspond to controller values defined  
// by the MIDI specification. This includes the standard MIDI Controller values (such as Volume and
// Mod Wheel) as well as MIDI status messages (such as Pitch Bend and Channel Pressure) and the 
// MIDI RPN control messages.

// For MIDI status messages, use a value of 0 for the "channel part" (lower four bits) when setting  
// these parameters. This allows audio units to distinguish these IDs from the 0-127 
// values used by MIDI controllers in the first byte of status messages.
// 
// The element ID represents the group or channel number.
//
// You can use the MusicDeviceMIDIEvent function to send a MIDI formatted control command to a device.
//
// You can use the SetParameter API calls, declared in the AUComponent.h header file, as follows:
//
//	scope == kAudioUnitScope_Group
//	element == groupID -> in MIDI equivalent to channel number 0->15, 
//			but this is not a limitation of the MusicDevice and values greater than 15 can be specified
//	paramID == midi controller value (0->127), (status bytes corresponding to pitch bend, channel pressure)
//	value == typically the range associated with the corresponding MIDI message	(7 bit, 0->127)
//			pitch bend is specified as a 14 bit value
	
// See the MusicDevice.h header file for more about using the extended control semantics 
// of this API.	

#endif // !TARGET_OS_IPHONE

// `Analog' AudioUnits


// Parameters for the AURandom unit
CF_ENUM(AudioUnitParameterID) {
	kRandomParam_BoundA 			= 0,
	kRandomParam_BoundB				= 1,
	kRandomParam_Curve				= 2
};


#pragma mark Apple Specific - iOS


// Parameters for the iOS reverb unit
CF_ENUM(AudioUnitParameterID) {
		// Global, CrossFade, 0->100, 100
	kReverb2Param_DryWetMix 						= 0,
		// Global, Decibels, -20->20, 0
	kReverb2Param_Gain								= 1,
		
		// Global, Secs, 0.0001->1.0, 0.008
	kReverb2Param_MinDelayTime						= 2,
		// Global, Secs, 0.0001->1.0, 0.050
	kReverb2Param_MaxDelayTime						= 3,
		// Global, Secs, 0.001->20.0, 1.0
	kReverb2Param_DecayTimeAt0Hz					= 4,
		// Global, Secs, 0.001->20.0, 0.5
	kReverb2Param_DecayTimeAtNyquist				= 5,
		// Global, Integer, 1->1000
	kReverb2Param_RandomizeReflections				= 6,
};

#endif //AudioUnit_AudioUnitParameters_h
#else
#include <AudioToolboxCore/AudioUnitParameters.h>
#endif
// ==========  AudioToolbox.framework/Headers/AudioConverter.h
#if (defined(USE_AUDIOTOOLBOX_PUBLIC_HEADERS) && USE_AUDIOTOOLBOX_PUBLIC_HEADERS) || !__has_include(<AudioToolboxCore/AudioConverter.h>)
/*!
	@file		AudioConverter.h
	@framework	AudioToolbox.framework
	@copyright	(c) 1985-2015 by Apple, Inc., all rights reserved.
    @abstract   API's to perform audio format conversions.
    
    @discussion
		AudioConverters convert between various linear PCM and compressed
		audio formats. Supported transformations include:

		- PCM float/integer/bit depth conversions
		- PCM sample rate conversion
		- PCM interleaving and deinterleaving
		- encoding PCM to compressed formats
		- decoding compressed formats to PCM

		A single AudioConverter may perform more than one
		of the above transformations.
*/

#ifndef AudioToolbox_AudioConverter_h
#define AudioToolbox_AudioConverter_h

//=============================================================================
//  Includes
//=============================================================================

#include <Availability.h>
#include <CoreAudioTypes/CoreAudioTypes.h>

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//  Theory of Operation
//=============================================================================

//=============================================================================
//  Types specific to the Audio Converter API
//=============================================================================

/*!
    @typedef    AudioConverterRef
    @abstract   A reference to an AudioConverter object.
*/
typedef struct OpaqueAudioConverter *   AudioConverterRef;

typedef UInt32                          AudioConverterPropertyID;

//=============================================================================
//  Standard Properties
//=============================================================================

/*!
    @enum       AudioConverterPropertyID
    @abstract   The properties of an AudioConverter, accessible via AudioConverterGetProperty()
                and AudioConverterSetProperty().
    
    @constant   kAudioConverterPropertyMinimumInputBufferSize
                    a UInt32 that indicates the size in bytes of the smallest buffer of input
                    data that can be supplied via the AudioConverterInputProc or as the input to
                    AudioConverterConvertBuffer
    @constant   kAudioConverterPropertyMinimumOutputBufferSize
                    a UInt32 that indicates the size in bytes of the smallest buffer of output
                    data that can be supplied to AudioConverterFillComplexBuffer or as the output to
                    AudioConverterConvertBuffer
    @constant   kAudioConverterPropertyMaximumInputPacketSize
                    a UInt32 that indicates the size in bytes of the largest single packet of
                    data in the input format. This is mostly useful for variable bit rate
                    compressed data (decoders).
    @constant   kAudioConverterPropertyMaximumOutputPacketSize
                    a UInt32 that indicates the size in bytes of the largest single packet of
                    data in the output format. This is mostly useful for variable bit rate
                    compressed data (encoders).
    @constant   kAudioConverterPropertyCalculateInputBufferSize
                    a UInt32 that on input holds a size in bytes that is desired for the output
                    data. On output, it will hold the size in bytes of the input buffer required
                    to generate that much output data. Note that some converters cannot do this
                    calculation.
    @constant   kAudioConverterPropertyCalculateOutputBufferSize
                    a UInt32 that on input holds a size in bytes that is desired for the input
                    data. On output, it will hold the size in bytes of the output buffer
                    required to hold the output data that will be generated. Note that some
                    converters cannot do this calculation.
    @constant   kAudioConverterPropertyInputCodecParameters
                    The value of this property varies from format to format and is considered
                    private to the format. It is treated as a buffer of untyped data.
    @constant   kAudioConverterPropertyOutputCodecParameters
                    The value of this property varies from format to format and is considered
                    private to the format. It is treated as a buffer of untyped data.
    @constant   kAudioConverterSampleRateConverterComplexity
                    An OSType that specifies the sample rate converter algorithm to use (as defined in
                    AudioToolbox/AudioUnitProperties.h)
    @constant   kAudioConverterSampleRateConverterQuality
                    A UInt32 that specifies rendering quality of the sample rate converter (see
                    enum constants below)
    @constant   kAudioConverterSampleRateConverterInitialPhase
                    A Float64 with value 0.0 <= x < 1.0 giving the initial subsample position of the 
                    sample rate converter.
    @constant   kAudioConverterCodecQuality
                    A UInt32 that specifies rendering quality of a codec (see enum constants
                    below)
    @constant   kAudioConverterPrimeMethod
                    a UInt32 specifying priming method (usually for sample-rate converter) see
                    explanation for struct AudioConverterPrimeInfo below along with enum
                    constants
    @constant   kAudioConverterPrimeInfo
                    A pointer to AudioConverterPrimeInfo (see explanation for struct
                    AudioConverterPrimeInfo below)
    @constant   kAudioConverterChannelMap
                    An array of SInt32's.  The size of the array is the number of output
                    channels, and each element specifies which input channel's data is routed to
                    that output channel (using a 0-based index of the input channels), or -1 if
                    no input channel is to be routed to that output channel.  The default
                    behavior is as follows. I = number of input channels, O = number of output
                    channels. When I > O, the first O inputs are routed to the first O outputs,
                    and the remaining puts discarded.  When O > I, the first I inputs are routed
                    to the first O outputs, and the remaining outputs are zeroed.
                    
                    A simple example for splitting mono input to stereo output (instead of routing
                    the input to only the first output channel):
                    
<pre>
   // this should be as large as the number of output channels:
  SInt32 channelMap[2] = { 0, 0 };
  AudioConverterSetProperty(theConverter, kAudioConverterChannelMap, 
    sizeof(channelMap), channelMap);
</pre>
    @constant   kAudioConverterDecompressionMagicCookie
                    A void * pointing to memory set up by the caller. Required by some formats
                    in order to decompress the input data.
    @constant   kAudioConverterCompressionMagicCookie
                    A void * pointing to memory set up by the caller. Returned by the converter
                    so that it may be stored along with the output data. It can then be passed
                    back to the converter for decompression at a later time.
    @constant   kAudioConverterEncodeBitRate
                    A UInt32 containing the number of bits per second to aim for when encoding
                    data. Some decoders will also allow you to get this property to discover the bit rate.
    @constant   kAudioConverterEncodeAdjustableSampleRate
                    For encoders where the AudioConverter was created with an output sample rate
                    of zero, and the codec can do rate conversion on its input, this provides a
                    way to set the output sample rate. The property value is a Float64.
    @constant   kAudioConverterInputChannelLayout
                    The property value is an AudioChannelLayout.
    @constant   kAudioConverterOutputChannelLayout
                    The property value is an AudioChannelLayout.
    @constant   kAudioConverterApplicableEncodeBitRates
                    The property value is an array of AudioValueRange describing applicable bit
                    rates based on current settings.
    @constant   kAudioConverterAvailableEncodeBitRates
                    The property value is an array of AudioValueRange describing available bit
                    rates based on the input format. You can get all available bit rates from
                    the AudioFormat API.
    @constant   kAudioConverterApplicableEncodeSampleRates
                    The property value is an array of AudioValueRange describing applicable
                    sample rates based on current settings.
    @constant   kAudioConverterAvailableEncodeSampleRates
                    The property value is an array of AudioValueRange describing available
                    sample rates based on the input format. You can get all available sample
                    rates from the AudioFormat API.
    @constant   kAudioConverterAvailableEncodeChannelLayoutTags
                    The property value is an array of AudioChannelLayoutTags for the format and
                    number of channels specified in the input format going to the encoder.
    @constant   kAudioConverterCurrentOutputStreamDescription
                    Returns the current completely specified output AudioStreamBasicDescription.
                    For example when encoding to AAC, your original output stream description
                    will not have been completely filled out.
    @constant   kAudioConverterCurrentInputStreamDescription
                    Returns the current completely specified input AudioStreamBasicDescription.
    @constant   kAudioConverterPropertySettings
                    Returns the a CFArray of property settings for converters.
    @constant   kAudioConverterPropertyBitDepthHint
                    An SInt32 of the source bit depth to preserve. This is a hint to some
                    encoders like lossless about how many bits to preserve in the input. The
                    converter usually tries to preserve as many as possible, but a lossless
                    encoder will do poorly if more bits are supplied than are desired in the
                    output. The bit depth is expressed as a negative number if the source was floating point,
                    e.g. -32 for float, -64 for double.
    @constant   kAudioConverterPropertyFormatList
                    An array of AudioFormatListItem structs describing all the data formats produced by the
                    encoder end of the AudioConverter. If the ioPropertyDataSize parameter indicates that
                    outPropertyData is sizeof(AudioFormatListItem), then only the best format is returned.
                    This property may be used for example to discover all the data formats produced by the AAC_HE2
                    (AAC High Efficiency vers. 2) encoder.
*/
CF_ENUM(AudioConverterPropertyID)
{
    kAudioConverterPropertyMinimumInputBufferSize       = 'mibs',
    kAudioConverterPropertyMinimumOutputBufferSize      = 'mobs',
    kAudioConverterPropertyMaximumInputPacketSize       = 'xips',
    kAudioConverterPropertyMaximumOutputPacketSize      = 'xops',
    kAudioConverterPropertyCalculateInputBufferSize     = 'cibs',
    kAudioConverterPropertyCalculateOutputBufferSize    = 'cobs',
    kAudioConverterPropertyInputCodecParameters         = 'icdp',
    kAudioConverterPropertyOutputCodecParameters        = 'ocdp',
    kAudioConverterSampleRateConverterComplexity        = 'srca',
    kAudioConverterSampleRateConverterQuality           = 'srcq',
    kAudioConverterSampleRateConverterInitialPhase      = 'srcp',
    kAudioConverterCodecQuality                         = 'cdqu',
    kAudioConverterPrimeMethod                          = 'prmm',
    kAudioConverterPrimeInfo                            = 'prim',
    kAudioConverterChannelMap                           = 'chmp',
    kAudioConverterDecompressionMagicCookie             = 'dmgc',
    kAudioConverterCompressionMagicCookie               = 'cmgc',
    kAudioConverterEncodeBitRate                        = 'brat',
    kAudioConverterEncodeAdjustableSampleRate           = 'ajsr',
    kAudioConverterInputChannelLayout                   = 'icl ',
    kAudioConverterOutputChannelLayout                  = 'ocl ',
    kAudioConverterApplicableEncodeBitRates             = 'aebr',
    kAudioConverterAvailableEncodeBitRates              = 'vebr',
    kAudioConverterApplicableEncodeSampleRates          = 'aesr',
    kAudioConverterAvailableEncodeSampleRates           = 'vesr',
    kAudioConverterAvailableEncodeChannelLayoutTags     = 'aecl',
    kAudioConverterCurrentOutputStreamDescription       = 'acod',
    kAudioConverterCurrentInputStreamDescription        = 'acid',
    kAudioConverterPropertySettings                     = 'acps',
    kAudioConverterPropertyBitDepthHint                 = 'acbd',
    kAudioConverterPropertyFormatList                   = 'flst'
};

#if !TARGET_OS_IPHONE
//=============================================================================
//  
//=============================================================================

/*!
    @enum       Mac OS X AudioConverter Properties

    @constant   kAudioConverterPropertyDithering
					A UInt32. Set to a value from the enum of dithering algorithms below. 
					Zero means no dithering and is the default. (Mac OS X only.)
    @constant   kAudioConverterPropertyDitherBitDepth
					A UInt32. Dither is applied at this bit depth.  (Mac OS X only.)

*/
CF_ENUM(AudioConverterPropertyID)
{
	kAudioConverterPropertyDithering					= 'dith',
	kAudioConverterPropertyDitherBitDepth				= 'dbit'
};

/*!
    @enum       Dithering algorithms

    @abstract   Constants to be used as the value for kAudioConverterPropertyDithering.

    @constant   kDitherAlgorithm_TPDF             Dither signal is generated by a white noise source with a triangular probability density function
    @constant   kDitherAlgorithm_NoiseShaping     Use a static, perceptually weighted noise shaped dither
*/
CF_ENUM(UInt32)
{
	kDitherAlgorithm_TPDF				= 1,	
	kDitherAlgorithm_NoiseShaping		= 2 
};
#endif

/*!
    @enum       Quality constants

    @abstract   Constants to be used with kAudioConverterSampleRateConverterQuality.

    @constant   kAudioConverterQuality_Max          maximum quality
    @constant   kAudioConverterQuality_High         high quality
    @constant   kAudioConverterQuality_Medium       medium quality
    @constant   kAudioConverterQuality_Low          low quality
    @constant   kAudioConverterQuality_Min          minimum quality
*/
CF_ENUM(UInt32)
{
    kAudioConverterQuality_Max                              = 0x7F,
    kAudioConverterQuality_High                             = 0x60,
    kAudioConverterQuality_Medium                           = 0x40,
    kAudioConverterQuality_Low                              = 0x20,
    kAudioConverterQuality_Min                              = 0
};


/*!
    @enum           Sample Rate Converter Complexity
    @constant       kAudioConverterSampleRateConverterComplexity_Linear
    @discussion         Linear interpolation. lowest quality, cheapest.
						InitialPhase and PrimeMethod properties are not operative with this mode.
    @constant       kAudioConverterSampleRateConverterComplexity_Normal
    @discussion         Normal quality sample rate conversion.
    @constant       kAudioConverterSampleRateConverterComplexity_Mastering
    @discussion         Mastering quality sample rate conversion. More expensive.
    @constant       kAudioConverterSampleRateConverterComplexity_MinimumPhase
    @discussion         Minimum phase impulse response. Stopband attenuation varies with quality setting.
                        The InitialPhase and PrimeMethod properties are not operative with this mode.
                        There are three levels of quality provided.
                            kAudioConverterQuality_Low (or Min)  : noise floor to -96 dB
                            kAudioConverterQuality_Medium        : noise floor to -144 dB
                            kAudioConverterQuality_High (or Max) : noise floor to -160 dB (this uses double precision internally)
						Quality equivalences to the other complexity modes are very roughly as follows:
							MinimumPhase Low    is somewhat better than Normal Medium.
							MinimumPhase Medium is similar to Normal Max.
							MinimumPhase High   is similar to Mastering Low.
						In general, MinimumPhase performs better than Normal and Mastering for the equivalent qualities listed above.
						MinimumPhase High is several times faster than Mastering Low.
 
*/
CF_ENUM(UInt32)
{
    kAudioConverterSampleRateConverterComplexity_Linear             = 'line',   // linear interpolation
    kAudioConverterSampleRateConverterComplexity_Normal             = 'norm',   // normal quality range, the default
    kAudioConverterSampleRateConverterComplexity_Mastering          = 'bats',   // higher quality range, more expensive
    kAudioConverterSampleRateConverterComplexity_MinimumPhase       = 'minp'	// minimum phase impulse response.
};


/*!
    @enum       Prime method constants

    @abstract   Constants to be used with kAudioConverterPrimeMethod.
    
    @constant   kConverterPrimeMethod_Pre
                    Primes with leading + trailing input frames.
    @constant   kConverterPrimeMethod_Normal
                    Only primes with trailing (zero latency). Leading frames are assumed to be
                    silence.
    @constant   kConverterPrimeMethod_None
                    Acts in "latency" mode. Both leading and trailing frames assumed to be
                    silence.
*/
CF_ENUM(UInt32)
{
    kConverterPrimeMethod_Pre       = 0,
    kConverterPrimeMethod_Normal    = 1,
    kConverterPrimeMethod_None      = 2
};

/*!
    @struct     AudioConverterPrimeInfo
    @abstract   Specifies priming information.
    
    @var        leadingFrames
        Specifies the number of leading (previous) input frames, relative to the normal/desired
        start input frame, required by the converter to perform a high quality conversion. If
        using kConverterPrimeMethod_Pre, the client should "pre-seek" the input stream provided
        through the input proc by leadingFrames. If no frames are available previous to the
        desired input start frame (because, for example, the desired start frame is at the very
        beginning of available audio), then provide "leadingFrames" worth of initial zero frames
        in the input proc.  Do not "pre-seek" in the default case of
        kConverterPrimeMethod_Normal or when using kConverterPrimeMethod_None.

    @var        trailingFrames
        Specifies the number of trailing input frames (past the normal/expected end input frame)
        required by the converter to perform a high quality conversion.  The client should be
        prepared to provide this number of additional input frames except when using
        kConverterPrimeMethod_None. If no more frames of input are available in the input stream
        (because, for example, the desired end frame is at the end of an audio file), then zero
        (silent) trailing frames will be synthesized for the client.
            
    @discussion
        When using AudioConverterFillComplexBuffer() (either a single call or a series of calls), some
        conversions, particularly involving sample-rate conversion, ideally require a certain
        number of input frames previous to the normal start input frame and beyond the end of
        the last expected input frame in order to yield high-quality results.
        
        These are expressed in the leadingFrames and trailingFrames members of the structure.
        
        The very first call to AudioConverterFillComplexBuffer(), or first call after
        AudioConverterReset(), will request additional input frames beyond those normally
        expected in the input proc callback to fulfill this first AudioConverterFillComplexBuffer()
        request. The number of additional frames requested, depending on the prime method, will
        be approximately:

        <pre>
            kConverterPrimeMethod_Pre       leadingFrames + trailingFrames
            kConverterPrimeMethod_Normal    trailingFrames
            kConverterPrimeMethod_None      0
        </pre>

        Thus, in effect, the first input proc callback(s) may provide not only the leading
        frames, but also may "read ahead" by an additional number of trailing frames depending
        on the prime method.

        kConverterPrimeMethod_None is useful in a real-time application processing live input,
        in which case trailingFrames (relative to input sample rate) of through latency will be
        seen at the beginning of the output of the AudioConverter.  In other real-time
        applications such as DAW systems, it may be possible to provide these initial extra
        audio frames since they are stored on disk or in memory somewhere and
        kConverterPrimeMethod_Pre may be preferable.  The default method is
        kConverterPrimeMethod_Normal, which requires no pre-seeking of the input stream and
        generates no latency at the output.
*/
struct AudioConverterPrimeInfo {
    UInt32      leadingFrames;
    UInt32      trailingFrames;
};
typedef struct AudioConverterPrimeInfo AudioConverterPrimeInfo;

//=============================================================================
//  Errors
//=============================================================================

CF_ENUM(OSStatus)
{
    kAudioConverterErr_FormatNotSupported       = 'fmt?',
    kAudioConverterErr_OperationNotSupported    = 0x6F703F3F, // 'op??', integer used because of trigraph
    kAudioConverterErr_PropertyNotSupported     = 'prop',
    kAudioConverterErr_InvalidInputSize         = 'insz',
    kAudioConverterErr_InvalidOutputSize        = 'otsz',
        // e.g. byte size is not a multiple of the frame size
    kAudioConverterErr_UnspecifiedError         = 'what',
    kAudioConverterErr_BadPropertySizeError     = '!siz',
    kAudioConverterErr_RequiresPacketDescriptionsError = '!pkd',
    kAudioConverterErr_InputSampleRateOutOfRange    = '!isr',
    kAudioConverterErr_OutputSampleRateOutOfRange   = '!osr'
};

#if TARGET_OS_IPHONE
/*!
    @enum       AudioConverter errors (iPhone only)
    @abstract   iPhone-specific OSStatus results for AudioConverter
    
    @constant   kAudioConverterErr_HardwareInUse
                    Returned from AudioConverterFillComplexBuffer if the underlying hardware codec has
                    become unavailable, probably due to an interruption. In this case, your application
                    must stop calling AudioConverterFillComplexBuffer. If the converter can resume from an
                    interruption (see kAudioConverterPropertyCanResumeFromInterruption), you must
                    wait for an EndInterruption notification from AudioSession, and call AudioSessionSetActive(true)
                    before resuming.
    @constant   kAudioConverterErr_NoHardwarePermission
                    Returned from AudioConverterNew if the new converter would use a hardware codec
                    which the application does not have permission to use.
*/  
CF_ENUM(OSStatus)
{
    kAudioConverterErr_HardwareInUse 		= 'hwiu',
    kAudioConverterErr_NoHardwarePermission = 'perm'
};
#endif

//=============================================================================
//  Routines
//=============================================================================

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterNew
    @abstract   Create a new AudioConverter.

    @param      inSourceFormat
                    The format of the source audio to be converted.
    @param      inDestinationFormat
                    The destination format to which the audio is to be converted.
    @param      outAudioConverter
                    On successful return, points to a new AudioConverter instance.
    @result     An OSStatus result code.
    
    @discussion
                For a pair of linear PCM formats, the following conversions
                are supported:
                
                <ul>
                <li>addition and removal of channels, when the stream descriptions'
                mChannelsPerFrame does not match. Channels may also be reordered and removed
                using the kAudioConverterChannelMap property.</li>
                <li>sample rate conversion</li>
                <li>interleaving/deinterleaving, when the stream descriptions' (mFormatFlags &
                kAudioFormatFlagIsNonInterleaved) does not match.</li>
                <li>conversion between any pair of the following formats:</li>
                    <ul>
                    <li>8 bit integer, signed or unsigned</li>
                    <li>16, 24, or 32-bit integer, big- or little-endian. Other integral
                    bit depths, if high-aligned and non-packed, are also supported</li>
                    <li>32 and 64-bit float, big- or little-endian.</li>
                    </ul>
                </ul>
                
                Also, encoding and decoding between linear PCM and compressed formats is
                supported. Functions in AudioToolbox/AudioFormat.h return information about the
                supported formats. When using a codec, you can use any supported PCM format (as
                above); the converter will perform any necessary additional conversion between
                your PCM format and the one created or consumed by the codec.
*/
extern OSStatus
AudioConverterNew(      const AudioStreamBasicDescription * inSourceFormat,
                        const AudioStreamBasicDescription * inDestinationFormat,
                        AudioConverterRef __nullable * __nonnull outAudioConverter)      API_AVAILABLE(macos(10.1), ios(2.0), watchos(2.0), tvos(9.0));


//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterNewSpecific
    @abstract   Create a new AudioConverter using specific codecs.

    @param      inSourceFormat
                    The format of the source audio to be converted.
    @param      inDestinationFormat
                    The destination format to which the audio is to be converted.
    @param      inNumberClassDescriptions
                    The number of class descriptions.
    @param      inClassDescriptions
                    AudioClassDescriptions specifiying the codec to instantiate.
    @param      outAudioConverter
                    On successful return, points to a new AudioConverter instance.
    @result     An OSStatus result code.
    
    @discussion
                This function is identical to AudioConverterNew(), except that the client may
                explicitly choose which codec to instantiate if there is more than one choice.
*/
extern OSStatus
AudioConverterNewSpecific(  const AudioStreamBasicDescription * inSourceFormat,
                            const AudioStreamBasicDescription * inDestinationFormat,
                            UInt32                              inNumberClassDescriptions,
                            const AudioClassDescription *       inClassDescriptions,
                            AudioConverterRef __nullable * __nonnull outAudioConverter)
                                                                                API_AVAILABLE(macos(10.4), ios(2.0), watchos(2.0), tvos(9.0));

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterDispose
    @abstract   Destroy an AudioConverter.

    @param      inAudioConverter
                    The AudioConverter to dispose.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioConverterDispose(  AudioConverterRef   inAudioConverter)                   API_AVAILABLE(macos(10.1), ios(2.0), watchos(2.0), tvos(9.0));

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterReset
    @abstract   Reset an AudioConverter

    @param      inAudioConverter
                    The AudioConverter to reset.
    @result     An OSStatus result code.
    
    @discussion
                Should be called whenever there is a discontinuity in the source audio stream
                being provided to the converter. This will flush any internal buffers in the
                converter.
*/

extern OSStatus
AudioConverterReset(    AudioConverterRef   inAudioConverter)                   API_AVAILABLE(macos(10.1), ios(2.0), watchos(2.0), tvos(9.0));

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterGetPropertyInfo
    @abstract   Returns information about an AudioConverter property.

    @param      inAudioConverter
                    The AudioConverter to query.
    @param      inPropertyID
                    The property to query.
    @param      outSize
                    If non-null, on exit, the maximum size of the property value in bytes.
    @param      outWritable
                    If non-null, on exit, indicates whether the property value is writable.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioConverterGetPropertyInfo(  AudioConverterRef           inAudioConverter,
                                AudioConverterPropertyID    inPropertyID,
                                UInt32 * __nullable         outSize,
                                Boolean * __nullable        outWritable)        API_AVAILABLE(macos(10.1), ios(2.0), watchos(2.0), tvos(9.0));

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterGetProperty
    @abstract   Returns an AudioConverter property value.

    @param      inAudioConverter
                    The AudioConverter to query.
    @param      inPropertyID
                    The property to fetch.
    @param      ioPropertyDataSize
                    On entry, the size of the memory pointed to by outPropertyData. On 
                    successful exit, the size of the property value.
    @param      outPropertyData
                    On exit, the property value.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioConverterGetProperty(  AudioConverterRef           inAudioConverter,
                            AudioConverterPropertyID    inPropertyID,
                            UInt32 *                    ioPropertyDataSize,
                            void *                      outPropertyData)        API_AVAILABLE(macos(10.1), ios(2.0), watchos(2.0), tvos(9.0));

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterSetProperty
    @abstract   Sets an AudioConverter property value.

    @param      inAudioConverter
                    The AudioConverter to modify.
    @param      inPropertyID
                    The property to set.
    @param      inPropertyDataSize
                    The size in bytes of the property value.
    @param      inPropertyData
                    Points to the new property value.
    @result     An OSStatus result code.
*/
extern OSStatus
AudioConverterSetProperty(  AudioConverterRef           inAudioConverter,
                            AudioConverterPropertyID    inPropertyID,
                            UInt32                      inPropertyDataSize,
                            const void *                inPropertyData)         API_AVAILABLE(macos(10.1), ios(2.0), watchos(2.0), tvos(9.0));

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterConvertBuffer
    @abstract   Converts data from an input buffer to an output buffer.

    @param      inAudioConverter
                    The AudioConverter to use.
    @param      inInputDataSize
                    The size of the buffer inInputData.
    @param      inInputData
                    The input audio data buffer.
    @param      ioOutputDataSize
                    On entry, the size of the buffer outOutputData. On exit, the number of bytes
                    written to outOutputData.
    @param      outOutputData
                    The output data buffer.
    @result
                Produces a buffer of output data from an AudioConverter, using the supplied
                input buffer.
    @discussion
                <b>WARNING:</b> this function will fail for any conversion where there is a
                variable relationship between the input and output data buffer sizes. This
                includes sample rate conversions and most compressed formats. In these cases,
                use AudioConverterFillComplexBuffer. Generally this function is only appropriate for
                PCM-to-PCM conversions where there is no sample rate conversion.
*/
extern OSStatus
AudioConverterConvertBuffer(    AudioConverterRef               inAudioConverter,
                                UInt32                          inInputDataSize,
                                const void *                    inInputData,
                                UInt32 *                        ioOutputDataSize,
                                void *                          outOutputData)  API_AVAILABLE(macos(10.1), ios(2.0), watchos(2.0), tvos(9.0));

//-----------------------------------------------------------------------------
/*!
    @typedef    AudioConverterComplexInputDataProc
    @abstract   Callback function for supplying input data to AudioConverterFillComplexBuffer.

    @param      inAudioConverter
                    The AudioConverter requesting input.
    @param      ioNumberDataPackets
                    On entry, the minimum number of packets of input audio data the converter
                    would like in order to fulfill its current FillBuffer request. On exit, the
                    number of packets of audio data actually being provided for input, or 0 if
                    there is no more input.
    @param      ioData
                    On exit, the members of ioData should be set to point to the audio data
                    being provided for input.
    @param      outDataPacketDescription
                    If non-null, on exit, the callback is expected to fill this in with
                    an AudioStreamPacketDescription for each packet of input data being provided.
    @param      inUserData
                    The inInputDataProcUserData parameter passed to AudioConverterFillComplexBuffer().
    @result     An OSStatus result code.
    
    @discussion
                This callback function supplies input to AudioConverterFillComplexBuffer.
                
                The AudioConverter requests a minimum number of packets (*ioNumberDataPackets).
                The callback may return one or more packets. If this is less than the minimum,
                the callback will simply be called again in the near future.

                The callback manipulates the members of ioData to point to one or more buffers
                of audio data (multiple buffers are used with non-interleaved PCM data). The
                callback is responsible for not freeing or altering this buffer until it is
                called again.

                If the callback returns an error, it must return zero packets of data.
                AudioConverterFillComplexBuffer will stop producing output and return whatever
                output has already been produced to its caller, along with the error code. This
                mechanism can be used when an input proc has temporarily run out of data, but
                has not yet reached end of stream.
*/
typedef OSStatus
(*AudioConverterComplexInputDataProc)(  AudioConverterRef               inAudioConverter,
                                        UInt32 *                        ioNumberDataPackets,
                                        AudioBufferList *               ioData,
                                        AudioStreamPacketDescription * __nullable * __nullable outDataPacketDescription,
                                        void * __nullable               inUserData);

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterFillComplexBuffer
    @abstract   Converts data supplied by an input callback function, supporting non-interleaved
                and packetized formats.

    @param      inAudioConverter
                    The AudioConverter to use.
    @param      inInputDataProc
                    A callback function which supplies the input data.
    @param      inInputDataProcUserData
                    A value for the use of the callback function.
    @param      ioOutputDataPacketSize
                    On entry, the capacity of outOutputData expressed in packets in the
                    converter's output format. On exit, the number of packets of converted
                    data that were written to outOutputData.
    @param      outOutputData
                    The converted output data is written to this buffer.
    @param      outPacketDescription
                    If non-null, and the converter's output uses packet descriptions, then
                    packet descriptions are written to this array. It must point to a memory
                    block capable of holding *ioOutputDataPacketSize packet descriptions.
                    (See AudioFormat.h for ways to determine whether an audio format
                    uses packet descriptions).
    @result     An OSStatus result code.

    @discussion
                Produces a buffer list of output data from an AudioConverter. The supplied input
                callback function is called whenever necessary.
*/
extern OSStatus
AudioConverterFillComplexBuffer(    AudioConverterRef                   inAudioConverter,
                                    AudioConverterComplexInputDataProc  inInputDataProc,
                                    void * __nullable                   inInputDataProcUserData,
                                    UInt32 *                            ioOutputDataPacketSize,
                                    AudioBufferList *                   outOutputData,
                                    AudioStreamPacketDescription * __nullable outPacketDescription)
                                                                                API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));


//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterConvertComplexBuffer
    @abstract   Converts PCM data from an input buffer list to an output buffer list.

    @param      inAudioConverter
                    The AudioConverter to use.
    @param      inNumberPCMFrames
                    The number of PCM frames to convert.
    @param      inInputData
                    The source audio buffer list.
    @param      outOutputData
                    The converted output data is written to this buffer list.
    @result     An OSStatus result code.
    @discussion
                <b>WARNING:</b> this function will fail for any conversion where there is a
                variable relationship between the input and output data buffer sizes. This
                includes sample rate conversions and most compressed formats. In these cases,
                use AudioConverterFillComplexBuffer. Generally this function is only appropriate for
                PCM-to-PCM conversions where there is no sample rate conversion.
*/
extern OSStatus
AudioConverterConvertComplexBuffer( AudioConverterRef               inAudioConverter,
                                    UInt32                          inNumberPCMFrames,
                                    const AudioBufferList *         inInputData,
                                    AudioBufferList *               outOutputData)
                                                                                API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

// =================================================================================================
// DEPRECATED
// =================================================================================================

/*
	Deprecated properties:
	
    @constant   kAudioConverterPropertyMaximumInputBufferSize
                    DEPRECATED. The AudioConverter input proc may be passed any number of packets of data.
                    If fewer are packets are returned than required, then the input proc will be called again.
                    If more packets are passed than required, they will remain in the client's buffer and be 
                    consumed as needed.
    @constant   kAudioConverterSampleRateConverterAlgorithm
                    DEPRECATED: please use kAudioConverterSampleRateConverterComplexity instead
	
*/
CF_ENUM(AudioConverterPropertyID)
{
    kAudioConverterPropertyMaximumInputBufferSize       = 'xibs',
    kAudioConverterSampleRateConverterAlgorithm         = 'srci',
};

#if TARGET_OS_IPHONE
/*!
    @enum       AudioConverterPropertyID (iOS only)
    @abstract   iOS-specific properties of an AudioConverter, accessible via AudioConverterGetProperty()
                and AudioConverterSetProperty().
 
    @constant   kAudioConverterPropertyCanResumeFromInterruption
                    A read-only UInt32 signifying whether the underlying codec supports resumption following
                    an interruption. If the property is unimplemented (i.e. AudioConverterGetProperty
                    returns an error), then the codec is not a hardware codec. If the property's value
                    is 1, then the codec can resume work following an interruption. If the property's
                    value is 0, then interruptions destroy the codec's state.
                    
                    DEPRECATED: Hardware codecs are no longer supported.
*/
CF_ENUM(AudioConverterPropertyID)
{
    kAudioConverterPropertyCanResumeFromInterruption    = 'crfi'
};
#endif

//-----------------------------------------------------------------------------
/*!
    @typedef    AudioConverterInputDataProc
    @abstract   Callback function for supplying input data to AudioConverterFillBuffer.

    @param      inAudioConverter
                    The AudioConverter requesting input.
    @param      ioDataSize
                    On entry, the minimum number of bytes of audio data the converter
                    would like in order to fulfill its current FillBuffer request.
                    On exit, the number of bytes of audio data actually being provided
                    for input, or 0 if there is no more input.
    @param      outData
                    On exit, *outData should point to the audio data being provided
                    for input.
    @param      inUserData
                    The inInputDataProcUserData parameter passed to AudioConverterFillBuffer().
    @result     An OSStatus result code.
    
    @discussion
                <b>NOTE:</b> This API is now deprecated, 
                use AudioConverterFillComplexBuffer instead.

                This callback function supplies input to AudioConverterFillBuffer.
                
                The AudioConverter requests a minimum amount of data (*ioDataSize). The callback
                may return any amount of data. If it is less than than the minimum, the callback
                will simply be called again in the near future.

                The callback supplies a pointer to a buffer of audio data. The callback is
                responsible for not freeing or altering this buffer until it is called again.
                
                If the callback returns an error, it must return zero bytes of data.
                AudioConverterFillBuffer will stop producing output and return whatever output
                has already been produced to its caller, along with the error code. This
                mechanism can be used when an input proc has temporarily run out of data, but
                has not yet reached end of stream.
*/
typedef OSStatus
(*AudioConverterInputDataProc)( AudioConverterRef           inAudioConverter,
                                UInt32 *                    ioDataSize,
                                void * __nonnull * __nonnull outData,
                                void * __nullable           inUserData);

//-----------------------------------------------------------------------------
/*!
    @function   AudioConverterFillBuffer
    @abstract   Converts data supplied by an input callback function.

    @param      inAudioConverter
                    The AudioConverter to use.
    @param      inInputDataProc
                    A callback function which supplies the input data.
    @param      inInputDataProcUserData
                    A value for the use of the callback function.
    @param      ioOutputDataSize
                    On entry, the size of the buffer pointed to by outOutputData.
                    On exit, the number of bytes written to outOutputData
    @param      outOutputData
                    The buffer into which the converted data is written.
    @result     An OSStatus result code.
    
    @discussion
                <b>NOTE:</b> This API is now deprecated, 
                use AudioConverterFillComplexBuffer instead.

                Produces a buffer of output data from an AudioConverter. The supplied input
                callback function is called whenever necessary.             
*/
#if !TARGET_OS_IPHONE
extern OSStatus
AudioConverterFillBuffer(   AudioConverterRef               inAudioConverter,
                            AudioConverterInputDataProc     inInputDataProc,
                            void * __nullable               inInputDataProcUserData,
                            UInt32 *                        ioOutputDataSize,
                            void *                          outOutputData)
                            
                                API_DEPRECATED("no longer supported", macos(10.1, 10.5)) API_UNAVAILABLE(ios, watchos, tvos);
#endif // !TARGET_OS_IPHONE

#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioConverter_h
#else
#include <AudioToolboxCore/AudioConverter.h>
#endif
