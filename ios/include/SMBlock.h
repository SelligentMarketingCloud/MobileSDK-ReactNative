//
//  SMBlock.h
//  MobileSDK
//
//  Created by Gauthier Dumont on 23/06/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//



/**
 *  @typedef type of block that will be triggered when an event has been succesfully sent
 *  @param success a SMSuccess object
 */
typedef void(^SMCompletionBlockSuccess)(SMSuccess *_Nullable success);

/**
 *  @typedef type of block that will be triggered when an event has failed to be sent
 *  @param failure a SMFailure failure
 */
typedef void(^SMCompletionBlockFailure)(SMFailure *_Nullable failure);
