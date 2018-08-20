// ==========  AudioUnit.framework/Headers/AudioComponent.h
/*!
	@file		AudioComponent.h
 	@framework	AudioUnit.framework
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


#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
    #include <CoreAudio/CoreAudioTypes.h>
    #include <CoreFoundation/CoreFoundation.h>
#else
    #include <CoreAudioTypes.h>
    #include <CoreFoundation.h>
#endif

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
    @field          componentType
                        A unique 4-byte code identifying the generic type of an audio component
    @field          componentSubType
                        the particular flavor of this instance
    @field          componentManufacturer
                        vendor identification
    @field          componentFlags
                        must be set to zero unless a known specific value is requested
    @field          componentFlagsMask
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
#if TARGET_OS_IPHONE
    typedef struct OpaqueAudioComponentInstance *   AudioComponentInstance;
#else
    typedef struct ComponentInstanceRecord *        AudioComponentInstance;
#endif

/*!
    @typedef        AudioComponentMethod
    @abstract       The broad prototype for an audio plugin method
    @discussion     Every audio plugin will implement a collection of methods that match a particular
					selector. For example, the AudioUnitInitialize API call is implemented by a
					plugin implementing the kAudioUnitInitializeSelect selector. Any function implementing
					an audio plugin selector conforms to the basic pattern where the first argument
					is a pointer to the plugin instance structure, has 0 or more specific arguments,  
					and returns an OSStatus.
*/
typedef OSStatus (*AudioComponentMethod)(void *self,...);

/*!
    @struct         AudioComponentPlugInInterface
    @discussion     A structure used to represent an audio plugin's routines 
    @field          Open
                        the function used to open (or create) an audio plugin instance
    @field          Close
                        the function used to close (or dispose) an audio plugin instance
    @field          Lookup
                        this is used to return a function pointer for a given selector, 
						or NULL if that selector is not implemented
    @field          reserved
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
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

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
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

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
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

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
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

/*!
    @function       AudioComponentGetVersion
    @abstract       Retrieve an audio component's version.
    @discussion
    @param          inComponent
                        the audio component (must not be NULL)
    @param          outVersion
                        the audio component's version in the form of 0xMMMMmmDD (Major, Minor, Dot)
    @result         an OSStatus result code.
*/
extern OSStatus 
AudioComponentGetVersion(   AudioComponent                      inComponent, 
                            UInt32 *                            outVersion)
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

#if __OBJC__ && !TARGET_OS_IPHONE
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
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_NA);
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
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);
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
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

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
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

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
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

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
                                                                            __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_3_0);

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
                                                    __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_5_0);

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
                                                    __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_NA);

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
		The keys for this dictionary is the platform (e.g. "i386") that generated the result.
*/
#define kAudioComponentConfigurationInfo_ValidationResult	"ValidationResult"
	
/*!
	 @function		AudioComponentValidate
	 @abstract		Tests a specified AudioComponent for API and behavioural conformance
	 @discussion	Currently, only AudioUnits can can be validated.
	 @param			inComponent
						The AudioComponent to validate.
	 @param			inValidationParameters
						A CFDictionaryRef that contains parameters for the validation operation.
						Passing NULL for this argument tells the system to use the default
						parameters.
	 @param			outValidationResult
						On exit, this is an AudioComponentValidationResult.
	 @result		an OSStatus result code.
*/
extern OSStatus
AudioComponentValidate( AudioComponent					inComponent,
						CFDictionaryRef __nullable		inValidationParameters,
						AudioComponentValidationResult *outValidationResult)
													__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_NA);
	
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
// ==========  AudioUnit.framework/Headers/MusicDevice.h
/*!
	@file		MusicDevice.h
	@framework	AudioUnit.framework
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

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreAudio/CoreAudioTypes.h>
	#include <AudioUnit/AUComponent.h>
#else
	#include <CoreAudioTypes.h>
	#include <AUComponent.h>
#endif

CF_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

#if !__LP64__
	#if PRAGMA_STRUCT_ALIGN
		#pragma options align=mac68k
	#elif PRAGMA_STRUCT_PACKPUSH
		#pragma pack(push, 2)
	#elif PRAGMA_STRUCT_PACK
		#pragma pack(2)
	#endif
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
	
	@param			argCount
			Should be set to 2
	@param			mPitch
			The pitch of the new note, typically specified using a MIDI note number (and a fractional pitch) within the 
					range of 0 < 128. So 60 is middle C, 60.5 is middle C + 50 cents.
	@param			mVelocity
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
	
	@param			mID
			The parameter ID
	@param			mValue
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
	
	@param			argCount
			The number of controls + 2 (for mPitch and mVelocity)
	@param			mPitch
			The pitch of the new note, typically specified using a MIDI note number (and a fractional pitch) within the 
				range of 0 < 128. So 60 is middle C, 60.5 is middle C + 50 cents.
	@param			mVelocity
			The velocity of the new note - this can be a fractional value - specified as MIDI (within the range of 0 < 128)
	@param			mControls
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
						UInt32					inOffsetSampleFrame)				__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

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
						UInt32					inLength)							__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);


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
						const MusicDeviceNoteParams *	 	inParams)				__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);

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
						UInt32					inOffsetSampleFrame)				__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_5_0);


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
	@param			inStatus
	@param			inData1
	@param			inData2
	@param			inOffsetSampleFrame

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
	@param			inData
	@param			inLength

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
	@param			inInstrument
	@param			inGroupID
	@param			outNoteInstanceID
	@param			inOffsetSampleFrame
	@param			inParams
	
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
	@param			inGroupID
	@param			inNoteInstanceID
	@param			inOffsetSampleFrame
	
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
										__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);


extern OSStatus
MusicDeviceReleaseInstrument(	MusicDeviceComponent		inUnit,
								MusicDeviceInstrumentID		inInstrument)		
										__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);

	
#if !__LP64__
	#if PRAGMA_STRUCT_ALIGN
		#pragma options align=reset
	#elif PRAGMA_STRUCT_PACKPUSH
		#pragma pack(pop)
	#elif PRAGMA_STRUCT_PACK
		#pragma pack()
	#endif
#endif

#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif /* AudioUnit_MusicDevice_h */

// ==========  AudioUnit.framework/Headers/AUAudioUnitImplementation.h
/*!
	@file		AUAudioUnitImplementation.h
 	@framework	AudioUnit.framework
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
:	Optional. If specified, the identifier of a bundle in the .appex
	or its enclosing app container in which the factory function and/or
	principal class are implemented.

AudioComponents
:	Registration info for each audio component type/subtype/manufacturer
	implemented in the extension. factoryFunction is only necessary
	if the AU is implemented using AUAudioUnitV2Bridge.
	See AudioComponent.h.

*/

#if __OBJC2__

#import <AudioUnit/AUAudioUnit.h>

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
NS_CLASS_AVAILABLE(10_11, 9_0)
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
// ==========  AudioUnit.framework/Headers/AudioOutputUnit.h
/*!
	@file		AudioOutputUnit.h
 	@framework	AudioUnit.framework
 	@copyright	(c) 2000-2015 Apple, Inc. All rights reserved.
	@brief		Additional Audio Unit API for audio input/output units.
*/

#ifndef AudioUnit_AudioOutputUnit_h
#define AudioUnit_AudioOutputUnit_h

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AUComponent.h>
#else
	#include <AUComponent.h>
#endif

CF_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

#if !__LP64__
	#if PRAGMA_STRUCT_ALIGN
		#pragma options align=mac68k
	#elif PRAGMA_STRUCT_PACKPUSH
		#pragma pack(push, 2)
	#elif PRAGMA_STRUCT_PACK
		#pragma pack(2)
	#endif
#endif

//-----------------------------------------------------------------------------
//	Start/stop methods for output units
//-----------------------------------------------------------------------------
extern OSStatus
AudioOutputUnitStart(	AudioUnit	ci)											__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

extern OSStatus
AudioOutputUnitStop(	AudioUnit	ci)											__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

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


#if !__LP64__
	#if PRAGMA_STRUCT_ALIGN
		#pragma options align=reset
	#elif PRAGMA_STRUCT_PACKPUSH
		#pragma pack(pop)
	#elif PRAGMA_STRUCT_PACK
		#pragma pack()
	#endif
#endif

#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif /* AudioUnit_AudioOutputUnit_h */
// ==========  AudioUnit.framework/Headers/AUComponent.h
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
		- Dispose audio unit (AudioComponentInstanceDispose)

	Audio units can be used programmatically (for instance, mixers can be used to render audio for a
	game, a generator to play audio files, etc), or they can be hosted in Digital Audio Workstation
	(DAW) applications such as Logic, Garage Band, etc. In the DAW case, it is common for an audio
	unit to provide a custom view to allow the user to interact with what can be complex DSP
	operations that the audio unit performs. The view is retrieved from an audio unit through
	AudioUnitGetProperty and then the host instantiates it (see <AudioUnit/AUCocoaUIView.h>)
*/
#ifndef AudioUnit_AUComponent_h
#define AudioUnit_AUComponent_h

//================================================================================================
#pragma mark Overview



#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AudioComponent.h>
	#include <CoreAudio/CoreAudioTypes.h>
#else
	#include <AudioComponent.h>
	#include <CoreAudioTypes.h>
#endif

CF_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

#if !__LP64__
	#if PRAGMA_STRUCT_ALIGN
		#pragma options align=mac68k
	#elif PRAGMA_STRUCT_PACKPUSH
		#pragma pack(push, 2)
	#elif PRAGMA_STRUCT_PACK
		#pragma pack(2)
	#endif
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
					through parameters or MIDI control messages. See <AudioUnit/MusicDevice.h>
										
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

#if TARGET_OS_IPHONE
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
					see <AudioUnit/AudioOutputUnit.h>

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
						- desktop only
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
#else
/*!
	@enum			Apple converter audio unit sub types (iOS only)
	@constant		kAudioUnitSubType_AUiPodTime
					An audio unit that provides simple (and limited) control over playback rate
					and time.
*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_AUiPodTime			= 'iptm'
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
	kAudioUnitSubType_NBandEQ				= 'nbeq'
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
#else
/*!
	@enum			Apple effect audio unit sub types (iOS only)
	@constant		kAudioUnitSubType_Reverb2
					A reverb for iOS
	@constant		kAudioUnitSubType_AUiPodEQ
					A simple graphic EQ with common presets
*/
CF_ENUM(UInt32) {
	kAudioUnitSubType_Reverb2				= 'rvb2',
	kAudioUnitSubType_AUiPodEQ				= 'ipeq'
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
	kAudioUnitSubType_3DMixer __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_3, __MAC_10_10, __IPHONE_NA, __IPHONE_NA)
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
					This flag can be set in a render input callback (or in the audio unit's render 
					operation itself) and is used to indicate that the render buffer contains only 
					silence. It can then be used by the caller as a hint to whether the buffer 
					needs to be processed or not.
					
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
    @constant   kAudioComponentErr_InstanceInvalidated
        the component instance's implementation is not available, most likely because the process
        that published it is no longer running
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
    kAudioComponentErr_InstanceInvalidated  = -66749,
};


#if TARGET_OS_IPHONE
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

	@field			scope	
					The scope for the parameter
	@field			element
					The element for the parameter
	@field			parameter
					The parameterID for the parameter
	
	@field			eventType
					The event type. This field further defines how the union described by 
					eventValues is to be interpreted.
	
	@field			eventValues
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
					completeness

	@field			mAudioUnit
					The audio unit instance to which the specified parameter applies.
	@field			mParameterID
					The parameterID for the parameter
	@field			mScope	
					The scope for the parameter
	@field			mElement
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
					completeness

	@field			mAudioUnit
					The audio unit instance which the specified property applies too
	@field			mPropertyID
					The propertyID for the property
	@field			mScope	
					The scope for the property
	@field			mElement
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
												__OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_7_0);

/*!
	@constant kAudioComponentInstanceInvalidationNotification
	@abstract Notification generated when an audio unit extension process exits abnormally.
	@discussion
		Register for this notification name with [NSNotificationCenter defaultCenter] or
		CFNotificationCenterGetLocalCenter(). The "object" refers to an AUAudioUnit instance to
		be observed, or can be nil to observe all instances. The notification's userInfo
		dictionary contains a key, "audioUnit", an NSValue whose pointerValue is the
		AudioUnit/AudioComponentInstance which is wrapping the AUAudioUnit communicating with the
		extension process. (This may be null if there is no such component instance.) For example:

	[[NSNotificationCenter defaultCenter] addObserverForName:(NSString *)kAudioComponentInstanceInvalidationNotification object:nil queue:nil usingBlock:^(NSNotification *note) {
		AUAudioUnit *auAudioUnit = (AUAudioUnit *)note.object;
		NSValue *val = note.userInfo[@"audioUnit"];
		AudioUnit audioUnit = (AudioUnit)val.pointerValue;
		NSLog(@"Received kAudioComponentInstanceInvalidationNotification: auAudioUnit %@, audioUnit %p", auAudioUnit, audioUnit);
	}];
*/
extern const CFStringRef kAudioComponentInstanceInvalidationNotification
												__OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);


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
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

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
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);


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
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

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
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

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
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

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
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

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
												__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

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
												__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

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
												__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

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
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

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
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

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
												__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

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
												__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

extern OSStatus
AudioUnitProcess (					AudioUnit						inUnit, 
									AudioUnitRenderActionFlags * __nullable	ioActionFlags, 
									const AudioTimeStamp *			inTimeStamp, 
									UInt32							inNumberFrames, 
									AudioBufferList *				ioData)
												__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_6_0);

extern OSStatus
AudioUnitProcessMultiple(			AudioUnit						inUnit, 
									AudioUnitRenderActionFlags * __nullable ioActionFlags, 
									const AudioTimeStamp *			inTimeStamp, 
									UInt32							inNumberFrames,
									UInt32							inNumberInputBufferLists,
									const AudioBufferList * __nonnull * __nonnull inInputBufferLists,
									UInt32							inNumberOutputBufferLists,
									AudioBufferList * __nonnull * __nonnull ioOutputBufferLists)
												__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_6_0);
	
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
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

#if TARGET_OS_IPHONE
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
                                                __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_7_0);


#if defined(__OBJC__)
@class UIImage;

extern UIImage * __nullable
AudioOutputUnitGetHostIcon(AudioUnit au, float desiredPointSize)
                                                __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_7_0);
extern UIImage * __nullable
AudioComponentGetIcon(AudioComponent comp, float desiredPointSize)
                                                __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_7_0);

#endif // __OBJC__


/*!
    @function       AudioComponentGetLastActiveTime
    @abstract       Fetches the time at which the application publishing the component was last active.
	@discussion
		Inter-app audio hosts can use this to sort the list of available nodes by how recently
		the user interacted with them.
	
    @param          inComponent
                        The AudioComponent being queried.
    @result         The CFAbsoluteTime at which the node was last active (0 if never).
*/
extern CFAbsoluteTime
AudioComponentGetLastActiveTime(AudioComponent comp)
                                                __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_7_0);
#endif // TARGET_OS_IPHONE




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
	@param			inID
	@param			inScope
	@param			inElement
	@param			outValue
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
	@param			inID
	@param			inScope
	@param			inElement
	@param			inValue
	@param			inBufferOffsetInFrames
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
	@param			ioActionFlags
	@param			inTimeStamp
	@param			inOutputBusNumber
	@param			inNumberFrames
	@param			ioData
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

#if !__LP64__ && !TARGET_OS_IPHONE
// this call is deprecated and replaced by AudioUnitRemovePropertyListenerWithUserData
// this allows apps to use the same function pointer more than once
// you provide the same function ptr and user data as provided when you add a property listener
extern OSStatus
AudioUnitRemovePropertyListener(	AudioUnit						inUnit,
									AudioUnitPropertyID				inID,
									AudioUnitPropertyListenerProc	inProc)			
				__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);
#endif

#if !__LP64__
	#if PRAGMA_STRUCT_ALIGN
		#pragma options align=reset
	#elif PRAGMA_STRUCT_PACKPUSH
		#pragma pack(pop)
	#elif PRAGMA_STRUCT_PACK
		#pragma pack()
	#endif
#endif

#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif /* AudioUnit_AUComponent_h */
// ==========  AudioUnit.framework/Headers/AUAudioUnit.h
/*!
	@file		AUAudioUnit.h
 	@framework	AudioUnit.framework
 	@copyright	(c) 2015 Apple, Inc. All rights reserved.

	@brief		Objective-C interfaces for hosting and implementing Audio Units.
*/

#if __OBJC2__

#import <AudioUnit/AUParameters.h>
#import <Foundation/NSExtensionRequestHandling.h>

#if !TARGET_OS_IPHONE
// for AudioObjectID for setDeviceID:error:
#import <CoreAudio/AudioHardwareBase.h>
#endif

NS_ASSUME_NONNULL_BEGIN

// forward declarations
@class AVAudioFormat;
@class AUAudioUnitBusArray;
@class AUAudioUnitBus;
@class AUAudioUnitPreset;
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
NS_CLASS_AVAILABLE(10_11, 9_0)
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
		See the discussion of AudioComponentInstantiationOptions in AudioUnit/AudioComponent.h.
	@param completionHandler
		Called in a thread/dispatch queue context internal to the implementation. The client should
		retain the supplied AUAudioUnit.
	@discussion
		Certain types of AUAudioUnits must be instantiated asynchronously -- see 
		the discussion of kAudioComponentFlag_RequiresAsyncInstantiation in
		AudioUnit/AudioComponent.h.

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
		values are invalidated (e.g. selection of a preset or setting fullState).
 
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

// ------------------------
// These properties and methods are generally optional.

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
		parameters provided by the developer. This property returns all of the available presets.
		
		Bridged to the v2 property kAudioUnitProperty_FactoryPresets.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSArray<AUAudioUnitPreset *> *factoryPresets;

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
*/
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL canProcessInPlace;

/*!	@property	renderingOffline
	@brief		Communicates to an audio unit that it is rendering offline.
	@discussion
		A host should use this property when using an audio unit in a context where there are 
		no realtime deadlines. An audio unit may respond by using a more expensive signal
		processing algorithm, or allowing itself to block at render time if data being generated on
		secondary work threads is not ready in time. (Normally, in a realtime thread, this
		data would have to be dropped).

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

@end

// =================================================================================================

/*!	@typedef	AUInputHandler
	@brief		Block to notify the client of an I/O unit that input is available.
	@param actionFlags
		Pointer to action flags.
	@param timestamp
		The HAL time at which the input data will be rendered. If there is a sample rate conversion
		or time compression/expansion downstream, the sample time will not be valid.
	@param frameCount
		The number of sample frames of input available.
	@param inputBusNumber
		The index of the input bus from which input is available.
	@discussion	The input data is obtained by calling the render block of the audio unit.
				The AUAudioUnit is not provided since it is not safe to message an Objective C object in a real time context.
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
@property (nonatomic, readonly) AudioObjectID deviceID;

/*!	@method		setDeviceID:error:
	@brief		Set the I/O hardware device.
	@param deviceID
		The device to select.
	@param outError
		Returned in the event of failure.
*/
- (BOOL)setDeviceID:(AudioObjectID)deviceID error:(NSError **)outError;
#endif

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
NS_CLASS_AVAILABLE(10_11, 9_0)
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
NS_CLASS_AVAILABLE(10_11, 9_0)
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
NS_CLASS_AVAILABLE(10_11, 9_0)
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
// ==========  AudioUnit.framework/Headers/AudioUnitProperties.h
/*!
	@file		AudioUnitProperties.h
 	@framework	AudioUnit.framework
 	@copyright	(c) 2000-2015 Apple, Inc. All rights reserved.
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

#ifndef AudioUnit_AudioUnitProperties_h
#define AudioUnit_AudioUnitProperties_h

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AUComponent.h>
	#include <CoreAudio/CoreAudioTypes.h>
	#include <CoreFoundation/CoreFoundation.h>
#else
	#include <AUComponent.h>
	#include <CoreAudioTypes.h>
	#include <CoreFoundation.h>
#endif

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
						Value Type:		AudioUnitParameterInfo
						Access:
						
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

						The host will also need to determine how many MIDI output streams the audio unit can generate 
						(and the name for each of these outputs). Each MIDI output is a complete MIDI data stream, 
						such as embodied by a MIDIEndpointRef in CoreMIDI.
						
						To do, the host uses this property and retrieves an array of CFStringRefs:
							- the size of the array is the number of MIDI Outputs the audio unit supports
							- each item in the array is the name for that output at that index
						
						The host should release the array when it is finished with it.
						
						Once the host has determined the audio unit supports this feature, it then instantiates a callback 
						with the unit that the unit will call with MIDI data (see kAudioUnitProperty_MIDIOutputCallback).
	
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

#if !TARGET_OS_IPHONE
	kAudioUnitProperty_FastDispatch					= 5,
	kAudioUnitProperty_SetExternalBuffer			= 15,
	kAudioUnitProperty_GetUIComponentList			= 18,
	kAudioUnitProperty_CocoaUI						= 31,
	kAudioUnitProperty_IconLocation					= 39,
	kAudioUnitProperty_AUHostIdentifier				= 46,
	kAudioUnitProperty_MIDIOutputCallbackInfo		= 47,
	kAudioUnitProperty_MIDIOutputCallback			= 48,
#endif
};

#if TARGET_OS_IPHONE
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
#endif



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
    @field          sourceAudioUnit
						The audio unit that is the source for the connection
    @field          sourceOutputNumber
						The source audio unit's output element to be used in the connection
    @field          destInputNumber
						The destination audio unit's input element to be used in the connection						
*/
typedef struct AudioUnitConnection {
	AudioUnit	sourceAudioUnit;
	UInt32		sourceOutputNumber;
	UInt32		destInputNumber;
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
	AURenderCallback			inputProc;
	void * __nullable			inputProcRefCon;
} AURenderCallbackStruct;

/*!
	@struct			AUPreset
	@abstract		Used to publish and set factory presets on an audio unit
	@field			presetNumber
						If < 0, then preset is a user preset
						If >= 0, then this field is used to select the factory preset
	@field			presetName
						If a factory preset, the name of the specified factory preset
*/
typedef struct AUPreset {
	SInt32		presetNumber;
	CFStringRef	presetName;
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
	@field			mCocoaAUViewBundleLocation
						Contains the location of the bundle which the host app can then use to locate the bundle
	@field			mCocoaAUViewClass
						Contains the names of the classes that implements the required protocol (AUCocoaUIBase). This class is a view factory that creates the NSView object that is the AudioUnit view.
*/
typedef struct AudioUnitCocoaViewInfo {
	CFURLRef	mCocoaAUViewBundleLocation;
	CFStringRef	mCocoaAUViewClass[1];
} AudioUnitCocoaViewInfo;

/*!
	@struct			AUHostVersionIdentifier
	@abstract		Used to describe the name and version of the audio unit's host
*/
typedef struct AUHostVersionIdentifier {
	CFStringRef 		hostName;	
	UInt32				hostVersion;
} AUHostVersionIdentifier;

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
#endif //!TARGET_OS_IPHONE

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
	@field			updatesPerSecond
						This is the number of times per second that it is suggested that the host get the value of this parameter.
	@field			historyDurationInSeconds
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
	@constant		kAudioUnitParameterFlag_NonRealTime
	@constant		kAudioUnitParameterFlag_CanRamp
	@constant		kAudioUnitParameterFlag_ExpertMode
	@constant		kAudioUnitParameterFlag_HasCFNameString
	@constant		kAudioUnitParameterFlag_IsGlobalMeta
	@constant		kAudioUnitParameterFlag_IsElementMeta
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
	@field			name
						UNUSED - set to zero - UTF8 encoded C string (originally). 
	@field			unitName
						only valid if kAudioUnitParameterUnit_CustomUnit is set. If kAudioUnitParameterUnit_CustomUnit
						is set, this field must contain a valid CFString.
	@field			clumpID
						only valid if kAudioUnitParameterFlag_HasClump
	@field			cfNameString
						only valid if kAudioUnitParameterFlag_HasCFNameString
	@field			unit				
						if the "unit" field contains a value not in the enum above, then assume 
						kAudioUnitParameterUnit_Generic
	@field			minValue
	@field			maxValue
	@field			defaultValue
	@field			flags
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


#if TARGET_OS_IPHONE
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
#endif

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
} __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_11, __IPHONE_NA, __IPHONE_NA);

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
} AUDistanceAttenuationData __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_5,__MAC_10_11, __IPHONE_NA, __IPHONE_NA);


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
	@discussion

	@field			format
	@discussion			One of the OtherPluginFormat values
						
	@field			plugin
	@discussion			struct AudioClassDescription {
							OSType mType;
							OSType mSubType;
							OSType mManufacturer;
						};
						is defined in <CoreAudio/CoreAudioTypes.h>

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
						Value Type:		Array of UInt32
						Access:			Read / Write

						This will also work with AUConverter. This property is used to map input channels from an input (source) to a destination.
						The number of channels represented in the channel map is the number of channels of the destination. The channel map entries
						contain a channel number of the source that should be mapped to that destination channel. If -1 is specified, than that 
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
							Property value is 1 if input or output is enabled on the specified element.

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

#if TARGET_OS_IPHONE
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
#endif // TARGET_OS_IPHONE

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
} __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA, __MAC_NA, __IPHONE_3_0, __IPHONE_7_0);
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

*/
CF_ENUM(AudioUnitPropertyID) {
	// General mixers
	kAudioUnitProperty_MeteringMode					= 3007,
	
	// Matrix Mixer
	kAudioUnitProperty_MatrixLevels					= 3006,
	kAudioUnitProperty_MatrixDimensions				= 3009,
	kAudioUnitProperty_MeterClipping				= 3011
};

/*!
	@struct			AudioUnitMeterClipping
	
	@field			peakValueSinceLastCall; 
	@discussion			The maximum value seen on the channel since the last time the property was retrieved.
	@field			sawInfinity;
	@discussion			TRUE if there was an infinite value on this channel.
	@field			sawNotANumber
	@discussion			TRUE if there was a floating point Not-A-Number value on this channel.
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
	@discussion			Scope:			Global
						Value Type:		UInt32
						Access:			Read / Write
						
	@constant		kAudioUnitProperty_UsesInternalReverb
	@discussion			Scope:			Global
						Value Type:		UInt32
						Access:			Read / Write
						
	@constant		kAudioUnitProperty_SpatializationAlgorithm
	@discussion			Scope:			Input
						Value Type:		UInt32
						Access:			Read / Write
						
						Used to set the spatialisation algorithm used by an input of AUSpatialMixer. See kSpatializationAlgorithm_
						
	@constant		kAudioUnitProperty_SpatialMixerRenderingFlags
	@discussion			Scope:			Input
						Value Type:		UInt32
						Access:			Read / Write

						Used to enable various rendering operations on a given input for the 3DMixer. See k3DMixerRenderingFlags_
						
	@constant		kAudioUnitProperty_SpatialMixerAttenuationCurve
	@discussion			Scope:			Input
						Value Type:		UInt32
						Access:			Read / Write

	@constant		kAudioUnitProperty_SpatialMixerDistanceParams
	@discussion			Scope:			Input
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
	kSpatializationAlgorithm_StereoPassThrough		= 5
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
    @abstract           Set if the unit is done with this slice
    @constant       kScheduledAudioSliceFlag_BeganToRender
    @abstract           Set if any portion of the buffer has been played
    @constant       kScheduledAudioSliceFlag_BeganToRenderLate
    @abstract           Set if any portion of the buffer was not played because it was scheduled late
    @constant       kScheduledAudioSliceFlag_Loop
    @abstract           specifies that the buffer should loop indefinitely
    @constant       kScheduledAudioSliceFlag_Interrupt
    @abstract           specifies that the buffer should interrupt any previously scheduled buffer
                        (by default, buffers following a playing buffer are not played until the
                        playing buffer has completed).
    @constant       kScheduledAudioSliceFlag_InterruptAtLoop
    @abstract           specifies that the buffer should interrupt any previously scheduled buffer,
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
	@field				mTimeStamp
	@field				mCompletionProc
							May be null
	@field				mCompletionProcUserData
	@field				mFlags
	@field				mReserved
							Must be 0
	@field				mReserved2
							For internal use
	@field				mNumberFrames
							Must be consistent with byte count of mBufferList
	@field				mBufferList
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
	@field			mTimeStamp
	@field			mCompletionProc
						may be NULL
	@field			mCompletionProcUserData
	@field			mAudioFile
						must be a valid and open AudioFileID
						defined in AudioToolbox/AudioFile.h: typedef	struct OpaqueAudioFileID	*AudioFileID;
	@field			mLoopCount
						0 = don't loop
	@field			mStartFrame
						offset into file
	@field			mFramesToPlay
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

	@field			fileURL
						The URL of the path to the bank or instrument file.   Caller is responsible for releasing the
 						provided CFURLRef.
	@field			instrumentType
						The type of instrument being loaded or created.  For example, use kInstrumentType_DLSPreset to load an
 						instrument from a DLS bank file.
	@field			bankMSB
						For the preset instruments, the most significant byte value for a particular bank variation within that
 						file.  Range is 0 to 127.  Use kAUSampler_DefaultMelodicBankMSB by default.
	@field			bankLSB
						For the preset instruments, the least significant byte value for a particular bank variation within that
 						file.  Range is 0 to 127.  Use kAUSampler_DefaultBankLSB by default.
	@field			presetID
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

#endif // AudioUnit_AudioUnitProperties_h
// ==========  AudioUnit.framework/Headers/AudioUnit.h
/*!
	@file		AudioUnit.h
 	@framework	AudioUnit.framework
 	@copyright	(c) 2002-2015 Apple, Inc. All rights reserved.

	@brief		Umbrella header for AudioUnit framework.
*/

#ifndef _AudioUnit_AudioUnit_h
#define _AudioUnit_AudioUnit_h

#include <TargetConditionals.h>
#define AUDIO_UNIT_VERSION 1070

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AudioComponent.h>
	#include <AudioUnit/AUComponent.h>
	#include <AudioUnit/AudioOutputUnit.h>
	#include <AudioUnit/AudioUnitProperties.h>
	#include <AudioUnit/AudioUnitParameters.h>
	#include <AudioUnit/MusicDevice.h>

	#if __OBJC2__
		#import <AudioUnit/AUAudioUnit.h>
		#import <AudioUnit/AUAudioUnitImplementation.h>
		#import <AudioUnit/AUParameters.h>
	#endif

	#if !TARGET_OS_IPHONE	
		#include <AudioUnit/AudioCodec.h>
		#include <AudioUnit/AUCocoaUIView.h>
	#endif

#else
	#include <AudioComponent.h>
	#include <AUComponent.h>
	#include <AudioOutputUnit.h>
	#include <AudioUnitProperties.h>
	#include <AudioUnitParameters.h>
	#include <AudioCodec.h>
	#include <MusicDevice.h>
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

#endif /* _AudioUnit_AudioUnit_h */

// ==========  AudioUnit.framework/Headers/AUParameters.h
/*!
	@file		AUParameters.h
 	@framework	AudioUnit.framework
 	@copyright	(c) 2015 Apple, Inc. All rights reserved.

	@brief		Objects representing an AUAudioUnit's tree of parameters.
*/

#if __OBJC2__

#import <AudioUnit/AUComponent.h>
#import <AudioUnit/AudioUnitProperties.h>
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

/*!	@typedef	AURecordedParameterEvent
	@brief		An event recording the changing of a parameter at a particular host time.
*/
typedef struct AURecordedParameterEvent {
	uint64_t hostTime;				///< The host time at which the event occurred.
	AUParameterAddress address;		///< The address of the parameter whose value changed.
	AUValue value;					///< The value of the parameter at that time.
} AURecordedParameterEvent;

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

/*!	@typedef	AUParameterObserverToken
	@brief		A token representing an installed AUParameterObserver or AUParameterRecordingObserver.
*/
typedef void *AUParameterObserverToken;

// =================================================================================================

/*!	@class		AUParameterNode
	@brief		A node in an audio unit's tree of parameters.
	@discussion
		Nodes are instances of either AUParameterGroup or AUParameter.
*/
NS_CLASS_AVAILABLE(10_11, 9_0)
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
		An audio unit host can use an AUParameterRecordingObserver to capture a series of changes
		to a parameter value, including the timing of the events, as generated by a UI gesture in a
		view, for example.
		
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
- (AUParameterObserverToken)tokenByAddingParameterRecordingObserver:(AUParameterRecordingObserver)observer;

/*!	@method removeParameterObserver:
	@brief	Remove an observer created with tokenByAddingParameterObserver or tokenByAddingParameterRecordingObserver:
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
NS_CLASS_AVAILABLE(10_11, 9_0)
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
		issue a KVO notification on the audio unit's parameterTree property.
*/
NS_CLASS_AVAILABLE(10_11, 9_0)
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
NS_CLASS_AVAILABLE(10_11, 9_0)
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

/// Set the parameter's value, preserving the host time of the gesture that initiated the change.
- (void)setValue:(AUValue)value originator:(AUParameterObserverToken __nullable)originator atHostTime:(uint64_t)hostTime;

/// Get a textual representation of a value for the parameter. Use value==nil to use the current value.
- (NSString *)stringFromValue:(const AUValue *__nullable)value;

/// Convert a textual representation of a value to a numeric one.
- (AUValue)valueFromString:(NSString *)string;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
// ==========  AudioUnit.framework/Headers/AudioUnitParameters.h
/*!
	@file		AudioUnitParameters.h
 	@framework	AudioUnit.framework
 	@copyright	(c) 2000-2015 Apple, Inc. All rights reserved.
	@abstract	Constants for the parameters of Apple audio units.
*/

#ifndef AudioUnit_AudioUnitParameters_h
#define AudioUnit_AudioUnitParameters_h

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreAudio/CoreAudioTypes.h>
	#include <AudioUnit/AUComponent.h>
#else
	#include <CoreAudioTypes.h>
	#include <AUComponent.h>
#endif

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
	
    // Input, rate scaler	0.5 -> 2.0
    kSpatialMixerParam_PlaybackRate	= 4,
    
    // bus enable : 0.0 or 1.0
    kSpatialMixerParam_Enable       = 5,
    
    // Minimum input gain constraint : 0.0 -> 1.0
    kSpatialMixerParam_MinGain      = 6,
    
    // Maximum input gain constraint : 0.0 -> 1.0
    kSpatialMixerParam_MaxGain      = 7,
	
    // Input, Dry/Wet equal-power blend, %	  0.0 -> 100.0
    kSpatialMixerParam_ReverbBlend		= 8,
    
    // Global, dB,		-40.0 -> +40.0
    kSpatialMixerParam_GlobalReverbGain	= 9,
	
    // Input, Lowpass filter attenuation at 5KHz :		decibels -100.0dB -> 0.0dB
    // smaller values make both direct and reverb sound more muffled; a value of 0.0 indicates no filtering
    // Occlusion is a filter applied to the sound prior to the reverb send
    kSpatialMixerParam_OcclusionAttenuation	= 10,
	
    // Input, Lowpass filter attenuation at 5KHz :		decibels -100.0dB -> 0.0dB
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
	
#if TARGET_OS_IPHONE
		// iPhone specific 3D mixer parameters

		// bus enable : 0.0 or 1.0
    k3DMixerParam_Enable       = 5,

		// Minimum input gain constraint : 0.0 -> 1.0 (available on iphone only)
    k3DMixerParam_MinGain      = 6,

		// Maximum input gain constraint : 0.0 -> 1.0 (available on iphone only)
    k3DMixerParam_MaxGain      = 7,
	
		// Input, Dry/Wet equal-power blend, %	  0.0 -> 100.0
    k3DMixerParam_ReverbBlend		= 8,

		// Global, dB,		-40.0 -> +40.0
    k3DMixerParam_GlobalReverbGain	= 9,
	
		// Input, Lowpass filter attenuation at 5KHz :		decibels -100.0dB -> 0.0dB
		// smaller values make both direct and reverb sound more muffled; a value of 0.0 indicates no filtering
		// Occlusion is a filter applied to the sound prior to the reverb send
    k3DMixerParam_OcclusionAttenuation	= 10,
	
		// Input, Lowpass filter attenuation at 5KHz :		decibels -100.0dB -> 0.0dB
		// smaller values make direct sound more muffled; a value of 0.0 indicates no filtering
		// Obstruction is a filter applied to the "direct" part of the sound (so is post reverb send)
    k3DMixerParam_ObstructionAttenuation = 11
#else
		// Desktop specific 3D mixer parameters

		// Input, Dry/Wet equal-power blend, %	  0.0 -> 100.0
    k3DMixerParam_ReverbBlend		= 5,

		// Global, dB,		-40.0 -> +40.0
    k3DMixerParam_GlobalReverbGain	= 6,
	
		// Input, Lowpass filter attenuation at 5KHz :		decibels -100.0dB -> 0.0dB
		// smaller values make both direct and reverb sound more muffled; a value of 0.0 indicates no filtering
		// Occlusion is a filter applied to the sound prior to the reverb send
    k3DMixerParam_OcclusionAttenuation	= 7,
	
		// Input, Lowpass filter attenuation at 5KHz :		decibels -100.0dB -> 0.0dB
		// smaller values make direct sound more muffled; a value of 0.0 indicates no filtering
		// Obstruction is a filter applied to the "direct" part of the sound (so is post reverb send)
    k3DMixerParam_ObstructionAttenuation = 8,

		// Input/Output, dB, -120->20, 0
    k3DMixerParam_MinGain		= 9,
	
		// Input/Output, dB, -120->20, 0
    k3DMixerParam_MaxGain		= 10,

		// read-only
		//
		// For each of the following, use the parameter ID plus the channel number
		// to get the specific parameter ID for a given channel.
		// For example, k3DMixerParam_PostAveragePower indicates the left channel
		// while k3DMixerParam_PostAveragePower + 1 indicates the right channel.
	k3DMixerParam_PreAveragePower	= 1000,
	k3DMixerParam_PrePeakHoldLevel	= 2000,
	k3DMixerParam_PostAveragePower	= 3000,
	k3DMixerParam_PostPeakHoldLevel	= 4000
#endif
};


// Parameters for the AUMultiChannelMixer unit
// these are available for both desktop and iphone
CF_ENUM(AudioUnitParameterID) {
		// Global, Linear Gain, 0->1, 1
	kMultiChannelMixerParam_Volume 	= 0,
		// Global, Boolean, 0->1, 1
	kMultiChannelMixerParam_Enable 	= 1,
		// Global, Pan
	kMultiChannelMixerParam_Pan     = 2,			// -1 - 0 - 1, only valid when output is not mono
													// relationship to mix matrix: last one in wins

		// read-only
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
		// Global, rate, 1/32 -> 32.0, 1.0
	kNewTimePitchParam_Rate							= 0,
		// Global, Cents, -2400 -> 2400, 1.0
	kNewTimePitchParam_Pitch						= 1,
		// Global, generic, 3.0 -> 32.0, 8.0
	kNewTimePitchParam_Overlap						= 4,
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

#if TARGET_OS_IPHONE

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
#endif // TARGET_OS_IPHONE

#endif //AudioUnit_AudioUnitParameters_h
