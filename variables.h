//#include <QObject>
#ifndef VARIABLES_H
#define VARIABLES_H

/* 协议状态标识 */
#define Frame_right         0xa0
#define Frame_wrong         0xa1
#define CheckSum_failed     0xa2
#define Unsupport_OT        0xa3
#define Unsupport_DL        0xa4
#define Unsupport_OB        0xa5
#define DataError           0xa6

//0帧头-1版本-2发送-3接收-4链路-5区域-6路口高-7路口低-8操作-9对象-10保留-*数据*-校验-帧尾
//通讯协议数据定义
#define frame_head  0xC0
#define frame_tail  0xC0
#define frame_ver   0x20
#define ID_PC       0x20
#define ID_TSC      0x10

//data link code 数据链路码
#define DL_Com              0x01
#define DL_BasicInfo        0x02
#define DL_CharacPar        0x03
#define DL_Intervention     0x04

//Operation type操作类型
#define OT                  0x80
#define OT_Query            0x80
#define OT_Set              0x81
#define OT_InitiativeReport 0x82
#define OT_QueryAnswer      0x83
#define OT_SetAnswer        0x84
#define OT_ErrorAnswer      0x85

//Object对象标识
#define O_Linking         0x01
#define O_TrafficFlow     0x02
#define O_WorkState       0x03
#define O_SignalState     0x04
#define O_CurrentTime     0x05
#define O_Channel         0x06
#define O_Phase           0x07
#define O_Pattern         0x08
#define O_Schedule        0x09
#define O_WorkMode        0x0a
#define O_Error           0x0b
#define O_Version         0x0c
#define O_CharacParVer    0x0d
#define O_IDCODE          0x0e
#define O_RemoteControl   0x0f
#define O_Vehdet          0x10
#define O_Plan            0x11
#define O_Action          0x12
#define O_Sequence        0x13
#define O_Split           0x14
#define O_Unit            0x15
#define O_Coord           0x16
#define O_Overlap         0x17
#define O_Peddet          0x18

#define O_PeddetState     0x28

#define O_Alarm           0xA0
#define O_BasicInfo       0xBD
#define O_DeviceInfo      0xBE
#define O_Call            0xBF  //不超过0xC0


#define TypeAlarm_Light         0x10
#define TypeAlarm_Detetor       0x30
#define TypeAlarm_Device        0x40
#define TypeAlarm_Environment   0x60

#define DoorState       0x70




//O_RemoteControl远程控制 指令码
#define Restart         0x24
#define Shutdown        0x25
#define ExtendTime      0x26
#define ClearError      0x27
#define Manual_auto     0x30//恢复自动
#define Manual_start    0x31//手控开始

//手控模式
#define Manual_NONE             0x00
#define Manual_yellowflash      0x30//
#define Manual_allred           0x31
#define Manual_lampoff          0x32
#define Manual_nextphase        0x33
#define Manual_appoint          0x34

//手控指定放行 方位码
#define MANUAL_POS_Other       ((uint8_t)0x00)     //其他
#define MANUAL_POS_East        ((uint8_t)0x01)     //东
#define MANUAL_POS_South       ((uint8_t)0x02)     //南
#define MANUAL_POS_West        ((uint8_t)0x04)     //西
#define MANUAL_POS_North       ((uint8_t)0x08)     //北
#define MANUAL_POS_NorthEast   ((uint8_t)0x10)     //东北
#define MANUAL_POS_SouthEast   ((uint8_t)0x20)     //东南
#define MANUAL_POS_SouthWest   ((uint8_t)0x40)     //西南
#define MANUAL_POS_NorthWest   ((uint8_t)0x80)     //西北

//手控指定放行 方向码
#define MANUAL_DIR_Other       ((uint8_t)0x00)     //其他
#define MANUAL_DIR_Left        ((uint8_t)0x01)     //左转
#define MANUAL_DIR_Straight    ((uint8_t)0x02)     //直行
#define MANUAL_DIR_Right       ((uint8_t)0x04)     //右转
#define MANUAL_DIR_Pedestrian  ((uint8_t)0x08)     //人行
#define MANUAL_DIR_Turn        ((uint8_t)0x10)     //掉头
#define MANUAL_DIR_Bicycle     ((uint8_t)0x20)     //自行车


//保留字数据
#define Reserve_Data      0x01


#define TimePar         0x0001
#define SchedulePar     0x0002
#define PlanPar         0x0004
#define ActionPar       0x0008
#define PatternPar      0x0010
#define SplitPar        0x0020
#define SequencePar     0x0040
#define PhasePar        0x0080
#define ChannelPar      0x0100
#define UnitPar         0x0200
#define CoordPar        0x0400
#define OverlapPar      0x0800
#define DevicePar       0x1000
#define BasicPar        0x2000
#define PeddetPar       0x4000
#define VehdetPar       0x8000
#define AllPar          0x00003FFF  //0x00007FFF



#endif // VARIABLES_H
