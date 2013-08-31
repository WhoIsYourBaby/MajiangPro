//
//  WeiboShareManager.h
//  MaJiong
//
//  Created by Kira on 8/1/13.
//
//

#import <Foundation/Foundation.h>


#define kAppKey             @"2053366422"
#define kAppSecret          @"9d402599d673bee313ccf5a702d31288"
#define kAppRedirectURI     @"https://api.weibo.com/oauth2/default.html"

#ifndef kAppKey
#error
#endif

#ifndef kAppSecret
#error
#endif

#ifndef kAppRedirectURI
#error
#endif

#import "SinaWeibo.h"

@interface WeiboShareManager : NSObject <SinaWeiboDelegate, SinaWeiboRequestDelegate>
{
    SinaWeibo *sinaweibo;
}

+ (void)LoginAndShareSina;

+ (void)LoginAndShareTwitter;

@end