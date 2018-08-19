// ==========  NaturalLanguage.framework/Headers/NaturalLanguage.h
/*    NaturalLanguage.h
      Copyright (c) 2017-2018, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <NaturalLanguage/NLLanguage.h>
#import <NaturalLanguage/NLLanguageRecognizer.h>
#import <NaturalLanguage/NLModel.h>
#import <NaturalLanguage/NLTagger.h>
#import <NaturalLanguage/NLTagScheme.h>
#import <NaturalLanguage/NLTokenizer.h>
// ==========  NaturalLanguage.framework/Headers/NLTokenizer.h
/*    NLTokenizer.h
      Copyright (c) 2017-2018, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <NaturalLanguage/NLLanguage.h>

NS_ASSUME_NONNULL_BEGIN

/* NLTokenizer is a class used to automatically segment natural-language text. An instance of this class is created with a specific unit and assigned a string to tokenize, and clients can then obtain ranges for tokens in that string appropriate to the given unit. Units are defined by NLTokenUnit, which specifies the size of the units in a string to which tokenization or tagging applies, whether word, sentence, paragraph, or document.
*/

typedef NS_ENUM(NSInteger, NLTokenUnit) {
    NLTokenUnitWord,         /* Token units are at word or equivalent level */
    NLTokenUnitSentence,     /* Token units are at sentence level */
    NLTokenUnitParagraph,    /* Token units are at paragraph level */
    NLTokenUnitDocument      /* Token unit is the entire string */
};

/* The tokenizer also conveys some basic information about the content of the token via NLTokenizerAttributes.
*/
typedef NS_OPTIONS(NSUInteger, NLTokenizerAttributes) {
    NLTokenizerAttributeNumeric    = 1 << 0,
    NLTokenizerAttributeSymbolic   = 1 << 1,
    NLTokenizerAttributeEmoji      = 1 << 2
} NS_SWIFT_NAME(NLTokenizer.Attributes);

NS_CLASS_AVAILABLE(10_14, 12_0)
@interface NLTokenizer : NSObject

- (instancetype)initWithUnit:(NLTokenUnit)unit NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@property (readonly, nonatomic) NLTokenUnit unit API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* An NLTokenizer instance must be assigned a string to tokenize, and clients can then obtain ranges for tokens in that string appropriate to the tokenizer's unit.
*/
@property (nullable, retain, nonatomic) NSString *string API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Clients may specify the language of the string, if it is known; otherwise it will be determined from the text.
*/
- (void)setLanguage:(NLLanguage)language API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Returns the range corresponding to the token for the tokenizer's unit that contains the given character index. The index must not extend beyond the end of the tokenizer's string, or the method will raise an exception.
*/
- (NSRange)tokenRangeAtIndex:(NSUInteger)characterIndex API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/* Returns the ranges corresponding to the tokens for the tokenizer's unit that intersect the given range.
*/
- (NSArray <NSValue *> *)tokensForRange:(NSRange)range API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/* The tokenizer will segment the string as needed into tokens for the given unit, and return those ranges via a block iterator, that iterates over all tokens intersecting a given range, supplying token ranges and flags. The range passed in must not extend beyond the end of the tokenizer's string, or the method will raise an exception. Note that a given instance of NLTokenizer should not be used from more than one thread simultaneously.
*/
- (void)enumerateTokensInRange:(NSRange)range usingBlock:(void (NS_NOESCAPE ^)(NSRange tokenRange, NLTokenizerAttributes flags, BOOL *stop))block API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
// ==========  NaturalLanguage.framework/Headers/NLLanguageRecognizer.h
/*    NLLanguageRecognizer.h
      Copyright (c) 2017-2018, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <NaturalLanguage/NLLanguage.h>

NS_ASSUME_NONNULL_BEGIN

/* NLLanguageRecognizer is a class used to automatically identify the language of text. An instance of this class is created and passed one or more pieces of text, and clients can then obtain either a single most likely language or a set of language candidates with probabilities. It is also possible to constrain the identification by specifying either a list of hints about known prior probabilities for languages, or a list of constraint languages into which the predictions are constrained to fall, or both.
*/

NS_CLASS_AVAILABLE(10_14, 12_0)
@interface NLLanguageRecognizer : NSObject

/* dominantLanguageForString: is a convenience method used to get the single most likely language for a specific piece of text, without having to create an NLLanguageRecognizer object.
*/
+ (nullable NLLanguage)dominantLanguageForString:(NSString *)string API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* To use an NLLanguageRecognizer object, clients create it and then pass in one or more pieces of text via the process method. After this, identification of the text can be obtained from the object. The object can be restored to its initial state by calling reset, so that it can then be reused for a new analysis. Note that a given instance of NLLanguageRecognizer should not be used from more than one thread simultaneously.
*/
- (instancetype)init NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
- (void)processString:(NSString *)string API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
- (void)reset API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* The identification obtained from an NLLanguageRecognizer object can be either a single most likely language, via dominantLanguage, or a set of language candidates with probabilities, via languageHypothesesWithMaximum:. The latter method returns a dictionary mapping languages to their estimated probabilities, up to a maximum number given by maxHypotheses.
*/
@property (nullable, readonly, copy, nonatomic) NLLanguage dominantLanguage API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
- (NSDictionary<NLLanguage, NSNumber *> *)languageHypothesesWithMaximum:(NSUInteger)maxHypotheses API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/* Allows clients to specify known prior probabilities for languages as hints for the language identification process. This should be a dictionary mapping languages to their prior probabilities.
*/
@property (copy, nonatomic) NSDictionary<NLLanguage, NSNumber *> *languageHints API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/*  Allows clients to constrain the space of identified languages. For example, setting Spanish, French and English as constraints would yield identification only from these three languages. */
@property (copy, nonatomic) NSArray<NLLanguage> *languageConstraints API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@end

NS_ASSUME_NONNULL_END
// ==========  NaturalLanguage.framework/Headers/NLTagScheme.h
/*    NLTagScheme.h
      Copyright (c) 2017-2018, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

/* An NLTagScheme is a type of tagging usable with NLTagger. A given tagger instance is created with an array of tag schemes, specifying which types of tagging it will provide. A specific tag scheme must be specified whenever tags are requested. Each tag scheme has its own set of tags. Clients using custom models may also define their own tag schemes and tags.
*/

typedef NSString *NLTagScheme NS_TYPED_EXTENSIBLE_ENUM;

FOUNDATION_EXPORT NLTagScheme const NLTagSchemeTokenType API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));               /* This tag scheme classifies tokens according to their broad general type:  word, punctuation, whitespace, etc. */
FOUNDATION_EXPORT NLTagScheme const NLTagSchemeLexicalClass API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));            /* This tag scheme classifies tokens according to class:  part of speech for words, type of punctuation or whitespace, etc. */
FOUNDATION_EXPORT NLTagScheme const NLTagSchemeNameType API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                /* This tag scheme classifies tokens as to whether they are part of named entities of various types or not. */
FOUNDATION_EXPORT NLTagScheme const NLTagSchemeNameTypeOrLexicalClass API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));  /* This tag scheme follows NLTagSchemeNameType for names, NLTagSchemeLexicalClass for all other tokens. */
FOUNDATION_EXPORT NLTagScheme const NLTagSchemeLemma API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                   /* This tag scheme supplies a stem form for each word token (if known). */
FOUNDATION_EXPORT NLTagScheme const NLTagSchemeLanguage API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                /* This tag scheme tags tokens according to their most likely language (if known). */
FOUNDATION_EXPORT NLTagScheme const NLTagSchemeScript API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                  /* This tag scheme tags tokens according to their script. */

/* An NLTag is a tag associated with a given tag scheme that can be returned by NLTagger. Each tag scheme has its own set of tags. For NLTagSchemeTokenType, NLTagSchemeLexicalClass, NLTagSchemeNameType, and NLTagSchemeNameTypeOrLexicalClass, tags will be taken from the lists below (clients may use == comparison). Tags for NLTagSchemeLemma are lemmas from the language. Tags for NLTagSchemeLanguage are standard language abbreviations. Tags for NLTagSchemeScript are standard script abbreviations
*/

typedef NSString *NLTag NS_TYPED_EXTENSIBLE_ENUM;

/* Tags for NLTagSchemeTokenType */
FOUNDATION_EXPORT NLTag const NLTagWord API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                          /* Tokens considered to be words or word-like linguistic items. */
FOUNDATION_EXPORT NLTag const NLTagPunctuation API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                   /* Tokens made up of punctuation. */
FOUNDATION_EXPORT NLTag const NLTagWhitespace API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                    /* Tokens made up of whitespace of all sorts. */
FOUNDATION_EXPORT NLTag const NLTagOther API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));                         /* Other tokens, including non-linguistic items such as symbols. */

/* Tags for NLTagSchemeLexicalClass */
FOUNDATION_EXPORT NLTag const NLTagNoun API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagVerb API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagAdjective API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagAdverb API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagPronoun API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagDeterminer API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagParticle API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagPreposition API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagNumber API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagConjunction API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagInterjection API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagClassifier API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagIdiom API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagOtherWord API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagSentenceTerminator API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagOpenQuote API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagCloseQuote API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagOpenParenthesis API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagCloseParenthesis API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagWordJoiner API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagDash API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagOtherPunctuation API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagParagraphBreak API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagOtherWhitespace API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Tags for NLTagSchemeNameType */
FOUNDATION_EXPORT NLTag const NLTagPersonalName API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagPlaceName API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLTag const NLTagOrganizationName API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

// ==========  NaturalLanguage.framework/Headers/NLTagger.h
/*    NLTagger.h
      Copyright (c) 2017-2018, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <NaturalLanguage/NLLanguage.h>
#import <NaturalLanguage/NLTagScheme.h>
#import <NaturalLanguage/NLTokenizer.h>

@class NLModel;

NS_ASSUME_NONNULL_BEGIN

/* NLTagger is a class used to automatically tag portions of natural language text with information such as parts of speech, named entities, lemmas, language, and script. An instance of this class is assigned a string to tag, and clients can then obtain tags and ranges for tokens in that string appropriate to a given tag scheme and unit. Predefined tag schemes and tags are defined in NLTagScheme.h.  Options arguments of type NLTaggerOptions may include the following flags, which allow clients interested only in certain general types of tokens to specify that tokens of other types should be omitted from the returned results.
*/

typedef NS_OPTIONS(NSUInteger, NLTaggerOptions) {   /* Any combination of options from the enumeration. */
    NLTaggerOmitWords         = 1 << 0,       /* Omit tokens of type NLTagWord. */
    NLTaggerOmitPunctuation   = 1 << 1,       /* Omit tokens of type NLTagPunctuation. */
    NLTaggerOmitWhitespace    = 1 << 2,       /* Omit tokens of type NLTagWhitespace. */
    NLTaggerOmitOther         = 1 << 3,       /* Omit tokens of type NLTagOther. */
    NLTaggerJoinNames         = 1 << 4,       /* Join tokens of tag scheme NLTagSchemeNameType. */
    NLTaggerJoinContractions  = 1 << 5        /* Join contractions such as it's, can't, etc. */
} NS_SWIFT_NAME(NLTagger.Options);

NS_CLASS_AVAILABLE(10_14, 12_0)
@interface NLTagger : NSObject

/* An instance of NLTagger is created with an array of tag schemes. The tagger will be able to supply tags corresponding to any of the schemes in this array.
*/
- (instancetype)initWithTagSchemes:(NSArray<NLTagScheme> *)tagSchemes NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@property (readonly, copy, nonatomic) NSArray<NLTagScheme> *tagSchemes API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* An NLTagger instance must be assigned a string to tag, and clients can then obtain tags and ranges for tokens in that string appropriate to a given tag scheme and unit.
*/
@property (nullable, retain, nonatomic) NSString *string API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Not all combinations of scheme and unit are supported, and not all combinations of scheme and language are supported. Clients can use +availableTagSchemesForUnit:language: to determine which ones are supported on the current device.
*/
+ (NSArray<NLTagScheme> *)availableTagSchemesForUnit:(NLTokenUnit)unit language:(NLLanguage)language API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Returns the range corresponding to the token for the given unit that contains the given character index.
*/
- (NSRange)tokenRangeAtIndex:(NSUInteger)characterIndex unit:(NLTokenUnit)unit API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/* Returns the top identified language (if any) for the entire string. Convenience for tagAtIndex: with NLTagSchemeLanguage and NLTaggerUnitDocument.
*/
@property (nullable, readonly, copy, nonatomic) NLLanguage dominantLanguage API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* The tagger will segment the string as needed into tokens for the given unit, and return those ranges along with a tag for any scheme in its array of tag schemes. The fundamental tagging method on NLTagger is a block iterator, that iterates over all tokens intersecting a given range, supplying tags and ranges. There are additional convenience methods for obtaining information about a single token, or for obtaining information about all tokens intersecting a given range at once. In each case, the index or range passed in must not extend beyond the end of the tagger's string, or the methods will raise an exception. Note that a given instance of NLTagger should not be used from more than one thread simultaneously.
*/
- (void)enumerateTagsInRange:(NSRange)range unit:(NLTokenUnit)unit scheme:(NLTagScheme)scheme options:(NLTaggerOptions)options usingBlock:(void (NS_NOESCAPE ^)(NLTag _Nullable tag, NSRange tokenRange, BOOL *stop))block API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;
- (nullable NLTag)tagAtIndex:(NSUInteger)characterIndex unit:(NLTokenUnit)unit scheme:(NLTagScheme)scheme tokenRange:(nullable NSRangePointer)tokenRange API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;
- (NSArray<NLTag> *)tagsInRange:(NSRange)range unit:(NLTokenUnit)unit scheme:(NLTagScheme)scheme options:(NLTaggerOptions)options tokenRanges:(NSArray<NSValue *> * _Nullable * _Nullable)tokenRanges API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/* If clients know the language or orthography for a given portion of the string, they may supply it to the tagger. Otherwise, the tagger will infer the language from the contents of the text. In each case, the range passed in must not extend beyond the end of the tagger's string, or the methods will raise an exception.
*/
- (void)setLanguage:(NLLanguage)language range:(NSRange)range API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;
- (void)setOrthography:(NSOrthography *)orthography range:(NSRange)range API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) NS_REFINED_FOR_SWIFT;

/* In addition to the built-in models for predefined tag schemes, clients can set custom models that they have trained, either for existing tag schemes or for custom tag schemes. If multiple models are specified, they will be matched to text based on the language that they specify.
*/
- (void)setModels:(NSArray <NLModel *> *)models forTagScheme:(NLTagScheme)tagScheme;
- (NSArray <NLModel *> *)modelsForTagScheme:(NLTagScheme)tagScheme;

@end

NS_ASSUME_NONNULL_END
// ==========  NaturalLanguage.framework/Headers/NLLanguage.h
/*    NLLanguage.h
      Copyright (c) 2017-2018, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

/* An NLLanguage is a BCP-47 language tag, such as "en" for English, "fr" for French, etc. Constants are provided for a set of languages, but this list is by no means exhaustive; clients may specify their own values using any language tag.
*/

typedef NSString *NLLanguage NS_TYPED_EXTENSIBLE_ENUM;

FOUNDATION_EXPORT NLLanguage const NLLanguageUndetermined API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

FOUNDATION_EXPORT NLLanguage const NLLanguageAmharic API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageArabic API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageArmenian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageBengali API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageBulgarian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageBurmese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageCatalan API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageCherokee API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageCroatian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageCzech API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageDanish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageDutch API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageEnglish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageFinnish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageFrench API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageGeorgian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageGerman API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageGreek API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageGujarati API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageHebrew API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageHindi API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageHungarian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageIcelandic API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageIndonesian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageItalian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageJapanese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageKannada API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageKhmer API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageKorean API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageLao API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageMalay API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageMalayalam API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageMarathi API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageMongolian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageNorwegian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageOriya API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguagePersian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguagePolish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguagePortuguese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguagePunjabi API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageRomanian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageRussian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageSimplifiedChinese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageSinhalese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageSlovak API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageSpanish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageSwedish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageTamil API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageTelugu API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageThai API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageTibetan API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageTraditionalChinese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageTurkish API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageUkrainian API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageUrdu API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
FOUNDATION_EXPORT NLLanguage const NLLanguageVietnamese API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
// ==========  NaturalLanguage.framework/Headers/NLModel.h
/*    NLModel.h
      Copyright (c) 2017-2018, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <NaturalLanguage/NLLanguage.h>
#import <CoreML/MLModel.h>

@class NLModelConfiguration;

NS_ASSUME_NONNULL_BEGIN

/* NLModel is a class representing a custom model that has been trained for tagging. Currently supported models follow one of two types. Classifier models, of type NLModelTypeClassifier, tag text at the sentence or higher level. Sequence models, of type NLModelTypeSequence, tag text at the token level. Currently NLModel objects can be created only from model files on disk or from MLModel objects. Each NLModel object has an associated NLModelConfiguration, which contains all the metadata about the model, including specifying whether it is a sequence or classifier model.
*/

typedef NS_ENUM(NSInteger, NLModelType) {
    NLModelTypeClassifier,
    NLModelTypeSequence
} NS_SWIFT_NAME(NLModel.ModelType);

NS_CLASS_AVAILABLE(10_14, 12_0)
@interface NLModel : NSObject

+ (nullable instancetype)modelWithContentsOfURL:(NSURL *)url error:(NSError **)error API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
+ (nullable instancetype)modelWithMLModel:(MLModel *)mlModel error:(NSError **)error API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@property (readonly, copy) NLModelConfiguration *configuration API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* For inference purposes, a model will usually be attached to an NLTagger via -setModels:forTagScheme:, and the tagger will then take care of calling the model to produce tags as appropriate. However, it is also possible to use a model to make an individual prediction, either of the label for a given pieces of text (for a classifier model), or of the labels for a given sequence of tokens (for a sequence model).
*/

- (nullable NSString *)predictedLabelForString:(NSString *)string API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

- (NSArray<NSString *> *)predictedLabelsForTokens:(NSArray<NSString *> *)tokens API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@end

/* NLModelConfiguration is a class representing the metadata about a model, including specifying whether it is a sequence or classifier model, what language it is intended to support, and what revision of the model training was used to produce the model.
*/

NS_CLASS_AVAILABLE(10_14, 12_0)
@interface NLModelConfiguration : NSObject <NSCopying, NSSecureCoding>

@property (readonly) NLModelType type API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Most models will be trained to support tagging for a specific language, specified using a standard language abbreviation.
*/
@property (nullable, readonly, copy) NLLanguage language API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/* Each update to model training is specified by a particular revision number, and each model is labeled with the revision of the model training that was used to produce it. Each system version has a current revision for each model type, corresponding to the most recent revision of model training available, and a larger set of supported revisions for backward compatibility. A given revision will be supported for a number of system versions, but not indefinitely, and the set of supported revisions can be used to determine whether a given revision is still supported. Attempting to use a model from a revision that is no longer supported will fail with a suitable error.
*/

@property (readonly) NSUInteger revision API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

+ (NSIndexSet *)supportedRevisionsForType:(NLModelType)type API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));
+ (NSUInteger)currentRevisionForType:(NLModelType)type API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@end

NS_ASSUME_NONNULL_END
