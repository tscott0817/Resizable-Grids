#include "grid.h"
#include <memory>
#include <vector>

Grid::Grid() {

}

void Grid::grid(double x, double y, double width, double height, double rowSize, double colSize) {

    // Outer container;
    container.setCenter(x, y);
    container.setSize(width - cellSize + containerPadding, height - cellSize + containerPadding);
    container.setColor(grey); // TODO: Make global param
    container.draw();

    // Scales cells relative to container
    scalarW = (width/rowSize);
    scalarH = (height/colSize);

    newCell.setColor(black); // TODO: Make global param
    newCell.setSize(scalarW - cellSize, scalarH - cellSize);

    // Positions cells in relation to container
    translateX = (container.getWidth()/2) - (newCell.getWidth()/2) - (containerPadding/2);
    translateY = (container.getHeight()/2) - (newCell.getHeight()/2) - (containerPadding/2);

    // Offset for cells; iterated by the scalars; needed so we start at 0 for first cell (since scalar already set and > 0)
    cellWidthMargin = 0;
    cellHeightMargin = 0;

    if (cells.size() < colSize) { // Build grid only if empty (at start of program)

        // Columns
        for (int i = 0; i < colSize; i++) {
            std::vector<Rect> temp; // Holds current cells

            // Rows
            for (int j = 0; j < rowSize; j++) {
                newCell.setCenter(x + cellWidthMargin - translateX, y + cellHeightMargin - translateY);
                temp.push_back(newCell);
                cellWidthMargin += scalarW;
            }

            cells.push_back(temp);
            cellWidthMargin = 0; // Reset for next row
            cellHeightMargin += scalarH;
        }
    }
}

void Grid::setCellSize(int size) {
    cellSize = size;
}

void Grid::setPadding(int padding) {
    containerPadding = padding;
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

