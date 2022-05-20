#include "grid.h"
#include <memory>
#include <vector>

Grid::Grid() {

}

void Grid::grid(double x, double y, double width, double height) {

    gridWidth = 8; // # Columns
    gridHeight = 7; // # Rows

    // Outer container
    container.setCenter(x, y);
    container.setSize(width, height);
    container.setColor(grey);
    container.draw();

    // Offset for cells
    cellWidthPos = 0;
    cellHeightPos = 0;

    // To resize
    translateX = width/2.5;
    translateY = height/2.55;
    scalarW = width/9.6;
    scalarH = height/9;
    scalarWS = width/8.7; // Width spacing between each cell
    scalarHS = height/7.7; // Height spacing between each cell

    // Columns
    if (cells.size() < gridHeight) { // Build grid only if empty (at start of program)

        for (int i = 0; i < gridHeight; i++) {

            Rect newCell;
            std::vector<Rect> temp;

            // Rows
            for (int j = 0; j < gridWidth; j++) {

                newCell.setColor(black); // TODO: Make global param
                newCell.setSize(scalarW, scalarH);
                newCell.setCenter((x + cellWidthPos) - translateX, (y + cellHeightPos) - translateY);
                temp.push_back(newCell);
                cellWidthPos += scalarWS;
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
            if (y > cells[i][j].getTopY() && y < cells[i][j].getBottomY() && x > cells[i][j].getLeftX() &&
                x < cells[i][j].getRightX()) {

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
    cells[column][row].setSize(scalarW/1.05, scalarH/1.05);
}

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
};

void Grid::setKey(std::string key){
    keyLabel = key;
}

std::string Grid::getKey() {
    return keyLabel;
}

void Grid::draw() {

//    int i = 0;
//    Scales scales;
//    std::vector<std::string> scale = scales.buildScale('A'); // Need to get key as variable
//    for (const std::vector<Rect> &vec: cells) {
//        keyLabel = scale[i];
//        for (Rect rect: vec) {
//
//            // Draw cells first
//            rect.draw();
//
//            // Center text on ui elements and draw on top of cells
//            glRasterPos2i(rect.getLeftX() + 25, rect.getTopY() + 35);
//            glColor3f(1, 1, 1);
//            for (const char &letter : keyLabel) {
//                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
//            }
//        }
//        i += 1;
//    }

    for (int i = 0; i < cells.size(); i++) {

        for (int j = 0; j < cells[i].size(); j++) {
            // Draw cells
            cells[i][j].draw();
            }
    }
}

