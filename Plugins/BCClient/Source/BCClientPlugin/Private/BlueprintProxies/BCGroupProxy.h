// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BrainCloudGroup.h"
#include "BCGroupProxy.generated.h"

class ABrainCloud;

class UBrainCloudGroupACL;

UCLASS(MinimalAPI)
class UBCGroupProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
	GENERATED_BODY()

public:
	UBCGroupProxy(const FObjectInitializer& ObjectInitializer);

	/**
	 * Accept an outstanding invitation to join the group.
	 *
	 * Service Name - group
	 * Service Operation - ACCEPT_GROUP_INVITATION
	 *
	 * Param - groupId ID of the group.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* AcceptGroupInvitation(ABrainCloud *brainCloud, const FString& groupId);

	/**
	 * Add a member to the group.
	 *
	 * Service Name - group
	 * Service Operation - ADD_GROUP_MEMBER
	 *
	 * Param - groupId ID of the group.
	 * Param - profileId Profile ID of the member being added.
	 * Param - role Role of the member being added.
	 * Param - jsonAttributes Attributes of the member being added.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* AddGroupMember(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes);

	/**
	 * Approve an outstanding request to join the group.
	 *
	 * Service Name - group
	 * Service Operation - APPROVE_GROUP_JOIN_REQUEST
	 *
	 * Param - groupId ID of the group.
	 * Param - profileId Profile ID of the invitation being deleted.
	 * Param - role Role of the member being invited.
	 * Param - jsonAttributes Attributes of the member being invited.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* ApproveGroupJoinRequest(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes);

	/**
	* Automatically join an open group that matches the search criteria and has space available.
	*
	* Service Name - group
	* Service Operation - AUTO_JOIN_GROUP
	*
	* Param - groupType Name of the associated group type.
	* Param - autoJoinStrategy Selection strategy to employ when there are multiple matches
	* Param - dataQueryJson Query parameters (optional)
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* AutoJoinGroup(ABrainCloud *brainCloud, const FString& groupType, EAutoJoinStrategy autoJoinStrategy, const FString& dataQueryJson);

	/**
	 * Cancel an outstanding invitation to the group.
	 *
	 * Service Name - group
	 * Service Operation - CANCEL_GROUP_INVITATION
	 *
	 * Param - groupId ID of the group.
	 * Param - profileId Profile ID of the invitation being deleted.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* CancelGroupInvitation(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId);

	/**
	 * Create a group.
	 *
	 * Service Name - group
	 * Service Operation - CREATE_GROUP
	 *
	 * Param - name Name of the group.
	 * Param - groupType Name of the type of group.
	 * Param - isOpenGroup true if group is open; false if closed.
	 * Param - acl The group's access control list. A null ACL implies default.
	 * Param - jsonOwnerAttributes Attributes for the group owner (current player).
	 * Param - jsonDefaultMemberAttributes Default attributes for group members.
	 * Param - jsonData Custom application data.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* CreateGroup(
			ABrainCloud *brainCloud,
			const FString& name,
			const FString& type,
			bool isOpenGroup,
			UBrainCloudGroupACL* acl,
			const FString& jsonData,
			const FString& jsonOwnerAttributes,
			const FString& jsonDefaultMemberAttributes);

	/**
	 * Create a group entity.
	 *
	 * Service Name - group
	 * Service Operation - CREATE_GROUP_ENTITY
	 *
	 * Param - groupId ID of the group.
	 * Param - isOwnedByGroupMember true if entity is owned by a member; false if owned by the entire group.
	 * Param - entityType Type of the group entity.
	 * Param - acl Access control list for the group entity.
	 * Param - jsonData Custom application data.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* CreateGroupEntity(
			ABrainCloud *brainCloud,
			const FString& groupId,
			const FString& entityType,
			bool isOwnedByGroupMember,
			UBrainCloudGroupACL* acl,
			const FString& jsonData);

	/**
	 * Delete a group.
	 *
	 * Service Name - group
	 * Service Operation - DELETE_GROUP
	 *
	 * Param - groupId ID of the group.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* DeleteGroup(ABrainCloud *brainCloud, const FString& groupId, int32 version);

	/**
	 * Delete a group entity.
	 *
	 * Service Name - group
	 * Service Operation - DELETE_GROUP_ENTITY
	 *
	 * Param - groupId ID of the group.
	 * Param - entityId ID of the entity.
	 * Param - version The current version of the group entity (for concurrency checking).
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* DeleteGroupEntity(ABrainCloud *brainCloud, const FString& groupId, const FString& entityId, int32 version);

	/**
	 * Read information on groups to which the current player belongs.
	 *
	 * Service Name - group
	 * Service Operation - GET_MY_GROUPS
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* GetMyGroups(ABrainCloud *brainCloud);

	/**
	 * Increment elements for the group's data field.
	 *
	 * Service Name - group
	 * Service Operation - INCREMENT_GROUP_DATA
	 *
	 * Param - groupId ID of the group.
	 * Param - jsonData Partial data map with incremental values.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* IncrementGroupData(ABrainCloud *brainCloud, const FString& groupId, const FString& jsonData);

	/**
	 * Increment elements for the group entity's data field.
	 *
	 * Service Name - group
	 * Service Operation - INCREMENT_GROUP_ENTITY_DATA
	 *
	 * Param - groupId ID of the group.
	 * Param - entityId ID of the entity.
	 * Param - jsonData Partial data map with incremental values.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* IncrementGroupEntityData(ABrainCloud *brainCloud, const FString& groupId, const FString& entityId, const FString& jsonData);

	/**
	 * Invite a member to the group.
	 *
	 * Service Name - group
	 * Service Operation - INVITE_GROUP_MEMBER
	 *
	 * Param - groupId ID of the group.
	 * Param - profileId Profile ID of the member being invited.
	 * Param - role Role of the member being invited.
	 * Param - jsonAttributes Attributes of the member being invited.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* InviteGroupMember(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes);

	/**
	 * Join an open group or request to join a closed group.
	 *
	 * Service Name - group
	 * Service Operation - JOIN_GROUP
	 *
	 * Param - groupId ID of the group.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* JoinGroup(ABrainCloud *brainCloud, const FString& groupId);

	/**
	 * Leave a group in which the player is a member.
	 *
	 * Service Name - group
	 * Service Operation - LEAVE_GROUP
	 *
	 * Param - groupId ID of the group.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* LeaveGroup(ABrainCloud *brainCloud, const FString& groupId);

	/**
	 * Read a page of group information.
	 *
	 * Service Name - group
	 * Service Operation - LIST_GROUPS_PAGE
	 *
	 * Param - context Query context.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* ListGroupsPage(ABrainCloud *brainCloud, const FString& jsonContext);

	/**
	 * Read a page of group information.
	 *
	 * Service Name - group
	 * Service Operation - LIST_GROUPS_PAGE_BY_OFFSET
	 *
	 * Param - encodedContext Encoded reference query context.
	 * Param - offset Number of pages by which to offset the query.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* ListGroupsPageByOffset(ABrainCloud *brainCloud, const FString& context, int32 pageOffset);

	/**
	 * Read information on groups to which the specified player belongs.  Access is subject to restrictions.
	 *
	 * Service Name - group
	 * Service Operation - LIST_GROUPS_WITH_MEMBER
	 *
	 * Param - profileId
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* ListGroupsWithMember(ABrainCloud *brainCloud, const FString& profileId);

	/**
	 * Read the specified group.
	 *
	 * Service Name - group
	 * Service Operation - READ_GROUP
	 *
	 * Param - groupId ID of the group.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* ReadGroup(ABrainCloud *brainCloud, const FString& groupId);

	/**
	* Read the specified group's data.
	*
	* Service Name - group
	* Service Operation - READ_GROUP_DATA
	*
	* Param - groupId ID of the group.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* ReadGroupData(ABrainCloud *brainCloud, const FString& groupId);

	/**
	 * Read a page of group entity information.
	 *
	 * Service Name - group
	 * Service Operation - READ_GROUP_ENTITIES_PAGE
	 *
	 * Param - context Query context.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* ReadGroupEntitiesPage(ABrainCloud *brainCloud, const FString& jsonContext);

	/**
	 * Read a page of group entity information.
	 *
	 * Service Name - group
	 * Service Operation - READ_GROUP_ENTITIES_PAGE_BY_OFFSET
	 *
	 * Param - encodedContext Encoded reference query context.
	 * Param - offset Number of pages by which to offset the query.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* ReadGroupEntitiesPageByOffset(ABrainCloud *brainCloud, const FString& context, int32 pageOffset);

	/**
	 * Read the specified group entity.
	 *
	 * Service Name - group
	 * Service Operation - READ_GROUP_ENTITY
	 *
	 * Param - groupId ID of the group.
	 * Param - entityId ID of the entity.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* ReadGroupEntity(ABrainCloud *brainCloud, const FString& groupId, const FString& entityId);

	/**
	 * Read the members of the group.
	 *
	 * Service Name - group
	 * Service Operation - READ_MEMBERS_OF_GROUP
	 *
	 * Param - groupId ID of the group.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* ReadGroupMembers(ABrainCloud *brainCloud, const FString& groupId);

	/**
	 * Reject an outstanding invitation to join the group.
	 *
	 * Service Name - group
	 * Service Operation - REJECT_GROUP_INVITATION
	 *
	 * Param - groupId ID of the group.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* RejectGroupInvitation(ABrainCloud *brainCloud, const FString& groupId);

	/**
	 * Reject an outstanding request to join the group.
	 *
	 * Service Name - group
	 * Service Operation - REJECT_GROUP_JOIN_REQUEST
	 *
	 * Param - groupId ID of the group.
	 * Param - profileId Profile ID of the invitation being deleted.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* RejectGroupJoinRequest(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId);

	/**
	 * Remove a member from the group.
	 *
	 * Service Name - group
	 * Service Operation - REMOVE_GROUP_MEMBER
	 *
	 * Param - groupId ID of the group.
	 * Param - profileId Profile ID of the member being deleted.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* RemoveGroupMember(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId);

	/**
	 * Updates a group's data.
	 *
	 * Service Name - group
	 * Service Operation - UPDATE_GROUP_DATA
	 *
	 * Param - groupId ID of the group.
	 * Param - version Version to verify.
	 * Param - jsonData Data to apply.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* UpdateGroupData(ABrainCloud *brainCloud, const FString& groupId, int32 version, const FString& jsonData);

	/**
	 * Update a group entity.
	 *
	 * Service Name - group
	 * Service Operation - UPDATE_GROUP_ENTITY_DATA
	 *
	 * Param - groupId ID of the group.
	 * Param - entityId ID of the entity.
	 * Param - version The current version of the group entity (for concurrency checking).
	 * Param - jsonData Custom application data.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* UpdateGroupEntityData(ABrainCloud *brainCloud, const FString& groupId, const FString& entityId, int32 version, const FString& jsonData);

	/**
	 * Update a member of the group.
	 *
	 * Service Name - group
	 * Service Operation - UPDATE_GROUP_MEMBER
	 *
	 * Param - groupId ID of the group.
	 * Param - profileId Profile ID of the member being updated.
	 * Param - role Role of the member being updated (optional).
	 * Param - jsonAttributes Attributes of the member being updated (optional).
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* UpdateGroupMember(ABrainCloud *brainCloud, const FString& groupId, const FString& profileId, ERole role, const FString& jsonAttributes);

	/**
	 * Updates a group's name.
	 *
	 * Service Name - group
	 * Service Operation - UPDATE_GROUP_NAME
	 *
	 * Param - groupId ID of the group.
	 * Param - name Name to apply.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Group")
		static UBCGroupProxy* UpdateGroupName(ABrainCloud *brainCloud, const FString& groupId, const FString& name);

	//Response delegates
	UPROPERTY(BlueprintAssignable)
		FBrainCloudCallbackDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FBrainCloudCallbackDelegate OnFailure;

protected:
	// IServerCallback interface
	void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
	void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
	// End of IServerCallback interface
};
