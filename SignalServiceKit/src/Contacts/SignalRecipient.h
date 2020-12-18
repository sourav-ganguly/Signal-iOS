//
//  Copyright (c) 2020 Open Whisper Systems. All rights reserved.
//

#import "BaseModel.h"

NS_ASSUME_NONNULL_BEGIN

@class SDSAnyReadTransaction;
@class SDSAnyWriteTransaction;
@class SignalServiceAddress;

typedef NS_CLOSED_ENUM(
    NSUInteger, SignalRecipientTrustLevel) { SignalRecipientTrustLevelLow, SignalRecipientTrustLevelHigh };

/// SignalRecipient serves two purposes:
///
/// a) It serves as a cache of "known" Signal accounts.  When the service indicates
///    that an account exists, we make sure that an instance of SignalRecipient exists
///    for that recipient id (using mark as registered) and has at least one device.
///    When the service indicates that an account does not exist, we remove any devices
///    from that SignalRecipient - but do not remove it from the database.
///    Note that SignalRecipients without any devices are not considered registered.
/// b) We hang the "known device list" for known signal accounts on this entity.
@interface SignalRecipient : BaseModel

@property (nonatomic, readonly) NSOrderedSet<NSNumber *> *devices;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithUniqueId:(NSString *)uniqueId NS_UNAVAILABLE;
- (instancetype)initWithGrdbId:(int64_t)grdbId uniqueId:(NSString *)uniqueId NS_UNAVAILABLE;

#if TESTABLE_BUILD
- (instancetype)initWithAddress:(SignalServiceAddress *)address;
- (instancetype)initWithUUIDString:(NSString *)uuidString;

- (instancetype)initWithPhoneNumber:(nullable NSString *)phoneNumber
                               uuid:(nullable NSUUID *)uuid
                            devices:(NSArray<NSNumber *> *)devices;
#endif

// --- CODE GENERATION MARKER

// This snippet is generated by /Scripts/sds_codegen/sds_generate.py. Do not manually edit it, instead run `sds_codegen.sh`.

// clang-format off

- (instancetype)initWithGrdbId:(int64_t)grdbId
                      uniqueId:(NSString *)uniqueId
                         devices:(NSOrderedSet<NSNumber *> *)devices
            recipientPhoneNumber:(nullable NSString *)recipientPhoneNumber
                   recipientUUID:(nullable NSString *)recipientUUID
NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(grdbId:uniqueId:devices:recipientPhoneNumber:recipientUUID:));

// clang-format on

// --- CODE GENERATION MARKER

+ (nullable instancetype)getRecipientForAddress:(SignalServiceAddress *)address
                                mustHaveDevices:(BOOL)mustHaveDevices
                                    transaction:(SDSAnyReadTransaction *)transaction
    NS_SWIFT_NAME(get(address:mustHaveDevices:transaction:));

+ (void)updateWithAddress:(SignalServiceAddress *)address
             devicesToAdd:(nullable NSArray<NSNumber *> *)devicesToAdd
          devicesToRemove:(nullable NSArray<NSNumber *> *)devicesToRemove
              transaction:(SDSAnyWriteTransaction *)transaction;

- (void)updateWithDevicesToAdd:(nullable NSArray<NSNumber *> *)devicesToAdd
               devicesToRemove:(nullable NSArray<NSNumber *> *)devicesToRemove
                   transaction:(SDSAnyWriteTransaction *)transaction;

@property (nonatomic, nullable) NSString *recipientPhoneNumber;
@property (nonatomic, nullable) NSString *recipientUUID;

@property (nonatomic, readonly) SignalServiceAddress *address;

- (NSComparisonResult)compare:(SignalRecipient *)other;

+ (BOOL)isRegisteredRecipient:(SignalServiceAddress *)address transaction:(SDSAnyReadTransaction *)transaction;

+ (SignalRecipient *)markRecipientAsRegisteredAndGet:(SignalServiceAddress *)address
                                          trustLevel:(SignalRecipientTrustLevel)trustLevel
                                         transaction:(SDSAnyWriteTransaction *)transaction;

+ (SignalRecipient *)markRecipientAsRegisteredAndGet:(SignalServiceAddress *)address
                                            deviceId:(UInt32)deviceId
                                          trustLevel:(SignalRecipientTrustLevel)trustLevel
                                         transaction:(SDSAnyWriteTransaction *)transaction;

+ (void)markRecipientAsUnregistered:(SignalServiceAddress *)address transaction:(SDSAnyWriteTransaction *)transaction;

- (void)removePhoneNumberForDatabaseMigration;

@end

NS_ASSUME_NONNULL_END
