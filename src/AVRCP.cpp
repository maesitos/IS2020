#include "IS2020.h"
#include "AVRCP.h"
#include <Arduino.h>

uint8_t  IS2020::avrcpGetCapabilities(uint8_t deviceId, uint8_t capId) {
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Get_Capability_command_for_Events\n"));
  uint8_t data[5] = {AVRCP_GET_CAPABILITIES, //6
                     0x00, //7 Reserved
                     0x00, 0x01, // 8-9 D => 13 bytes
                     capId //0x02 company ID, 0x03 EventsID
                    }; //23,24,25,26
  IS2020::sendPacketArrayInt(7, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpListPlayerAttributes(uint8_t deviceId) {
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_List_Player_Attributes\n"));
  uint8_t data[5] = {AVRCP_LIST_PLAYER_ATTRIBUTES, //6
                     0x00, //7 Reserved
                     0x00, 0x01,
                     0x00
                    };
  IS2020::sendPacketArrayInt(7, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpListPlayerValues(uint8_t deviceId, uint8_t attribute) {
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_List_Player_Values\n"));
  uint8_t data[5] = {AVRCP_LIST_PLAYER_VALUES, //6
                     0x00, //7 Reserved
                     0x00, 0x01,
                     attribute
                    };
  IS2020::sendPacketArrayInt(7, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}
/*

*/
uint8_t  IS2020::avrcpGetCurrentPlayerValue(uint8_t deviceId, uint8_t attribute) {
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Get_Current_Player_Value\n"));
  uint8_t data[5] = {AVRCP_GET_CURRENT_PLAYER_VALUE, //6
                     0x00, //7 Reserved
                     0x00, 0x01, //size
                     attribute
                    };
  IS2020::sendPacketArrayInt(7, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpSetPlayerValue(uint8_t deviceId, uint8_t attribute, uint8_t value) {
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Set_Player_Value\n"));
  uint8_t data[6] = {AVRCP_SET_PLAYER_VALUE, //6
                     0x00, //7 Reserved
                     0x00, 0x02, //size
                     attribute, value
                    };
  IS2020::sendPacketArrayInt(8, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpGetPlayerAttributeText(uint8_t deviceId, uint8_t attribute) {
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Get_Player_Attribute_Text\n"));
  uint8_t data[5] = {AVRCP_GET_PLAYER_ATTRIBUTE_TEXT, //6
                     0x00, //7 Reserved
                     0x00, 0x01, //size
                     attribute
                     /*0x01,0x02,0x03,0x04*/
                    };
  IS2020::sendPacketArrayInt(7, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpGetPlayerValueText(uint8_t deviceId, uint8_t attribute, uint8_t setting) {
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Get_Player_Value_Text\n"));
  uint8_t data[7] = {AVRCP_GET_PLAYER_VALUE_TEXT, //6
                     0x00, //7 Reserved
                     0x00, 0x01, //size
                     attribute,
                     0x01,
                     setting
                    };
  IS2020::sendPacketArrayInt(9, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpDisplayableCharset(uint8_t deviceId) {
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Displayable_Charset\n"));
  uint8_t data[6] = {AVRCP_DISPLAYABLE_CHARSET, //6
                     0x00, //7 Reserved
                     0x00, 0x02, //size
                     0x00, 0x6A//0x6A - vincent
                    };
  IS2020::sendPacketArrayInt(8, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpGetElementAttributes(uint8_t deviceId) {
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP Get element attributes command\n"));
//thx to Vincent Gijsen
// https://github.com/VincentGijsen/MelbusRtos/blob/3d812d4549950435f2c2a302021bebe854f464c5/src/IS2020/AVRCP.c#L37
	uint8_t data[] = {
				AVRCP_GET_ELEMENT_ATTRIBUTES,
				0,
				0,0x0d,
				0,0,0,0,
				1,
				0,0,0,0,0,0,0,1,
	};
//	size_t s = sizeof(data) / sizeof(uint8_t);
//	uint8_t pkgLen = s + 2;
  IS2020::sendPacketArrayInt(/*pkgLen*/19, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpGetElementAttributesAll(uint8_t deviceId) {
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Get_Element_Attributes\n"));
  uint8_t data[5] = {AVRCP_GET_ELEMENT_ATTRIBUTES, //1
                      0x00, //2
                      0x00,0x01,0x00/*, 9, //3,4 - size after this
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //1,2,3,4 5,6,7,8
                      0x00*/
                     };
  IS2020::sendPacketArrayInt(7, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpGetPlayStatus(uint8_t deviceId) {
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Get_Element_Attributes\n"));
  uint8_t data[3] = {AVRCP_GET_PLAY_STATUS, //command
                      0x00, //reserved
                      0x00//, 0x00
                     };
  IS2020::sendPacketArrayInt(5, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpRegistrationForNotificationOfEvent(uint8_t deviceId, uint8_t event, uint8_t param1, uint8_t param2, uint8_t param3, uint8_t param4) {
  IS2020::getNextEventFromBt();
  uint8_t data[9] = {AVRCP_REGISTER_NOTIFICATION, //PDU ID (0x31 – Register Notification)
                     0x00, //reserved
                     0x00, 0x05, // Parameter Length (0x5)
                     event, //EventID
                     param1, param2, param3, param4
                    };
  IS2020::sendPacketArrayInt(11, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
  IS2020::getNextEventFromBt(); IS2020::getNextEventFromBt(); IS2020::getNextEventFromBt();
}


uint8_t  IS2020::avrcpRequestContinuing(uint8_t deviceId, uint8_t pdu){
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Request_Continuing\n"));
  uint8_t data[5] = {AVRCP_REQUEST_CONTINUING, //1
                      0x00, //2
                      0x00, 0x01,
                      pdu
                     };
  IS2020::sendPacketArrayInt(7, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpAbortContinuing(uint8_t deviceId, uint8_t pdu){
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Abort_Continuing\n"));
  uint8_t data[5] = {AVRCP_ABORT_CONTINUING, //1
                      0x00, //2
                      0x00, 0x01,
                      pdu
                     };
  IS2020::sendPacketArrayInt(7, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpSetAbsoluteVolume(uint8_t deviceId, uint8_t volume){
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Set_Absolute_Volume\n"));
  uint8_t data[5] = {AVRCP_SET_ABSOLUTE_VOLUME, //1
                      0x00, //2
                      0x00, 0x01,
                      volume
                     };
  IS2020::sendPacketArrayInt(7, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpSetAddressedPlayer(uint8_t deviceId, uint16_t player){
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Set_Addressed_Player\n"));
  uint8_t data[6] = {ACRCP_SET_ADDRESSED_PLAYER, //1
                      0x00, //2
                      0x00, 0x02,
                      ((player>>8) & 0xFF),(player & 0xFF)
                     };
  IS2020::sendPacketArrayInt(8, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpSetBrowsedPlayer(uint8_t deviceId, uint16_t player){
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Set_Addressed_Player\n"));
  uint8_t data[6] = {AVRCP_SET_BROWSED_PLAYER, //1
                      0x00, //2
                      0x00, 0x02,
                      ((player>>8) & 0xFF),(player & 0xFF)
                     };
  IS2020::sendPacketArrayInt(8, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpGetFolderItems(uint8_t deviceId, uint8_t scope, uint32_t start,uint8_t end){
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Set_Addressed_Player\n"));
  uint8_t data[14] = {AVRCP_GET_FOLDER_ITEMS, //1
                      0x00, //2,
                      0x00, 0x0B,
                      scope, //scope
                      ((start>>14)&0xFF),((start>>16)&0xFF),((start>>8)&0xFF),(start&0xFF),//start
                      ((end>>14)&0xFF),((end>>16)&0xFF),((end>>8)&0xFF),(end&0xFF),//end
                      0x00
                     };
  IS2020::sendPacketArrayInt(16, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

uint8_t  IS2020::avrcpChangePath(uint8_t deviceId, uint8_t direction, uint64_t folderUID){
  IS2020::getNextEventFromBt();
  IS2020::DBG_AVRCP(F("AVRCP_Set_Addressed_Player\n"));
  uint8_t data[15] = {AVRCP_GET_FOLDER_ITEMS, //1
                      0x00, //2,
                      0x00, 0x0B,//Parameter Length
                      0x12,0x34, //UID Counter
                      direction,//Direction: 0x01 (Folder Down)
                     // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05//Folder UID:
                      ((folderUID>>56)&0xFF),((folderUID>>48)&0xFF),((folderUID>>40)&0xFF),((folderUID>>32)&0xFF),
                      ((folderUID>>24)&0xFF),((folderUID>>16)&0xFF),((folderUID>>8)&0xFF),(folderUID&0xFF)
                     };
  IS2020::sendPacketArrayInt(16, CMD_AVRCP_Specific_Cmd, deviceId, data);
  return checkResponce(EVT_Command_ACK);
}

void IS2020::registerAllEvents(uint8_t deviceId) {}

uint8_t IS2020::avrcpRegNotifyPlaybackStatusChanged(uint8_t deviceId){
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_PLAYBACK_STATUS_CHANGED, 0x00, 0x00, 0x00, 0x00);
}

uint8_t IS2020::avrcpRegNotifyTrackChanged(uint8_t deviceId){
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_TRACK_CHANGED, 0x00, 0x00, 0x00, 0x00);
}

uint8_t IS2020::avrcpRegNotifyTrackReachedEnd(uint8_t deviceId){
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_TRACK_REACHED_END, 0x00, 0x00, 0x00, 0x00);
}

uint8_t IS2020::avrcpRegNotifyTrackReachedStart(uint8_t deviceId){
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_TRACK_REACHED_START, 0x00, 0x00, 0x00, 0x00);
}

uint8_t IS2020::avrcpRegNotifyTrackPositionChanged(uint8_t deviceId,uint8_t interval){//interval in seconds
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_PLAYBACK_POS_CHANGED, 0x00, 0x00,0x13, 0x88);
}

uint8_t IS2020::avrcpRegNotifyBattStatusChanged(uint8_t deviceId){
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_BATT_STATUS_CHANGED, 0x00, 0x00, 0x00, 0x00);
}

uint8_t IS2020::avrcpRegNotifySystemStatusChanged(uint8_t deviceId){
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_SYSTEM_STATUS_CHANGED, 0x00, 0x00, 0x00, 0x00);
}

uint8_t IS2020::avrcpRegNotifyPlayerAppSettingsChanged(uint8_t deviceId){
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_PLAYER_APPLICATION_SETTING_CHANGED, 0x00, 0x00, 0x00, 0x00);
}

uint8_t IS2020::avrcpRegNotifyNowPlayingContentChanged(uint8_t deviceId){
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_NOW_PLAYING_CONTENT_CHANGED, 0x00, 0x00, 0x00, 0x00);
}

uint8_t IS2020::avrcpRegNotifyAvailablePlayersChanged(uint8_t deviceId){
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_AVAILABLE_PLAYERS_CHANGED, 0x00, 0x00, 0x00, 0x00);
}

uint8_t IS2020::avrcpRegNotifyAddressedPlayerChanged(uint8_t deviceId){
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_ADDRESSED_PLAYER_CHANGED, 0x00, 0x00, 0x00, 0x00);
}

uint8_t IS2020::avrcpRegNotifyUIDsChanged(uint8_t deviceId){
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_UIDS_CHANGED, 0x00, 0x00, 0x00, 0x00);
}

uint8_t IS2020::avrcpRegNotifyVolumeChanged(uint8_t deviceId){
  IS2020::avrcpRegistrationForNotificationOfEvent(deviceId, AVRCP_EVENT_VOLUME_CHANGED, 0x00, 0x00, 0x00, 0x00);
}



void IS2020::decodeAvrcpPdu(uint8_t pdu) {
  DBG_AVRCP(F("Decoded PDU event: "));
  switch (pdu)
  {
    /* PDU types for metadata transfer */
    case AVRCP_GET_CAPABILITIES:
      IS2020::DBG_AVRCP(F("AVRCP_GET_CAPABILITIES"));
      break;
    case AVRCP_LIST_PLAYER_ATTRIBUTES:
      IS2020::DBG_AVRCP(F("AVRCP_LIST_PLAYER_ATTRIBUTES"));
      break;
    case AVRCP_LIST_PLAYER_VALUES:
      IS2020::DBG_AVRCP(F("AVRCP_LIST_PLAYER_VALUES"));
      break;
    case AVRCP_GET_CURRENT_PLAYER_VALUE:
      IS2020::DBG_AVRCP(F("AVRCP_GET_CURRENT_PLAYER_VALUE"));
      break;
    case AVRCP_SET_PLAYER_VALUE :
      IS2020::DBG_AVRCP(F("AVRCP_SET_PLAYER_VALUE"));
      break;
    case AVRCP_GET_PLAYER_ATTRIBUTE_TEXT:
      IS2020::DBG_AVRCP(F("AVRCP_GET_PLAYER_ATTRIBUTE_TEXT"));
      break;
    case AVRCP_GET_PLAYER_VALUE_TEXT:
      IS2020::DBG_AVRCP(F("AVRCP_GET_PLAYER_VALUE_TEXT"));
      break;
    case AVRCP_DISPLAYABLE_CHARSET:
      IS2020::DBG_AVRCP(F("AVRCP_DISPLAYABLE_CHARSET"));
      break;
    case AVRCP_CT_BATTERY_STATUS:
      IS2020::DBG_AVRCP(F("AVRCP_CT_BATTERY_STATUS"));
      break;
    case AVRCP_GET_ELEMENT_ATTRIBUTES:
      IS2020::DBG_AVRCP(F("AVRCP_GET_ELEMENT_ATTRIBUTES"));
      break;
    case AVRCP_GET_PLAY_STATUS:
      IS2020::DBG_AVRCP(F("AVRCP_GET_PLAY_STATUS"));
      break;
    case AVRCP_REGISTER_NOTIFICATION:
      IS2020::DBG_AVRCP(F("AVRCP_REGISTER_NOTIFICATION"));
      break;
    case AVRCP_REQUEST_CONTINUING:
      IS2020::DBG_AVRCP(F("AVRCP_REQUEST_CONTINUING"));
      break;
    case AVRCP_ABORT_CONTINUING:
      IS2020::DBG_AVRCP(F("AVRCP_ABORT_CONTINUING"));
      break;
    case AVRCP_SET_ABSOLUTE_VOLUME:
      IS2020::DBG_AVRCP(F("AVRCP_SET_ABSOLUTE_VOLUME"));
      break;
    case ACRCP_SET_ADDRESSED_PLAYER:
      IS2020::DBG_AVRCP(F("ACRCP_SET_ADDRESSED_PLAYER"));
      break;
    case AVRCP_SET_BROWSED_PLAYER:
      IS2020::DBG_AVRCP(F("AVRCP_SET_BROWSED_PLAYER"));
      break;
    case AVRCP_GET_FOLDER_ITEMS:
      IS2020::DBG_AVRCP(F("AVRCP_GET_FOLDER_ITEMS"));
      break;
    case AVRCP_CHANGE_PATH:
      IS2020::DBG_AVRCP(F("AVRCP_CHANGE_PATH"));
      break;
    case AVRCP_GET_ITEM_ATTRIBUTES:
      IS2020::DBG_AVRCP(F("AVRCP_GET_ITEM_ATTRIBUTES"));
      break;
    case AVRCP_PLAY_ITEM:
      IS2020::DBG_AVRCP(F("AVRCP_PLAY_ITEM"));
      break;
    case AVRCP_SEARCH:
      IS2020::DBG_AVRCP(F("AVRCP_SEARCH"));
      break;
    case AVRCP_ADD_TO_NOW_PLAYING:
      IS2020::DBG_AVRCP(F("AVRCP_ADD_TO_NOW_PLAYING"));
      break;
    case AVRCP_GENERAL_REJECT:
      IS2020::DBG_AVRCP(F("AVRCP_GENERAL_REJECT"));
      break;
    default:
      DBG_AVRCP(F("Unknown: ")); DBG(String(pdu, HEX));
  }
//  DBG_AVRCP(F("\n"));
}


void IS2020::decodeAvrcpEvent(uint8_t Event) {
  DBG_AVRCP(F("Decoded AVRCP event: "));
  switch (Event)
  {
    case AVRCP_EVENT_PLAYBACK_STATUS_CHANGED:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_PLAYBACK_STATUS_CHANGED"));
      break;
    case AVRCP_EVENT_TRACK_CHANGED:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_TRACK_CHANGED"));
      break;
    case AVRCP_EVENT_TRACK_REACHED_END:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_TRACK_REACHED_END"));
      break;
    case AVRCP_EVENT_TRACK_REACHED_START:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_TRACK_REACHED_START"));
      break;
    case AVRCP_EVENT_PLAYBACK_POS_CHANGED:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_PLAYBACK_POS_CHANGED"));
      break;
    case AVRCP_EVENT_BATT_STATUS_CHANGED:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_BATT_STATUS_CHANGED"));
      break;
    case AVRCP_EVENT_SYSTEM_STATUS_CHANGED:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_SYSTEM_STATUS_CHANGED"));
      break;
    case AVRCP_EVENT_PLAYER_APPLICATION_SETTING_CHANGED:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_PLAYER_APPLICATION_SETTING_CHANGED"));
      break;
    case AVRCP_EVENT_NOW_PLAYING_CONTENT_CHANGED:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_NOW_PLAYING_CONTENT_CHANGED"));
      break;
    case AVRCP_EVENT_AVAILABLE_PLAYERS_CHANGED:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_AVAILABLE_PLAYERS_CHANGED"));
      break;
    case AVRCP_EVENT_ADDRESSED_PLAYER_CHANGED:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_ADDRESSED_PLAYER_CHANGED"));
      break;
    case AVRCP_EVENT_UIDS_CHANGED:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_UIDS_CHANGED"));
      break;
    case AVRCP_EVENT_VOLUME_CHANGED:
      IS2020::DBG_AVRCP(F("AVRCP_EVENT_VOLUME_CHANGED"));
      break;
    default:
      DBG_AVRCP(F("Unknown: ")); DBG(String(Event, HEX));
  }
  DBG_AVRCP(F("\n"));
}

void IS2020::decodeAvrcpPlayerAtributes(uint8_t attribute) {
  /* player attributes */
  DBG_AVRCP(F("Decoded player attribute: "));
  switch (attribute)
  {
    case AVRCP_ATTRIBUTE_ILEGAL:
      DBG_AVRCP(F("AVRCP_ATTRIBUTE_ILEGAL"));
      break;
    case AVRCP_ATTRIBUTE_EQUALIZER:
      DBG_AVRCP(F("AVRCP_ATTRIBUTE_EQUALIZER"));
      break;
    case AVRCP_ATTRIBUTE_REPEAT_MODE:
      DBG_AVRCP(F("AVRCP_ATTRIBUTE_REPEAT_MODE"));
      break;
    case AVRCP_ATTRIBUTE_SHUFFLE:
      DBG_AVRCP(F("AVRCP_ATTRIBUTE_SHUFFLE"));
      break;
    case AVRCP_ATTRIBUTE_SCAN:
      DBG_AVRCP(F("AVRCP_ATTRIBUTE_SCAN"));
      break;
  }
  DBG_AVRCP(F("\n"));
}
