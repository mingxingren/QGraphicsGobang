#ifndef CGAMELOGIC_H
#define CGAMELOGIC_H

#include <utility>

/**
 * @brief The CGameLogic class 用于五子棋的逻辑
 */
class CGameLogic
{
public:
    enum ePieceType
    {
        EPIECETYPE_EMPTY,   ///< 未落子
        EPIECETYPE_BLACK,   ///< 黑子
        EPIECETYPE_WHITE,   ///< 白子
    };

    struct TCoordinate
    {
        int _iRow = 0;
        int _iColumn = 0;
    };

public:
    CGameLogic();

    bool IsEmptyPosition(int _iRow, int _iColumn);
    bool NextStep(int _iRow, int _iColumn);

private:
    bool _IsVictory(int _iCurRow, int _iCurColumn);
    void _HorizontalSamplePieceType(int _iNextRow, int _iNextColumn, ePieceType _eType, int _iNextStep, int &_iCount);
    void _VerticalSamplePieceType(int _iNextRow, int _iNextColumn, ePieceType _eType, int _iNextStep, int &_iCount);
    void _HVSamplePieceType(int _iNextRow, int _iNextColumn, ePieceType _eType,
                            int _iNextRowStep, int _iNextColumnStep, int &_iCount);

private:
    ePieceType m_ePieceTypePostion[15][15];     ///< 用于描述棋子的位置
    ePieceType m_eCurrentPieceType = EPIECETYPE_EMPTY;     ///< 当前棋子类型
};

#endif // CGAMELOGIC_H
