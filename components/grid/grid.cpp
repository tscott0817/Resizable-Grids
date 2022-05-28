#include "grid.h"
#include <memory>
#include <vector>

Grid::Grid() {

}

void Grid::grid(double x, double y, double width, double height, double rowSize, double colSize) {

    int padding = 30;
    // Outer container;
    container.setCenter(x, y);
    // Size of container is relative to # of cells, margins, and size of cell
    //container.setSize(rowSize * scalarW + (newCell.getWidth()/2), colSize * scalarH + (newCell.getHeight()/2));
    //container.setSize(rowSize * scalarW, colSize * scalarH);
    //container.setSize(rowSize * scalarWS, colSize * scalarHS);
    container.setSize(width + padding, height + padding); // TODO: Don't hardcode container padding
    container.setColor(grey); // TODO: Make global param
    container.draw();

    scalarW = (width/rowSize);
    scalarH = (height/colSize);

    // Cell stuff
    newCell.setColor(black); // TODO: Make global param
    newCell.setSize(scalarW - 5, scalarH - 5);

    // Starts cell (0,0) at top left of container
    translateX = (container.getWidth()/2) - (newCell.getWidth()/2);
    translateY = (container.getHeight()/2) - (newCell.getHeight()/2);

    // Offset for cells
    cellWidthMargin = 0;
    cellHeightMargin = 0;

    // Columns
    if (cells.size() < colSize) { // Build grid only if empty (at start of program)

        for (int i = 0; i < colSize; i++) {
            std::vector<Rect> temp;

            // Rows
            for (int j = 0; j < rowSize; j++) {

                // padding/2 cancels the difference of the corners; since cell (0,0) is at top left edge
                newCell.setCenter(((x + cellWidthMargin) - translateX) + padding/2, ((y + cellHeightMargin) - translateY) + padding/2);
                temp.push_back(newCell);
                cellWidthMargin += scalarW;
            }

            cells.push_back(temp);
            cellWidthMargin = 0; // Reset for next row
            cellHeightMargin += scalarH;
        }
    }
}

void Grid::setMarginVert(int margin) {
    marginVert = margin;
}
void Grid::setMarginHor(int margin) {
    marginHor = margin;
}

bool Grid::checkOverlap(int x, int y) {
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {

            // Check if mouse in area of a cell
            if (y > cells[i][j].getTopY() && y < cells[i][j].getBottomY()
                && x > cells[i][j].getLeftX() && x < cells[i][j].getRightX()) {

                // Hold cell at current mouse pos for interactions
                column = i;
                row = j;
                return true;
            }
        }
    }
    return false;
}

void Grid::hoverColor() {
    cells[column][row].setColor(purple);
}

// TODO: Remove hardcoded values
void Grid::hoverCompress() {
    cells[column][row].setSize(scalarW/1.05, scalarH/1.05); // Denom = value to shrink cell by
}

// Stops every event at once
void Grid::releaseAll() {
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j].setColor(black);
            cells[i][j].setSize(scalarW, scalarH);
        }
    }
}

// Don't release if you want the cell to stay the color it changed to
void Grid::releaseColor() {
    cells[column][row].setColor(black);
}

void Grid::releaseCompress() {
    cells[column][row].setSize(scalarW, scalarH);
}

void Grid::draw() {
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j].draw();
        }
    }
}

