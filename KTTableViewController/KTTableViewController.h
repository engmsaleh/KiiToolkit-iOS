//
//
// Copyright 2013 Kii Corporation
// http://kii.com
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//

#import <UIKit/UIKit.h>
#import "CKRefreshArrowView.h"

@class KiiQuery, KiiBucket, KiiObject;

/** 
 Implement the delegate methods to be notified of changes in the status
 */
@protocol KTTableViewDelegate <NSObject>
@optional

/** 
 Called when the query is beginning to execute
 */
- (void) tableDidStartLoading;

/**
 Called when the query has finished executing
 
 @param error If nil, the query was successful. Otherwise, something went wrong - check the error to find out what
 */
- (void) tableDidFinishLoading:(NSError*)error;
@end

@interface KTTableViewController : UITableViewController <UIScrollViewDelegate>

/** The query to be executed when the table view is loaded/refreshed */
@property (nonatomic, strong) KiiQuery *query;

/** The bucket to execute the query on in order to retrieve the data. Must be either a KiiBucket or a KiiFileBucket object */
@property (nonatomic, strong) id bucket;

/** The page size of the tableview. Default is undefined and determined by how many results are returned by the server */
@property (nonatomic, assign) int pageSize;

/** If pagination is enabled, when the user scrolls to the bottom of the page and more results exist, they will be loaded automatically. Default = YES */
@property (nonatomic, assign) BOOL paginationEnabled;

/** When enabled, pull-to-refresh will be available. This is available pre-iOS6 and the view is customizable via refreshNoticeView. Default = YES */
@property (nonatomic, assign) BOOL refreshControlEnabled;

#pragma mark - Refresh notice view

/** This view displays the pull-to-refresh arrow and text labels. Manipulate this view to customize the look of the pull-to-refresh mechanism */
@property (nonatomic, strong) UIView *refreshNoticeView;

/** A subview of refreshNoticeView, this label displays the pull-to-refresh text. Manipulate this view to customize the look of the pull-to-refresh mechanism */
@property (nonatomic, strong) UILabel *refreshNoticeLabel;

/** A subview of refreshNoticeView, this is the circular arrow that displays alongside the pull-to-refresh text. Manipulate this view to customize the look of the pull-to-refresh mechanism */
@property (nonatomic, strong) CKRefreshArrowView *loadingArrow;

/** Shown when the table view is refreshing, use this property to customize color, etc. */
@property (nonatomic, strong) UIActivityIndicatorView *refreshSpinner;

#pragma mark - Actions

/**
 Will refresh the table view, reloading the original query and populating the table's results once complete
 */
- (void) refreshQuery;

#pragma mark - Datasource methods

/**
 <b>This method must be overridden by your subclass!</b>
 
 @param tableView The tableview to which the cell will belong
 @param object The KiiObject or KiiFile that the cell will represent. Use the contents within this object to create the cell appropriately
 @param indexPath The index path where this cell will reside
 @return A UITableViewCell object
 */
- (UITableViewCell *)tableView:(UITableView *)tableView
              cellForKiiObject:(id)object
                   atIndexPath:(NSIndexPath*)indexPath;

@end
