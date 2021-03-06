/*
 * UIFocusAnimationCoordinator.h
 *
 * UIKit (c) 2015-2017
 *「Public_不知名开发者 | https://github.com/CoderLN | https://www.jianshu.com/u/fd745d76c816」
 *
 * 各位厂友, 由于「时间 & 知识」有限, 总结的文章难免有「未全、不足」, 该模块将系统化学习, 后续「坚持新增文章, 替换、补充文章内容」
 */
 
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


/// UIFocusAnimationContext is used to provide UIKit-determined context about animations that are related to a focus update.
NS_CLASS_AVAILABLE_IOS(11_0) @protocol UIFocusAnimationContext <NSObject>

/// The duration of the main animations in seconds.
@property (nonatomic, readonly) NSTimeInterval duration;

@end

/// UIFocusAnimationCoordinator is used to coordinate disparate animations that are related to a focus update.
NS_CLASS_AVAILABLE_IOS(9_0) @interface UIFocusAnimationCoordinator : NSObject

/**
 Specifies focus-related animations that should be coordinated with the animations of the focusing or un-focusing view.
 
 Any animations specified will be run in the same animation context as the main animation. The completion block is invoked after the main animation completes.
 (Note that this may not be after all the coordinated animations specified by the call complete if the duration is not inherited.)
 
 It is perfectly legitimate to only specify a completion block.
 */
- (void)addCoordinatedAnimations:(nullable void (^)(void))animations completion:(nullable void (^)(void))completion;

/**
 Specifies focus-related animations that should be coordinated with the animations of the focusing item.
 
 Any animations specified will be run in the same animation context as the main animation. The completion block is invoked after the UIKit-defined animations complete.
 
 It is perfectly legitimate to only specify a completion block.
 
 A context object is provided in the animation block with details of the UIKit-defined animations being run for the focusing item.
 */
- (void)addCoordinatedFocusingAnimations:(void (^ _Nullable)(id<UIFocusAnimationContext> animationContext))animations completion:(void (^ _Nullable)(void))completion API_AVAILABLE(ios(11.0), tvos(11.0));

/**
 Specifies focus-related animations that should be coordinated with the animations of the un-focusing item.
 
 Any animations specified will be run in the same animation context as the main animation. The completion block is invoked after the UIKit-defined animations complete.
 
 It is perfectly legitimate to only specify a completion block.
 
 A context object is provided in the animation block with details of the UIKit-defined animations being run for the un-focusing item.
 */
- (void)addCoordinatedUnfocusingAnimations:(void (^ _Nullable)(id<UIFocusAnimationContext> animationContext))animations completion:(void (^ _Nullable)(void))completion API_AVAILABLE(ios(11.0), tvos(11.0));

@end
NS_ASSUME_NONNULL_END
