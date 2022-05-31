//
//  VODUploadModel.h
//  VODUpload
//
//  Created by Leigang on 2016/10/26.
//  Copyright © 2016年 Leigang. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, VODUploadFileStatus) {
    VODUploadFileStatusReady,
    VODUploadFileStatusUploading,
    VODUploadFileStatusCanceled,
    VODUploadFileStatusPaused,
    VODUploadFileStatusSuccess,
    VODUploadFileStatusFailure
};

typedef NS_ENUM(NSInteger, VODStatus) {
    VODStatusReady,
    VODStatusStarted,
    VODStatusPaused,
    VODStatusCancel,
    VODStatusStoped,
    VODStatusSuccess,
    VODStatusFailure,
    VODStatusExpire
};

@interface OSSConfig : NSObject

@property (nonatomic, strong) NSString* accessKeyId;
@property (nonatomic, strong) NSString* accessKeySecret;
@property (nonatomic, strong) NSString* secretToken;
@property (nonatomic, strong) NSString* expireTime;

@end


@interface VodInfo : NSObject

/**
 标题
 */
@property (nonatomic, copy) NSString* title;

/**
 标签
 */
@property (nonatomic, copy) NSString* tags;

/**
 描述
 */
@property (nonatomic, copy) NSString* desc;

/**
 分类id
 */
@property (nonatomic, strong) NSNumber* cateId;

/**
 封面url
 */
@property (nonatomic, copy) NSString* coverUrl;

/**
 设置自定义数据
 */
@property (nonatomic, copy) NSString* userData;

/**
 isProcess
 */
@property (nonatomic, assign) BOOL isProcess;

/**
 是否显示水印
 */
@property (nonatomic, assign) BOOL isShowWaterMark;

/**
 优先级
 */
@property (nonatomic, strong) NSNumber* priority;

/**
 设置存储区域
 */
@property (nonatomic, copy) NSString* storageLocation;

/**
 设置转码模板id
 */
@property (nonatomic, copy) NSString* templateGroupId;

/**
 图片类型。仅对图片上传有效。取值：default, cover, 默认值：cover
 */
@property (nonatomic, copy) NSString* imageType;

/**
 获取json字符串
 */
- (NSString*)toJson;


@end


@interface UploadFileInfo : NSObject
/**
 是否流文件
 */
@property (nonatomic, readonly) BOOL isStreamFile;
/**
 文件路径
 */
@property (nonatomic, copy) NSString* filePath;
/**
 oss的endpoint
 */
@property (nonatomic, copy) NSString* endpoint;
/**
 oss的bucket
 */
@property (nonatomic, copy) NSString* bucket;
/**
 oss的对象
 */
@property (nonatomic, copy) NSString* object;
/**
 vod具体信息
 */
@property (nonatomic, strong) VodInfo* vodInfo;
/**
 vod上传状态
 */
@property VODUploadFileStatus state;

@end

@class UploadStreamFileInfo;
/**
 流文件回调
 */
@protocol UploadStreamFileInfoDelegate <NSObject>
@optional
/**
 流文件大小发生改变
 @param fileInfo 流文件信息
 @param size 当前大小，Byte
 */
- (void) onUploadStreamFileInfo:(UploadStreamFileInfo *)fileInfo sizeChange:(NSUInteger)size;
/**
 上传进度发生改变
 @param fileInfo 流文件信息
 @param uploadSize 当前已经上传的大小，Byte
 */
- (void) onUploadStreamFileInfo:(UploadStreamFileInfo *)fileInfo uploadProgress:(NSUInteger)uploadSize;
@end

@interface UploadStreamFileInfo : UploadFileInfo
/**
 上传回调
 */
@property (nonatomic, weak) id<UploadStreamFileInfoDelegate> delegate;
/**
 分片大小，Byte，至少100KB
 */
@property (nonatomic, readonly) NSUInteger partSize;
/**
 首片分片大小，Byte，至少100KB
 */
@property (nonatomic, readonly) NSUInteger optimizeFirstPartSize;
/**
 当前文件偏移
 */
@property (nonatomic, readonly) NSUInteger currentOffset;
/**
 当前文件大小，Byte
 */
@property (nonatomic, readonly) NSUInteger currentSize;
/**
 当前文件是否已经完整
 */
@property (nonatomic, readonly) BOOL isFileComplete;
/**
 文件大小（byte)；文件完整前未确定
 */
@property (nonatomic, readonly) NSUInteger fileSize;
/**
 当前已经上传的大小（byte）
 */
@property (nonatomic, readonly) NSUInteger hasUploadedSize;

/**
 初始化流文件
 
 @param fileName 文件名
 @param partSize 分段大小
 @param firstPartSize 首段优化大小（默认可以跟partSize一样）
 */
- (instancetype) initWithFileName:(NSString *)fileName
                         partSize:(NSUInteger)partSize
            optimizeFirstPartSize:(NSUInteger)firstPartSize;

/**
 添加流数据
 
 @param buffer 流数据
 */
- (void) appendBuffer:(NSData *)buffer;

/**
 跳到某个位置
 
 @param offset 偏移位置
 */
- (void) seek:(NSUInteger)offset;

/**
 标记文件已经完成了（不再调用appendBuffer:）了
 */
- (void) fileComplete;
@end

@interface VodUploadResult: NSObject
@property (nonatomic, copy) NSString* videoId;
@property (nonatomic, copy) NSString* imageUrl;
@property (nonatomic, copy) NSString* bucket;
@property (nonatomic, copy) NSString* endpoint;
@end

typedef void (^OnUploadSucceedListener) (UploadFileInfo* fileInfo);

/**
 上传完成回调

 @param fileInfo 上传文件信息
 @param result 上传结果信息
 */
typedef void (^OnUploadFinishedListener) (UploadFileInfo* fileInfo, VodUploadResult* result);

/**
 上传失败回调

 @param fileInfo 上传文件信息
 @param code 错误码
 @param message 错误描述
 */
typedef void (^OnUploadFailedListener) (UploadFileInfo* fileInfo, NSString *code, NSString * message);

/**
 上传进度回调

 @param fileInfo 上传文件信息
 @param uploadedSize 已上传大小
 @param totalSize 总大小
 */
typedef void (^OnUploadProgressListener) (UploadFileInfo* fileInfo, long uploadedSize, long totalSize);

/**
 token过期回调
 上传地址和凭证方式上传需要调用resumeWithAuth:方法继续上传
 STS方式上传需要调用resumeWithToken:accessKeySecret:secretToken:expireTime:方法继续上传
 */
typedef void (^OnUploadTokenExpiredListener) ();

/**
 上传开始重试回调
 */
typedef void (^OnUploadRertyListener) ();

/**
 上传结束重试，继续上传回调
 */
typedef void (^OnUploadRertyResumeListener) ();

/**
 开始上传回调
 上传地址和凭证方式上传需要调用setUploadAuthAndAddress:uploadAuth:uploadAddress:方法设置上传地址和凭证
 @param fileInfo 上传文件信息
 */
typedef void (^OnUploadStartedListener) (UploadFileInfo* fileInfo);

@interface VODUploadListener : NSObject
@property (nonatomic, copy) OnUploadSucceedListener success
__attribute__((deprecated("", "use OnUploadFinishedListener to replace")));

@property (nonatomic, copy) OnUploadFinishedListener finish;
@property (nonatomic, copy) OnUploadFailedListener failure;
@property (nonatomic, copy) OnUploadProgressListener progress;
@property (nonatomic, copy) OnUploadTokenExpiredListener expire;
@property (nonatomic, copy) OnUploadRertyListener retry;
@property (nonatomic, copy) OnUploadRertyResumeListener retryResume;
@property (nonatomic, copy) OnUploadStartedListener started;

@end


@interface VODUploadModel : NSObject

@end
