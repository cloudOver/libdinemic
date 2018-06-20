Purpose of DAction and DActionFlag classes
==========================================
DAction class is designed to create own actions to react on database updates.
Each DAction instance could implement own methods:
 * on_create
 * on_created
 * on_update
 * on_updated
 * on_delete
 * on_deleted
 * on_remove
 * on_removed

To connect action with update types, it is necessary to call several methods
on SyncInterface object (add_on_..._listener). To avoid adding not implemented
listeners, one could override the apply and revoke methods, to apply add all
necessary listeners to the SyncInterface.

Each of listeners gets information about matched update. This information is
provided with the DActionFlags object.


DActionFlags class
==================
Information provided by DActionFlags should be used to obtain information
about update reveived by database node. All fields are automatically filled
by SyncInterface class. Most important flags are:
 * chained
 * verified
 * caller_id - ID of object, which created an update

If chained is set to True, it means that update was successfully verified in
chain of other updates. Usually it means, that hash of previous message
matches with one provided in update headers (DHeaders class, fields Previous
and Previous-Hash).

If the verified field is set to True, it means that caller has successfully
signed the updated by its own key. It DOES NOT mean, that update is authorized
to update an object. To verify it, the updated object name should be compared
with caller_id field and/or caller_id should be compared with authorized_keys
list in the object.


DAppHelpers namespace
=====================
This namespace provides several useful DAction classes, which could be used
to obtain the right behavior of application (i.e. to ignore unsigned updates).
