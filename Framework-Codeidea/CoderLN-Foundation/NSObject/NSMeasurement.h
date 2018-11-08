/*
 * NSMeasurement.h
 *
 * Foundation (c) 2015-2017
 *「Public_不知名开发者 | https://github.com/CoderLN | https://www.jianshu.com/u/fd745d76c816」
 *
 * 各位厂友, 由于「时间 & 知识」有限, 总结的文章难免有「未全、不足」, 该模块将系统化学习, 后续「坚持新增文章, 替换、补充文章内容」
 */

 
#import <Foundation/NSObject.h>
#import <Foundation/NSUnit.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_12, 10_0)
@interface NSMeasurement<UnitType: NSUnit *> : NSObject<NSCopying, NSSecureCoding> {
@private
    UnitType _unit;
    double _doubleValue;
}

@property (readonly, copy) UnitType unit;
@property (readonly) double doubleValue;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithDoubleValue:(double)doubleValue unit:(UnitType)unit NS_DESIGNATED_INITIALIZER;

/*
 Given an NSUnit object, canBeConvertedToUnit: will check for dimensionality i.e. check the unit type (NSUnitAngle, NSUnitLength, NSUnitCustom, etc.) of the NSUnit object.  It will return YES if the unit type of the given unit is the same as the unit type of the unit within the NSMeasurement object and NO if not.
 Note: This method will return NO if given or called on a dimensionless unit.
 */
- (BOOL)canBeConvertedToUnit:(NSUnit *)unit;

/*
 Given an NSUnit object, measurementByConvertingUnit: will first check for dimensionality i.e. check the unit type (NSUnitAngle, NSUnitLength, NSUnitCustom, etc.) of the NSUnit object.  If the unit type of the given unit is not the same as the unit type of the unit within the NSMeasurement object (i.e. the units are of differing dimensionalities), measurementByConvertingToUnit: will throw an InvalidArgumentException.
 
 @return A new NSMeasurement object with the given unit and converted value.
 */
- (NSMeasurement *)measurementByConvertingToUnit:(NSUnit *)unit;

/*
 Given an NSMeasurement object, these methods will first check for dimensionality i.e. check the unit type (NSUnitAngle, NSUnitLength, NSUnitCustom, etc.) of the unit contained in that object.  If the unit type of the unit in the given NSMeasurement object is not the same as the unit type of the unit within the current NSMeasurement instance (i.e. the units are of differing dimensionalities), these methods will throw an InvalidArgumentException.
 
 @return A new NSMeasurement object with the adjusted value and a unit that is the same type as the current NSMeasurement instance.
 */
- (NSMeasurement<UnitType> *)measurementByAddingMeasurement:(NSMeasurement<UnitType> *)measurement;
- (NSMeasurement<UnitType> *)measurementBySubtractingMeasurement:(NSMeasurement<UnitType> *)measurement;

@end
NS_ASSUME_NONNULL_END
