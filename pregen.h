#ifndef preMoveGen_H
#define preMoveGen_H


// 借助“位行”和“位列”生成车炮着法的预置结构
struct SlideMoveStruct {
  unsigned char NonCap[2];    // 不吃子能走到的最大一格/最小一格
  unsigned char RookCap[2];   // 车吃子能走到的最大一格/最小一格
  unsigned char CannonCap[2]; // 炮吃子能走到的最大一格/最小一格
  unsigned char SuperCap[2];  // 超级炮(隔两子吃子)能走到的最大一格/最小一格
}; // smv

// 借助“位行”和“位列”判断车炮着法合理性的预置结构
struct SlideMaskStruct {
  unsigned short NonCap, RookCap, CannonCap, SuperCap;
}; // sms

extern SlideMoveStruct _smvRankMoveTab[9][512];
extern SlideMoveStruct _smvFileMoveTab[10][1024];

extern SlideMaskStruct _smsRankMaskTab[9][512];   // 36,864 字节
extern SlideMaskStruct _smsFileMaskTab[10][1024]; // 81,920 字节

extern uint16 _UpMask[256];            //当前的向上所有的F1111111
extern uint16 _LoMask[256];
extern uint16 _RightMask[256];
extern uint16 _LeftMask[256];
extern uint8  PreKingMove[256][8];
extern uint8  PreShiXiangAndEyeMove[256][16];           //包括相眼
extern uint8  PreMaAndLegMove[256][32];                 //包括马眼

extern uint8 _nBoardIndex[256];
//extern uint8  _GetDir[512];

extern uint8  _GetDir[256][256];
extern uint8  PreRPawnMove[256][4];                  //0,黑卒,1,红兵'
extern uint8  PreBPawnMove[256][4];                  //0,黑卒,1,红兵

extern void initPreGen(void);

extern uint64 Zobrist[BPAWN+1][256], ZobColour;

#endif