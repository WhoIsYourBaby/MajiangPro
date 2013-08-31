//
//  IOSHelper.m
//  MaJiong
//
//  Created by HalloWorld on 13-1-4.
//
//

#import "IOSHelper.h"

static IOSHelper *helperInterface = nil;

@implementation IOSHelper
- (id)init
{
    self = [super init];
    if (self) {
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    }
    return self;
}

+ (id)shareInterface
{
    if (helperInterface == nil) {
        helperInterface = [[IOSHelper alloc] init];
    }
    return helperInterface;
}

- (void)dealloc
{
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
    [super dealloc];
}

- (void)getProductInfo {
    NSSet * set = [NSSet setWithArray:@[@"com.majiang.iad"]];
    SKProductsRequest * request = [[SKProductsRequest alloc] initWithProductIdentifiers:set];
    request.delegate = self;
    [request start];
    [request release];
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
    NSArray *myProduct = response.products;
    if (myProduct.count == 0) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"无法获取产品信息,购买失败" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alert show];
        [alert release];
        return;
    }
    SKPayment * payment = [SKPayment paymentWithProduct:[myProduct objectAtIndex:0]];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions {
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased://交易完成
                NSLog(@"transactionIdentifier = %@", transaction.transactionIdentifier);
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStateFailed://交易失败
                [self failedTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored://已经购买过该商品
                [self restoreTransaction:transaction];
                break;
            case SKPaymentTransactionStatePurchasing:      //商品添加进列表
                NSLog(@"商品添加进列表");
                break;
            default:
                break;
        }
    }
}

- (void)completeTransaction:(SKPaymentTransaction *)transaction {
    // Your application should implement these two methods.
    NSString * productIdentifier = transaction.payment.productIdentifier;
//    NSString * receipt = [transaction.transactionReceipt base64EncodedString];
    if ([productIdentifier length] > 0) {
        // 向自己的服务器验证购买凭证
    }
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"noiad"];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"noiad" object:nil];
    // Remove the transaction from the payment queue.
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}
- (void)failedTransaction:(SKPaymentTransaction *)transaction {
    if(transaction.error.code != SKErrorPaymentCancelled) {
        NSLog(@"购买失败");
    } else {
        NSLog(@"用户取消交易");
    }
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}
- (void)restoreTransaction:(SKPaymentTransaction *)transaction {
    // 对于已购商品，处理恢复购买的逻辑
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"noiad"];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"noiad" object:nil];
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0) {
        [[IOSHelper shareInterface] getProductInfo];
    } else {
        [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
    }
}

#pragma mark - Actions
+(void)buyNoIad
{
    if ([SKPaymentQueue canMakePayments]) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:nil delegate:[IOSHelper shareInterface] cancelButtonTitle:@"Buy" otherButtonTitles:@"Restore", nil];
        [alert show];
        [alert release];
    } else {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"失败,用户禁止应用内付费购买." delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alert show];
        [alert release];
    }
}

@end
