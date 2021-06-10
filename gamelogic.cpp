#include "gamelogic.h"

#include <QDebug>

CGameLogic::CGameLogic()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            m_ePieceTypePostion[i][j] = EPIECETYPE_EMPTY;
        }
    }
}

bool CGameLogic::IsEmptyPosition(int _iRow, int _iColumn)
{
    if (_iRow < 15 && _iColumn < 15)
    {
        return m_ePieceTypePostion[_iRow][_iColumn] == EPIECETYPE_EMPTY;
    }
    else {
        return false;
    }
}

bool CGameLogic::NextStep(int _iRow, int _iColumn)
{
    if (_iRow < 15 && _iColumn < 15)
    {
        switch (m_eCurrentPieceType)
        {
        case EPIECETYPE_EMPTY:
            m_ePieceTypePostion[_iRow][_iColumn] = EPIECETYPE_BLACK;
            break;
        case EPIECETYPE_BLACK:
            m_ePieceTypePostion[_iRow][_iColumn] = EPIECETYPE_WHITE;
            break;
        case EPIECETYPE_WHITE:
            m_ePieceTypePostion[_iRow][_iColumn] = EPIECETYPE_BLACK;
            break;
        default:
            break;
        }
        m_eCurrentPieceType = m_ePieceTypePostion[_iRow][_iColumn];
        _IsVictory(_iRow, _iColumn);
        return true;
    }
    return false;
}

bool CGameLogic::_IsVictory(int _iCurRow, int _iCurColumn)
{
    int iCount = 0;
    _HorizontalSamplePieceType(_iCurRow, _iCurColumn, m_eCurrentPieceType, 1, iCount);
    _HorizontalSamplePieceType(_iCurRow, _iCurColumn, m_eCurrentPieceType, -1, iCount);
    --iCount;
    if (iCount >= 5)
    {
        goto line_result;
    }

    iCount = 0;
    _VerticalSamplePieceType(_iCurRow, _iCurColumn, m_eCurrentPieceType, 1, iCount);
    _VerticalSamplePieceType(_iCurRow, _iCurColumn, m_eCurrentPieceType, -1, iCount);
    --iCount;
    if (iCount >= 5)
    {
        goto line_result;
    }

    iCount = 0;
    _HVSamplePieceType(_iCurRow, _iCurColumn, m_eCurrentPieceType, 1, 1, iCount);
    _HVSamplePieceType(_iCurRow, _iCurColumn, m_eCurrentPieceType, -1, -1, iCount);
    --iCount;
    if (iCount >= 5)
    {
        goto line_result;
    }

    iCount = 0;
    _HVSamplePieceType(_iCurRow, _iCurColumn, m_eCurrentPieceType, 1, -1, iCount);
    _HVSamplePieceType(_iCurRow, _iCurColumn, m_eCurrentPieceType, -1, 1, iCount);
    --iCount;
    if (iCount >= 5)
    {
        goto line_result;
    }

line_result:
    if (iCount >= 5)
    {
        qDebug() << ((m_eCurrentPieceType == EPIECETYPE_BLACK) ? "黑棋胜利" : "白棋胜利");
    }
}

void CGameLogic::_HorizontalSamplePieceType(int _iNextRow, int _iNextColumn, ePieceType _eType, int _iNextStep, int &_iCount)
{
    if (_iNextRow > 0 && _iNextRow < 15 && _iNextColumn > 0 && _iNextColumn < 15)
    {
        if (m_ePieceTypePostion[_iNextRow][_iNextColumn] == _eType)
        {
            _iCount++;
            _HorizontalSamplePieceType(_iNextRow + _iNextStep, _iNextColumn, _eType, _iNextStep, _iCount);
        }
        return;
    }
    return;
}

void CGameLogic::_VerticalSamplePieceType(int _iNextRow, int _iNextColumn, ePieceType _eType, int _iNextStep, int &_iCount)
{
    if (_iNextRow > 0 && _iNextRow < 15 && _iNextColumn > 0 && _iNextColumn < 15)
    {
        if (m_ePieceTypePostion[_iNextRow][_iNextColumn] == _eType)
        {
            _iCount++;
            _VerticalSamplePieceType(_iNextRow, _iNextColumn+ _iNextStep, _eType, _iNextStep, _iCount);
        }
        return;
    }
    return;
}

void CGameLogic::_HVSamplePieceType(int _iNextRow, int _iNextColumn, ePieceType _eType, int _iNextRowStep, int _iNextColumnStep, int &_iCount)
{
    if (_iNextRow > 0 && _iNextRow < 15 && _iNextColumn > 0 && _iNextColumn < 15)
    {
        if (m_ePieceTypePostion[_iNextRow][_iNextColumn] == _eType)
        {
            _iCount++;
            _HVSamplePieceType(_iNextRow + _iNextRowStep, _iNextColumn+ _iNextColumnStep, _eType,
                               _iNextRowStep, _iNextColumnStep, _iCount);
        }
        return;
    }
    return;
}
