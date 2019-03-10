/*!
  ISptEntryExt.h
  SptIMCoreIOS

  Copyright © 2018 ClearOne Inc. All rights reserved.
*/

#import "ISptTypes.h"

@class ISptRoomData;
@class SptSchMeeting;
@class ISptContactData;




/*!
 @class SptEntryField
 Entry field, it can be one entry in an agenda or notes
 */
@interface SptEntryField : NSObject

/*!
 Entry ID
 */
@property (readonly) SptEntryID entryID;
/*!
 Entry text
 */
@property (readonly) NSString *entryText;

@end

/*!
 @class SptEntryCollection
 A collection of entries
 */
@interface SptEntryCollection : NSObject

/*!
 Type of entry

 - kEntryTypeInvalid: Invalid entry type
 - kEntryTypeAgenda: Agenda entry type
 - kEntryTypeNote: Note entry type
 */
typedef NS_ENUM(NSUInteger, SptEntryType){
    kEntryTypeInvalid,
    kEntryTypeAgenda,
    kEntryTypeNote
};

/*!
 Type of entry
 */
@property (readonly) SptEntryType type;

/*!
 An NSArray of SptEntryField with the entries collection
 */
@property (readonly) NSArray *entries;

@end


/*!
 @class SptManageEntryCollection
 Manage entry colectiopn
 Add, remove and modify entries in an Agenda or notes
 */
@interface SptManageEntryCollection : NSObject

/*!
 Add a new entry

 @param entry Text of the entry to add
 @return YES in case of success, NO otherwise
 */
-(BOOL)addNewEntry:(NSString *)entry;
/*!
 Remove an entry

 @param entryID Entry ID to remove
 @return YES in case of success, NO otherwise
 */
-(BOOL)removeEntry:(SptEntryID)entryID;

/*!
 Modify an existing entry

 @param entryID Entry ID to modify
 @param newEntry Text to set
 @return YES in case of success, NO otherwise
 */
-(BOOL)modifyEntry:(SptEntryID)entryID text:(NSString *)newEntry;
@end

/*!
 @class SptSchManageEntryCollection
 Manage an entry collection in a meeting
 */
@interface SptSchManageEntryCollection : SptManageEntryCollection
/*!
 Create a manage entry collection object

 @param seqID Meeting sequence ID
 @param meetingID Meeting ID
 @param entryType Type of entries to manage
 @return Created object
 */
+(instancetype) withData:(SptMeetingSeqID)seqID
                 meeting:(SptMeetingID)meetingID
                    type:(SptEntryType)entryType;


@end

/*!
 @class SptRoomManageEntryCollection
 Manage an entry collection in a chat or channel
 */
@interface SptRoomManageEntryCollection : SptManageEntryCollection
/*!
 Create a manage entry collection object

 @param roomID Room ID
 @return created object
 */
+(instancetype) withData:(SptIMRoomID)roomID;
@end




/*!
 @class SptToDo
 ToDo data
 */
@interface SptToDo : SptEntryField
/*!
 Type of ToDo

 - kSptInvalidTodo: Invalid ToDo note
 - kSptPersonalTodo: Personal ToDo
 - kSptRoomTodo: Room ToDo
 - kSptMeetingTodo: Meeting ToDo
 */
typedef NS_ENUM(NSUInteger, SptToDoType){
    kSptInvalidTodo,
    kSptPersonalTodo,
    kSptRoomTodo,
    kSptMeetingTodo
};
/*!
 ToDo type
 */
@property (readonly) SptToDoType todoType;
/*!
 A NSArray of ISptContactData with the assigned contacts, nil in case assigned to everybody
 */
@property (readonly) NSArray *assignedTo;

/*!
 A NSArray of NSNumber with the assigned contacts, nil in case assigned to everybody
 */
@property (readonly) NSArray *assignedToIDs;
/*!
 Assigner contact data
 */
@property (readonly) ISptContactData *assignedBy;
/*!
 Yes in case is done, No in case pending
 */
@property (readonly) bool done;
/*!
 Due date, nil in case not set
 */
@property (readonly) NSDate *dueDate;
/*!
 Created date in local time
 */
@property (readonly) NSDate *createdDate;
/*!
 In case ToDo belong to a room, room ID
 */
@property (readonly) SptIMRoomID roomID;
/*!
 In case ToDo belong to a meeting, meeting sequence ID
 */
@property (readonly) SptMeetingSeqID seqID;
/*!
 In case ToDo belong to a meeting, meeting ID
 */
@property (readonly) SptMeetingID meetingID;

@end



/*!
 @class SptModifyToDoCollection
 Modify a ToDo collection
 You can add, remove and modify ToDos
 */
@interface SptModifyToDoCollection : NSObject

/*!
 Modify Personal ToDos

 @return instance object
 */
+(instancetype)initWithPersonalToDos;

/*!
 Modify room ToDos

 @param roomID Room ID
 @return instace object
 */
+(instancetype)initWithRoomData:(SptIMRoomID)roomID;
/*!
 Modify meeting ToDos

 @param seqID Meeting sequence ID
 @param meetingID Meeting ID
 @return instance object
 */
+(instancetype)initWithMeetingData:(SptMeetingSeqID)seqID
                           meeting:(SptMeetingID)meetingID;

/*!
 Modify a ToDo

 @param entryID Entry ID of the ToDo to modify
 @param todoText New ToDo text, set it to nil to keep current text
 @param done YES in case done, No in case pending
 @param assignedTo An NSArray of Contacts ID with the assigned contact IDs, set it to nil to keep current assigned, set it empty in case you want to assign it to everybodt
 @param date Due data, set it to nil in case not set
 */
-(void)modifyTodo:(SptEntryID)entryID
             text:(NSString *)todoText
           isDone:(BOOL)done
         assingTo:(NSArray *)assignedTo
          dueDate:(NSDate *)date;

/*!
 Add a new ToDo

 @param todoText Text of the ToDo
 @param done YES in case of done, NO in case of pending
 @param assignedTo NSArray with the assigned contact IDs, nil in case assign to everybody
 @param date Due date, nil in case not set
 */
-(void)addNewToDo:(NSString *)todoText
           isDone:(BOOL)done
         assingTo:(NSArray *)assignedTo
          dueDate:(NSDate *)date;

/*!
 Remove a ToDo

 @param entryID Entry ID of the ToDo to remove
 */
-(void)removeToDo:(SptEntryID)entryID;

@end



