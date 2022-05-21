#include "grid.h"
#include <memory>
#include <vector>

Grid::Grid() {

}

void Grid::grid(double x, double y, double width, double height, double rowSize, double colSize) {


    gridWidth = rowSize; // # Columns
    gridHeight = colSize; // # Rows

    // Amount of space in between cells (lower denom = more space)
    scalarWS = width/colSize;
    scalarHS = height/rowSize;

//    // Size of cells themselves (lower denom = smaller cells)
//    scalarW = width/colSize + 1.0;
//    scalarH = height/rowSize + 1.0;

    // Size of cells themselves (lower denom = smaller cells)
    scalarW = width/(colSize + 1.0);
    scalarH = height/(rowSize + 1.0);


    // Cell stuff
    newCell.setColor(black); // TODO: Make global param
    newCell.setSize(scalarW, scalarH);

    // Outer container
    container.setCenter(x, y);
    // Size of container is relative to # of cells, margins, and size of cell
    container.setSize(rowSize * scalarW + (newCell.getWidth()/2), colSize * scalarH + (newCell.getHeight()/2));
    //container.setSize(rowSize * scalarW, colSize * scalarH);
    //container.setSize(rowSize * scalarWS, colSize * scalarHS);
    container.setColor(grey); // TODO: Make global param
    container.draw();

    // Shifts grid relative to container
    translateX = (container.getWidth()/2) - (newCell.getWidth()/2);
    translateY = (container.getHeight()/2) - (newCell.getHeight()/2);

    // Offset for cells
    cellWidthPos = 0;
    cellHeightPos = 0;

    // Columns
    if (cells.size() < gridHeight) { // Build grid only if empty (at start of program)

        for (int i = 0; i < gridHeight; i++) {

            //Rect newCell;
            std::vector<Rect> temp;

            // Rows
            for (int j = 0; j < gridWidth; j++) {

                newCell.setCenter((x + cellWidthPos) - translateX, (y + cellHeightPos) - translateY);
                temp.push_back(newCell);
                cellWidthPos += scalarWS;
                //cellWidthPos += 60; // TODO: Not sure if want hardcoded; used scalarWS before
            }

            cells.push_back(temp);
            cellWidthPos = 0; // Reset for next row
            cellHeightPos += scalarHS;
        }
    }
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

