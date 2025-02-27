// Copyright (c) 2020 Tencent. All rights reserved.

/// @defgroup V2TXLiveDef_cplusplus V2TXLiveDef
/// 腾讯云直播服务(LVB)关键类型定义
/// @{

#ifndef MODULE_CPP_V2TXLIVEDEF_H_
#define MODULE_CPP_V2TXLIVEDEF_H_

#ifdef LITEAV_EXPORTS
#define LITEAV_API __declspec(dllexport)
#else
#define LITEAV_API __declspec(dllimport)
#endif

#include <stdint.h>
#include "V2TXLiveCode.hpp"

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#ifdef TRTC_EXPORTS
#define V2_API __declspec(dllexport)
#else
#define V2_API __declspec(dllimport)
#endif
#elif __APPLE__
#include <TargetConditionals.h>
#define V2_API __attribute__((visibility("default")))
#elif __ANDROID__
#define V2_API __attribute__((visibility("default")))
#else
#define V2_API
#endif

#define TARGET_PLATFORM_DESKTOP ((__APPLE__ && TARGET_OS_MAC && !TARGET_OS_IPHONE) || _WIN32)
#define TARGET_PLATFORM_PHONE (__ANDROID__ || (__APPLE__ && TARGET_OS_IOS))

namespace liteav {

/**
 * @brief 支持协议
 */
enum V2TXLiveMode {

#if TARGET_PLATFORM_DESKTOP
    V2TXLiveModeNotSupported,
#else
    // Windows、Mac暂不支持RTMP协议
    V2TXLiveModeRTMP,
#endif

    /// 支持协议: TRTC
    V2TXLiveModeRTC,

};
/// @}

/////////////////////////////////////////////////////////////////////////////////
//
//           （一）视频相关类型定义
//
/////////////////////////////////////////////////////////////////////////////////
/// @name 视频相关类型定义
/// @{

/**
 * @brief 视频分辨率
 */
enum V2TXLiveVideoResolution {

    /// 分辨率 160*160，码率范围：100Kbps ~ 150Kbps，帧率：15fps
    V2TXLiveVideoResolution160x160,

    /// 分辨率 270*270，码率范围：200Kbps ~ 300Kbps，帧率：15fps
    V2TXLiveVideoResolution270x270,

    /// 分辨率 480*480，码率范围：350Kbps ~ 525Kbps，帧率：15fps
    V2TXLiveVideoResolution480x480,

    /// 分辨率 320*240，码率范围：250Kbps ~ 375Kbps，帧率：15fps
    V2TXLiveVideoResolution320x240,

    /// 分辨率 480*360，码率范围：400Kbps ~ 600Kbps，帧率：15fps
    V2TXLiveVideoResolution480x360,

    /// 分辨率 640*480，码率范围：600Kbps ~ 900Kbps，帧率：15fps
    V2TXLiveVideoResolution640x480,

    /// 分辨率 320*180，码率范围：250Kbps ~ 400Kbps，帧率：15fps
    V2TXLiveVideoResolution320x180,

    /// 分辨率 480*270，码率范围：350Kbps ~ 550Kbps，帧率：15fps
    V2TXLiveVideoResolution480x270,

    /// 分辨率 640*360，码率范围：500Kbps ~ 900Kbps，帧率：15fps
    V2TXLiveVideoResolution640x360,

    /// 分辨率 960*540，码率范围：800Kbps ~ 1500Kbps，帧率：15fps
    V2TXLiveVideoResolution960x540,

    /// 分辨率 1280*720，码率范围：1000Kbps ~ 1800Kbps，帧率：15fps
    V2TXLiveVideoResolution1280x720,

    /// 分辨率 1920*1080，码率范围：2500Kbps ~ 3000Kbps，帧率：15fps
    V2TXLiveVideoResolution1920x1080,

};

/**
 * @brief 视频宽高比模式。
 *
 * @note
 * - 横屏模式下的分辨率: V2TXLiveVideoResolution640_360 + V2TXLiveVideoResolutionModeLandscape = 640x360
 * - 竖屏模式下的分辨率: V2TXLiveVideoResolution640_360 + V2TXLiveVideoResolutionModePortrait = 360x640
 */
enum V2TXLiveVideoResolutionMode {

    /// 横屏模式
    V2TXLiveVideoResolutionModeLandscape,

    /// 竖屏模式
    V2TXLiveVideoResolutionModePortrait

};

/**
 * 视频编码参数。
 *
 * 该设置决定远端用户看到的画面质量。
 */
struct V2_API V2TXLiveVideoEncoderParam {
    ///【字段含义】 视频分辨率
    ///【特别说明】如需使用竖屏分辨率，请指定 videoResolutionMode 为 Portrait，例如： 640 × 360 + Portrait = 360 × 640。
    ///【推荐取值】
    /// - 桌面平台（Win + Mac）：建议选择 640 × 360 及以上分辨率，videoResolutionMode 选择 Landscape，即横屏分辨率。
    V2TXLiveVideoResolution videoResolution;

    ///【字段含义】分辨率模式（横屏分辨率 or 竖屏分辨率）
    ///【推荐取值】桌面平台（Windows、Mac）建议选择 Landscape。
    ///【特别说明】如需使用竖屏分辨率，请指定 resMode 为 Portrait，例如： 640 × 360 + Portrait = 360 × 640。
    V2TXLiveVideoResolutionMode videoResolutionMode;

    ///【字段含义】视频采集帧率
    ///【推荐取值】15fps 或 20fps。5fps 以下，卡顿感明显。10fps 以下，会有轻微卡顿感。20fps 以上，会浪费带宽（电影的帧率为 24fps）。
    uint32_t videoFps;

    ///【字段含义】目标视频码率，SDK 会按照目标码率进行编码，只有在弱网络环境下才会主动降低视频码率。
    ///【推荐取值】请参考 V2TXLiveVideoResolution 在各档位注释的最佳码率，也可以在此基础上适当调高。
    ///           比如：V2TXLiveVideoResolution1280x720 对应 1200kbps 的目标码率，您也可以设置为 1500kbps 用来获得更好的观感清晰度。
    ///【特别说明】您可以通过同时设置 videoBitrate 和 minVideoBitrate 两个参数，用于约束 SDK 对视频码率的调整范围：
    /// - 如果您将 videoBitrate 和 minVideoBitrate 设置为同一个值，等价于关闭 SDK 对视频码率的自适应调节能力。
    uint32_t videoBitrate;

    ///【字段含义】最低视频码率，SDK 会在网络不佳的情况下主动降低视频码率以保持流畅度，最低会降至 minVideoBitrate 所设定的数值。
    ///【推荐取值】您可以通过同时设置 videoBitrate 和 minVideoBitrate 两个参数，用于约束 SDK 对视频码率的调整范围：
    /// - 如果您将 videoBitrate 和 minVideoBitrate 设置为同一个值，等价于关闭 SDK 对视频码率的自适应调节能力。
    uint32_t minVideoBitrate;

    V2TXLiveVideoEncoderParam(V2TXLiveVideoResolution resolution);
};

/**
 * @brief 本地摄像头镜像类型。
 */
enum V2TXLiveMirrorType {

    /// 系统默认镜像类型，前置摄像头镜像，后置摄像头不镜像
    V2TXLiveMirrorTypeAuto,

    /// 前置摄像头和后置摄像头，都切换为镜像模式
    V2TXLiveMirrorTypeEnable,

    /// 前置摄像头和后置摄像头，都切换为非镜像模式
    V2TXLiveMirrorTypeDisable

};

/**
 * @brief 视频画面填充模式。
 */
enum V2TXLiveFillMode {

    /// 图像铺满屏幕，超出显示视窗的视频部分将被裁剪，画面显示可能不完整
    V2TXLiveFillModeFill,

    /// 图像长边填满屏幕，短边区域会被填充黑色，画面的内容完整
    V2TXLiveFillModeFit

};

/**
 * @brief 视频画面顺时针旋转角度。
 */
enum V2TXLiveRotation {

    /// 不旋转
    V2TXLiveRotation0,

    /// 顺时针旋转90度
    V2TXLiveRotation90,

    /// 顺时针旋转180度
    V2TXLiveRotation180,

    /// 顺时针旋转270度
    V2TXLiveRotation270

};

/**
 * @brief 视频帧的像素格式。
 */
enum V2TXLivePixelFormat {

    /// 未知
    V2TXLivePixelFormatUnknown,

    /// YUV420P I420
    V2TXLivePixelFormatI420,

    /// BGRA8888
    V2TXLivePixelFormatBGRA32

};

/**
 * @brief 视频数据包装格式。
 *
 * @note 在自定义采集和自定义渲染功能，您需要用到下列枚举值来指定您希望以什么样的格式来包装视频数据。
 */
enum V2TXLiveBufferType {

    /// 未知
    V2TXLiveBufferTypeUnknown,

    /// 二进制Buffer类型
    V2TXLiveBufferTypeByteBuffer

};

/**
 * @brief 视频帧信息类。
 *        V2TXLiveVideoFrame 描述了视频帧编码之前或解码之后图像的原始数据。
 * @note  在自定义采集和渲染期间使用。使用自定义采集时, 你需要向 V2TXLiveVideoFrame 中填充视频数据用来发送。 使用自定义渲染时, 视频帧是通过填充 V2TXLiveVideoFrame 返回。
 */
struct V2TXLiveVideoFrame {
    /// 【字段含义】视频帧像素格式
    V2TXLivePixelFormat pixelFormat;

    /// 【字段含义】视频数据包装格式
    V2TXLiveBufferType bufferType;

    /// 【字段含义】bufferType 为 V2TXLiveBufferTypeByteBuffer 时的视频数据。
    char* data;

    /// 【字段含义】视频数据的长度，单位是字节
    int32_t length;

    /// 【字段含义】视频宽度
    int32_t width;

    /// 【字段含义】视频高度
    int32_t height;

    /// 【字段含义】视频帧的顺时针旋转角度
    V2TXLiveRotation rotation;

    V2TXLiveVideoFrame() : pixelFormat(V2TXLivePixelFormatUnknown), bufferType(V2TXLiveBufferTypeUnknown), data(nullptr), length(0), width(0), height(0), rotation(V2TXLiveRotation0) {
    }
};
/// @}

/// @}
/////////////////////////////////////////////////////////////////////////////////
//
//          （二）音频相关类型定义
//
/////////////////////////////////////////////////////////////////////////////////

/// @name 音频相关类型定义
/// @{

/**
 * @brief 声音音质。
 */
enum V2TXLiveAudioQuality {

    /// 语音音质：采样率：16k；单声道；音频码率：16kbps；适合语音通话为主的场景，比如在线会议，语音通话
    V2TXLiveAudioQualitySpeech,

    /// 默认音质：采样率：48k；单声道；音频码率：50kbps；SDK 默认的音频质量，如无特殊需求推荐选择之
    V2TXLiveAudioQualityDefault,

    /// 音乐音质：采样率：48k；双声道 + 全频带；音频码率：128kbps；适合需要高保真传输音乐的场景，比如K歌、音乐直播等
    V2TXLiveAudioQualityMusic

};

/**
 * @brief 音频帧数据
 */
struct V2TXLiveAudioFrame {
    /// 【字段含义】音频数据
    char* data;

    /// 【字段含义】音频数据的长度
    uint32_t length;

    /// 【字段含义】采样率
    uint32_t sampleRate;

    /// 【字段含义】声道数
    uint32_t channel;

    V2TXLiveAudioFrame() : data(nullptr), length(0), sampleRate(48000), channel(1) {
    }
};

struct V2TXLiveAudioFrameObserverFormat {
    ///【字段含义】采样率
    ///【推荐取值】默认值：48000Hz。支持 16000, 32000, 44100, 48000。
    int sampleRate;

    ///【字段含义】声道数
    ///【推荐取值】默认值：1，代表单声道。可设定的数值只有两个数字：1-单声道，2-双声道。
    int channel;

    ///【字段含义】采样点数
    ///【推荐取值】取值必须是 sampleRate/100 的整数倍。
    int samplesPerCall;

    V2TXLiveAudioFrameObserverFormat() : sampleRate(0), channel(0), samplesPerCall(0) {
    }
};

/// @}
/////////////////////////////////////////////////////////////////////////////////
//
//          （三）推流器和播放器的一些统计指标数据定义
//
/////////////////////////////////////////////////////////////////////////////////

/// @name 推流器和播放器的一些统计指标数据定义
/// @{

/**
 * @brief 推流器的统计数据。
 */
struct V2TXLivePusherStatistics {
    /// 【字段含义】当前 App 的 CPU 使用率（％）
    int32_t appCpu;

    /// 【字段含义】当前系统的 CPU 使用率（％）
    int32_t systemCpu;

    /// 【字段含义】视频宽度
    int32_t width;

    /// 【字段含义】视频高度
    int32_t height;

    /// 【字段含义】帧率（fps）
    int32_t fps;

    /// 【字段含义】视频码率（Kbps）
    int32_t videoBitrate;

    /// 【字段含义】音频码率（Kbps）
    int32_t audioBitrate;

    V2TXLivePusherStatistics() : appCpu(0), systemCpu(0), width(0), height(0), fps(0), audioBitrate(0), videoBitrate(0) {
    }
};

/**
 * @brief 播放器的统计数据。
 */
struct V2TXLivePlayerStatistics {
    /// 【字段含义】当前 App 的 CPU 使用率（％）
    int32_t appCpu;

    /// 【字段含义】当前系统的 CPU 使用率（％）
    int32_t systemCpu;

    /// 【字段含义】视频宽度
    int32_t width;

    /// 【字段含义】视频高度
    int32_t height;

    /// 【字段含义】帧率（fps）
    int32_t fps;

    /// 【字段含义】视频码率（Kbps）
    int32_t videoBitrate;

    /// 【字段含义】音频码率（Kbps）
    int32_t audioBitrate;

    V2TXLivePlayerStatistics() : appCpu(0), systemCpu(0), width(0), height(0), fps(0), audioBitrate(0), videoBitrate(0) {
    }
};

/// @}

/// @}
/////////////////////////////////////////////////////////////////////////////////
//
//          （四）连接状态相关枚举值定义
//
/////////////////////////////////////////////////////////////////////////////////
/// @name 连接状态相关枚举值定义
/// @{

/**
 * @brief 直播流连接状态
 */
enum V2TXLivePushStatus {

    /// 与服务器断开连接
    V2TXLivePushStatusDisconnected,

    /// 正在连接服务器
    V2TXLivePushStatusConnecting,

    /// 连接服务器成功
    V2TXLivePushStatusConnectSuccess,

    /// 重连服务器中
    V2TXLivePushStatusReconnecting

};
/// @}

/// @}
/////////////////////////////////////////////////////////////////////////////////
//
//          (五) 音视频状态有关的枚举值的定义
//
/////////////////////////////////////////////////////////////////////////////////

/// @name 音视频状态有关的枚举值的定义
/// @{

/**
 * @brief 直播流的播放状态。
 */
enum V2TXLivePlayStatus {

    /// 播放停止
    V2TXLivePlayStatusStopped,

    /// 正在播放
    V2TXLivePlayStatusPlaying,

    /// 正在缓冲(首次加载不会抛出 Loading 事件)
    V2TXLivePlayStatusLoading,

};

/**
 * @brief 直播流的播放状态变化原因
 */
enum V2TXLiveStatusChangeReason {

    /// 内部原因
    V2TXLiveStatusChangeReasonInternal,

    /// 开始网络缓冲
    V2TXLiveStatusChangeReasonBufferingBegin,

    /// 结束网络缓冲
    V2TXLiveStatusChangeReasonBufferingEnd,

    /// 本地启动播放
    V2TXLiveStatusChangeReasonLocalStarted,

    /// 本地停止播放
    V2TXLiveStatusChangeReasonLocalStopped,

    /// 远端可播放
    V2TXLiveStatusChangeReasonRemoteStarted,

    /// 远端流停止或中断
    V2TXLiveStatusChangeReasonRemoteStopped,

    /// 远端流离线
    V2TXLiveStatusChangeReasonRemoteOffline,

};
/// @}

/////////////////////////////////////////////////////////////////////////////////
//
//          (六) 公共配置组件
//
/////////////////////////////////////////////////////////////////////////////////
/// @name 公共配置组件有关的枚举值的定义
/// @{

/**
 * 图片类型.
 */
enum V2TXLiveImageType {

    ///图片文件路径，支持 GIF、JPEG、PNG文件格式
    V2TXLiveImageTypeFile = 0,

    /// BGRA32格式内存块
    V2TXLiveImageTypeBGRA32 = 1,

    /// RGBA32格式内存块
    V2TXLiveImageTypeRGBA32 = 2,
};

/**
 * 图片信息
 */
struct V2TXLiveImage {
    /// V2TXLiveImageTypeFile: 图片路径; 其他类型:图片内容
    const char* imageSrc;

    ///图片数据类型,默认为V2TXLiveImageFile {@link V2TXLiveImageType}
    V2TXLiveImageType imageType;

    ///图片宽度,默认为0(图片数据类型为V2TXLiveImageTypeFile,忽略该参数)
    uint32_t imageWidth;

    ///图片高度,默认为0(图片数据类型为V2TXLiveImageTypeFile,忽略该参数)
    uint32_t imageHeight;

    ///图片数据的长度;单位字节
    uint32_t imageLength;

    V2TXLiveImage() : imageSrc(nullptr), imageType(V2TXLiveImageTypeBGRA32), imageWidth(0), imageHeight(0), imageLength(0){};
};

/// @name 屏幕分享有关的定义
/// @{
/**
 * 屏幕分享目标信息
 */
enum V2TXLiveScreenCaptureSourceType {

    /// 未知
    V2TXLiveScreenCaptureSourceTypeUnknown = -1,

    /// 该分享目标是某一个窗口
    V2TXLiveScreenCaptureSourceTypeWindow = 0,

    /// 该分享目标是整个桌面
    V2TXLiveScreenCaptureSourceTypeScreen = 1,

    /// 自定义窗口类型
    V2TXLiveScreenCaptureSourceTypeCustom = 2,

};

/**
 * 屏幕分享窗口信息
 *
 * 您可以通过 getScreenCaptureSources() 枚举可共享的窗口列表，列表通过 IV2TXLiveScreenCaptureSourceList 返回
 */
struct V2TXLiveScreenCaptureSourceInfo {
    /// 采集源类型
    V2TXLiveScreenCaptureSourceType sourceType;

    /// 采集源 ID；对于窗口，该字段指示窗口句柄；对于屏幕，该字段指示屏幕 ID
    void* sourceId;

    /// 采集源名称，UTF8 编码
    const char* sourceName;

    /// 缩略图内容
    V2TXLiveImage thumbBGRA;

    /// 图标内容
    V2TXLiveImage iconBGRA;

    /// 是否为最小化窗口，通过 getScreenCaptureSources 获取列表时的窗口状态，仅采集源为 Window 时才可用
    bool isMinimizeWindow;

    /// 是否为主屏，是否为主屏，仅采集源类型为 Screen 时才可用
    bool isMainScreen;

    V2TXLiveScreenCaptureSourceInfo() : sourceType(V2TXLiveScreenCaptureSourceTypeUnknown), sourceId(nullptr), sourceName(nullptr), isMinimizeWindow(false), isMainScreen(false){};
};

/**
 * 屏幕分享窗口列表
 */
class IV2TXLiveScreenCaptureSourceList {
   protected:
    virtual ~IV2TXLiveScreenCaptureSourceList() {
    }

   public:
    /**
     * @return 窗口个数
     */
    virtual uint32_t getCount() = 0;

    /**
     * @return 窗口信息
     */
    virtual V2TXLiveScreenCaptureSourceInfo getSourceInfo(uint32_t index) = 0;

    /**
     * @brief 遍历完窗口列表后，调用 release 释放资源。
     */
    virtual void release() = 0;
};

/**
 * 屏幕分享参数
 *
 * 您可以通过设置结构体内的参数控制屏幕分享边框的颜色、宽度、是否采集鼠标等参数
 */
struct V2TXLiveScreenCaptureProperty {
    /// 是否采集目标内容时顺带采集鼠标，默认为 true
    bool enableCaptureMouse;

    /// 是否高亮正在共享的窗口，默认为 true
    bool enableHighlightBorder;

    /// 是否开启高性能模式（只会在分享屏幕时会生效），开启后屏幕采集性能最佳，但无法过滤远端的高亮边框，默认为 true
    bool enableHighPerformance;

    /// 指定高亮边框颜色，RGB 格式，传入 0 时采用默认颜色，默认颜色为 #8CBF26
    int highlightBorderColor;

    /// 指定高亮边框的宽度，传入0时采用默认描边宽度，默认宽度为 5，最大值为 50
    int highlightBorderSize;

    /// 窗口采集时是否采集子窗口（与采集窗口具有 Owner 或 Popup 属性），默认为 false
    bool enableCaptureChildWindow;

    V2TXLiveScreenCaptureProperty() : enableCaptureMouse(true), enableHighlightBorder(true), enableHighPerformance(true), highlightBorderColor(0), highlightBorderSize(0), enableCaptureChildWindow(false) {
    }
};
/// @}

}  // namespace liteav

#endif  // MODULE_CPP_V2TXLIVEDEF_H_
/// @}
