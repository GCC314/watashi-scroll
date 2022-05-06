#ifndef BLOCK_H
#define BLOCK_H

const int BLOCK_ID_NONE = 0;
const int BLOCK_ID_DIRT = 1;

#include <QGraphicsItem>

class Block : public QGraphicsItem
{
public:
    Block();
};

#endif // BLOCK_H
