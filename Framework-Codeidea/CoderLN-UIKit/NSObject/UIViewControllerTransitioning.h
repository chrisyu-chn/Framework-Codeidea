/*
 * UIViewControllerTransitioning.h
 *
 * UIKit (c) 2013-2017
 *「Public_不知名开发者 | https://github.com/CoderLN | https://www.jianshu.com/u/fd745d76c816」
 *
 * 各位厂友, 由于「时间 & 知识」有限, 总结的文章难免有「未全、不足」, 该模块将系统化学习, 后续「坚持新增文章, 替换、补充文章内容」
 */
 
#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIViewControllerTransitionCoordinator.h>
#import <UIKit/UIViewAnimating.h>
#import <UIKit/UITimingParameters.h>

NS_ASSUME_NONNULL_BEGIN

@class UIView;

// The following keys are understood by UIViewControllerContextTransitioning context objects
// that are created by the system.

#if UIKIT_STRING_ENUMS
UIKIT_EXTERN UITransitionContextViewControllerKey const UITransitionContextFromViewControllerKey NS_SWIFT_NAME(from) NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN UITransitionContextViewControllerKey const UITransitionContextToViewControllerKey NS_SWIFT_NAME(to) NS_AVAILABLE_IOS(7_0);

UIKIT_EXTERN UITransitionContextViewKey const UITransitionContextFromViewKey NS_SWIFT_NAME(from) NS_AVAILABLE_IOS(8_0);
UIKIT_EXTERN UITransitionContextViewKey const UITransitionContextToViewKey NS_SWIFT_NAME(to) NS_AVAILABLE_IOS(8_0);
#else
UIKIT_EXTERN UITransitionContextViewControllerKey const UITransitionContextFromViewControllerKey NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN UITransitionContextViewControllerKey const UITransitionContextToViewControllerKey NS_AVAILABLE_IOS(7_0);

UIKIT_EXTERN UITransitionContextViewKey const UITransitionContextFromViewKey NS_AVAILABLE_IOS(8_0);
UIKIT_EXTERN UITransitionContextViewKey const UITransitionContextToViewKey NS_AVAILABLE_IOS(8_0);
#endif


// A transition context object is constructed by the system and passed to the
// animator in its animateTransition: and transitionDuration: methods as well as
// to the interaction controller in its startInteractiveTransition: method. If
// there is an interaction controller its startInteractiveTransition: is called
// first and its up to the the interaction controller object to call the
// animateTransition: method if needed. If there is no interaction controller,
// then the system automatically invokes the animator's animateTransition:
// method.
//
// The system queries the view controller's transitioningDelegate or the
// navigation controller's delegate to determine if an animator or interaction
// controller should be used in a transition. The transitioningDelegate is a new
// propery on UIViewController and conforms to the
// UIViewControllerTransitioningDelegate protocol defined below. The navigation
// controller likewise has been augmented with a couple of new delegate methods.
//
// The UIViewControllerContextTransitioning protocol can be adopted by custom
// container controllers.  It is purposely general to cover more complex
// transitions than the system currently supports. For now, navigation push/pops
// and UIViewController present/dismiss transitions can be
// customized. Information about the transition is obtained by using the
// viewControllerForKey:, initialFrameForViewController:, and
// finalFrameForViewController: methods. The system provides two keys for
// identifying the from view controller and the to view controller for
// navigation push/pop and view controller present/dismiss transitions.
//
// All custom animations must invoke the context's completeTransition: method
// when the transition completes.  Furthermore the animation should take place
// within the containerView specified by the context. For interactive
// transitions the context's updateInteractiveTransition:,
// finishInteractiveTransition or cancelInteractiveTransition should be called
// as the interactive animation proceeds. The UIPercentDrivenInteractiveTransition
// class provides an implementation of the UIViewControllerInteractiveTransitioning
// protocol that can be used to interactively drive any UIView property animations
// that are created by an animator.


@protocol UIViewControllerContextTransitioning <NSObject>

// The view in which the animated transition should take place.
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) UIView *containerView;
#else
- (UIView *)containerView;
#endif

// Most of the time this is YES. For custom transitions that use the new UIModalPresentationCustom
// presentation type we will invoke the animateTransition: even though the transition should not be
// animated. This allows the custom transition to add or remove subviews to the container view.
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly, getter=isAnimated) BOOL animated;

@property(nonatomic, readonly, getter=isInteractive) BOOL interactive; // This indicates whether the transition is currently interactive.

@property(nonatomic, readonly) BOOL transitionWasCancelled;

@property(nonatomic, readonly) UIModalPresentationStyle presentationStyle;
#else
- (BOOL)isAnimated;

// The next two values can change if the animating transition is interruptible.
- (BOOL)isInteractive; // This indicates whether the transition is currently interactive.
- (BOOL)transitionWasCancelled;

- (UIModalPresentationStyle)presentationStyle;
#endif

// An interaction controller that conforms to the
// UIViewControllerInteractiveTransitioning protocol (which is vended by a
// container view controller's delegate or, in the case of a presentation, the
// transitioningDelegate) should call these methods as the interactive
// transition is scrubbed and then either cancelled or completed. Note that if
// the animator is interruptible, then calling finishInteractiveTransition: and
// cancelInteractiveTransition: are indications that if the transition is not
// interrupted again it will finish naturally or be cancelled.

- (void)updateInteractiveTransition:(CGFloat)percentComplete;
- (void)finishInteractiveTransition;
- (void)cancelInteractiveTransition;

// This should be called if the transition animation is interruptible and it
// is being paused.
- (void)pauseInteractiveTransition NS_AVAILABLE_IOS(10_0);

// This must be called whenever a transition completes (or is cancelled.)
// Typically this is called by the object conforming to the
// UIViewControllerAnimatedTransitioning protocol that was vended by the transitioning
// delegate.  For purely interactive transitions it should be called by the
// interaction controller. This method effectively updates internal view
// controller state at the end of the transition.
- (void)completeTransition:(BOOL)didComplete;


// Currently only two keys are defined by the
// system - UITransitionContextToViewControllerKey, and
// UITransitionContextFromViewControllerKey.
// Animators should not directly manipulate a view controller's views and should
// use viewForKey: to get views instead.
- (nullable __kindof UIViewController *)viewControllerForKey:(UITransitionContextViewControllerKey)key;

// Currently only two keys are defined by the system -
// UITransitionContextFromViewKey, and UITransitionContextToViewKey
// viewForKey: may return nil which would indicate that the animator should not
// manipulate the associated view controller's view.
- (nullable __kindof UIView *)viewForKey:(UITransitionContextViewKey)key NS_AVAILABLE_IOS(8_0);

#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) CGAffineTransform targetTransform NS_AVAILABLE_IOS(8_0);
#else
- (CGAffineTransform)targetTransform NS_AVAILABLE_IOS(8_0);
#endif

// The frame's are set to CGRectZero when they are not known or
// otherwise undefined.  For example the finalFrame of the
// fromViewController will be CGRectZero if and only if the fromView will be
// removed from the window at the end of the transition. On the other
// hand, if the finalFrame is not CGRectZero then it must be respected
// at the end of the transition.
- (CGRect)initialFrameForViewController:(UIViewController *)vc;
- (CGRect)finalFrameForViewController:(UIViewController *)vc;
@end

@protocol UIViewControllerAnimatedTransitioning <NSObject>

// This is used for percent driven interactive transitions, as well as for
// container controllers that have companion animations that might need to
// synchronize with the main animation.
- (NSTimeInterval)transitionDuration:(nullable id <UIViewControllerContextTransitioning>)transitionContext;
// This method can only  be a nop if the transition is interactive and not a percentDriven interactive transition.
- (void)animateTransition:(id <UIViewControllerContextTransitioning>)transitionContext;

@optional

/// A conforming object implements this method if the transition it creates can
/// be interrupted. For example, it could return an instance of a
/// UIViewPropertyAnimator. It is expected that this method will return the same
/// instance for the life of a transition.
- (id <UIViewImplicitlyAnimating>) interruptibleAnimatorForTransition:(id <UIViewControllerContextTransitioning>)transitionContext NS_AVAILABLE_IOS(10_0);

// This is a convenience and if implemented will be invoked by the system when the transition context's completeTransition: method is invoked.
- (void)animationEnded:(BOOL) transitionCompleted;

@end


@protocol UIViewControllerInteractiveTransitioning <NSObject>
- (void)startInteractiveTransition:(id <UIViewControllerContextTransitioning>)transitionContext;

@optional
#if UIKIT_DEFINE_AS_PROPERTIES
@property(nonatomic, readonly) CGFloat completionSpeed;
@property(nonatomic, readonly) UIViewAnimationCurve completionCurve;
#else
- (CGFloat)completionSpeed;
- (UIViewAnimationCurve)completionCurve;
#endif

/// In 10.0, if an object conforming to UIViewControllerAnimatedTransitioning is
/// known to be interruptible, it is possible to start it as if it was not
/// interactive and then interrupt the transition and interact with it. In this
/// case, implement this method and return NO. If an interactor does not
/// implement this method, YES is assumed.
@property (nonatomic, readonly) BOOL wantsInteractiveStart NS_AVAILABLE_IOS(10_0);

@end

@class UIPresentationController;

@protocol UIViewControllerTransitioningDelegate <NSObject>

@optional
- (nullable id <UIViewControllerAnimatedTransitioning>)animationControllerForPresentedController:(UIViewController *)presented presentingController:(UIViewController *)presenting sourceController:(UIViewController *)source;

- (nullable id <UIViewControllerAnimatedTransitioning>)animationControllerForDismissedController:(UIViewController *)dismissed;

- (nullable id <UIViewControllerInteractiveTransitioning>)interactionControllerForPresentation:(id <UIViewControllerAnimatedTransitioning>)animator;

- (nullable id <UIViewControllerInteractiveTransitioning>)interactionControllerForDismissal:(id <UIViewControllerAnimatedTransitioning>)animator;

- (nullable UIPresentationController *)presentationControllerForPresentedViewController:(UIViewController *)presented presentingViewController:(nullable UIViewController *)presenting sourceViewController:(UIViewController *)source NS_AVAILABLE_IOS(8_0);

@end

NS_CLASS_AVAILABLE_IOS(7_0) @interface UIPercentDrivenInteractiveTransition : NSObject <UIViewControllerInteractiveTransitioning>

/// This is the non-interactive duration that was returned when the
/// animators transitionDuration: method was called when the transition started.
@property (readonly) CGFloat duration;

/// The last percentComplete value specified by updateInteractiveTransition:
@property (readonly) CGFloat percentComplete;

/// completionSpeed defaults to 1.0 which corresponds to a completion duration of
/// (1 - percentComplete)*duration.  It must be greater than 0.0. The actual
/// completion is inversely proportional to the completionSpeed.  This can be set
/// before cancelInteractiveTransition or finishInteractiveTransition is called
/// in order to speed up or slow down the non interactive part of the
/// transition.
@property (nonatomic,assign) CGFloat completionSpeed;

/// When the interactive part of the transition has completed, this property can
/// be set to indicate a different animation curve. It defaults to UIViewAnimationCurveEaseInOut.
/// Note that during the interactive portion of the animation the timing curve is linear.
@property (nonatomic,assign) UIViewAnimationCurve completionCurve;

/// For an interruptible animator, one can specify a different timing curve provider to use when the
/// transition is continued. This property is ignored if the animated transitioning object does not
/// vend an interruptible animator.
@property (nullable, nonatomic, strong)id <UITimingCurveProvider> timingCurve NS_AVAILABLE_IOS(10_0);

/// Set this to NO in order to start an interruptible transition non
/// interactively. By default this is YES, which is consistent with the behavior
/// before 10.0.
@property (nonatomic) BOOL wantsInteractiveStart NS_AVAILABLE_IOS(10_0);

/// Use this method to pause a running interruptible animator. This will ensure that all blocks
/// provided by a transition coordinator's notifyWhenInteractionChangesUsingBlock: method
/// are executed when a transition moves in and out of an interactive mode.
- (void)pauseInteractiveTransition NS_AVAILABLE_IOS(10_0);

// These methods should be called by the gesture recognizer or some other logic
// to drive the interaction. This style of interaction controller should only be
// used with an animator that implements a CA style transition in the animator's
// animateTransition: method. If this type of interaction controller is
// specified, the animateTransition: method must ensure to call the
// UIViewControllerTransitionParameters completeTransition: method. The other
// interactive methods on UIViewControllerContextTransitioning should NOT be
// called. If there is an interruptible animator, these methods will either scrub or continue
// the transition in the forward or reverse directions.
- (void)updateInteractiveTransition:(CGFloat)percentComplete;
- (void)cancelInteractiveTransition;
- (void)finishInteractiveTransition;

@end
NS_ASSUME_NONNULL_END

