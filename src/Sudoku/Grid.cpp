#include "Grid.hpp"


std::vector<int> Sudoku::Grid::values() const
{
  std::vector<int> values(_size[iGrid]);
  std::transform(_cells.cbegin(), _cells.cend(), values.begin(), [](Cell const& cell) { return cell.value(); });
  return values;
}


void Sudoku::Grid::assignMemberships()
{
  //   j 0   1   2
  // i +---+---+---+
  //   |   |   |   |
  // 0 |   |   |   |
  //   |   |   |   |
  //   +---+---+---+
  //   |   |   | * |	This marked cell is in block (1,2), subcell (0,1).
  // 1 |   |   |   |
  //   |   |   |   |
  //   +---+---+---+
  //   |   |   |   |
  // 2 |   |   |   |
  //   |   |   |   |
  //   +---+---+---+
  for (int i = 0; i < _size[iRank]; i++)	// (i,j) addresses blocks
    for (int j = 0; j < _size[iRank]; j++)
      for (int k = 0; k < _size[iRank]; k++)	// (k,l) addresses cells in a block
        for (int l = 0; l < _size[iRank]; l++)
        {
          int cell_row = _size[iRank] * i + k;
          int cell_col = _size[iRank] * j + l;

          Cell& cell = _cells[_size[iBlock] * cell_row + cell_col];
          Slice& row = _rows[cell_row];
          Slice& column = _columns[cell_col];
          Slice& block = _blocks[_size[iRank] * i + j];

          cell.assignMembership(Row, row);
          cell.assignMembership(Column, column);
          cell.assignMembership(Block, block);

          row.assignMember(cell_col, cell);
          column.assignMember(cell_row, cell);
          block.assignMember(_size[iRank] * k + l, cell);
        }
}
