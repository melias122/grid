#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "PGA/Migrator.h"

//
// Migracne schemy (Topologie)
//

using topology_func = bool(Migrator &, int);

/*
 * Topologia ~b
 */
bool grid(Migrator &m, int size)
{
    switch (size) {
    case 11:
        /*
         *   0 - 1 - 2 - 3
         *   |   |   |   |
         *   4 - 5 - 6 - 7
         *   |   |   |
         *   8 - 9 - 10
         */
        m.addMigration(0, 1, Migration::Type::Best, 1);
        m.addMigration(0, 4, Migration::Type::Best, 1);

        m.addMigration(1, 0, Migration::Type::Best, 1);
        m.addMigration(1, 2, Migration::Type::Best, 1);
        m.addMigration(1, 5, Migration::Type::Best, 1);

        m.addMigration(2, 1, Migration::Type::Best, 1);
        m.addMigration(2, 3, Migration::Type::Best, 1);
        m.addMigration(2, 6, Migration::Type::Best, 1);

        m.addMigration(3, 2, Migration::Type::Best, 1);
        m.addMigration(3, 7, Migration::Type::Best, 1);

        m.addMigration(4, 0, Migration::Type::Best, 1);
        m.addMigration(4, 5, Migration::Type::Best, 1);
        m.addMigration(4, 8, Migration::Type::Best, 1);

        m.addMigration(5, 1, Migration::Type::Best, 1);
        m.addMigration(5, 4, Migration::Type::Best, 1);
        m.addMigration(5, 6, Migration::Type::Best, 1);
        m.addMigration(5, 9, Migration::Type::Best, 1);

        m.addMigration(6, 2, Migration::Type::Best, 1);
        m.addMigration(6, 5, Migration::Type::Best, 1);
        m.addMigration(6, 7, Migration::Type::Best, 1);
        m.addMigration(6, 10, Migration::Type::Best, 1);

        m.addMigration(7, 3, Migration::Type::Best, 1);
        m.addMigration(7, 6, Migration::Type::Best, 1);

        m.addMigration(8, 4, Migration::Type::Best, 1);
        m.addMigration(8, 9, Migration::Type::Best, 1);

        m.addMigration(9, 5, Migration::Type::Best, 1);
        m.addMigration(9, 8, Migration::Type::Best, 1);
        m.addMigration(9, 10, Migration::Type::Best, 1);

        m.addMigration(10, 6, Migration::Type::Best, 1);
        m.addMigration(10, 9, Migration::Type::Best, 1);

        break;
    case 5:
        /*
         *    0   -   1
         *    | \   / |
         *    |   2   |
         *    | /   \ |
         *    3   -   4
         */
        m.addMigration(0, 3, Migration::Type::Best, 1);
        m.addMigration(3, 0, Migration::Type::Best, 1);

        m.addMigration(3, 2, Migration::Type::Best, 1);
        m.addMigration(2, 3, Migration::Type::Best, 1);

        m.addMigration(3, 4, Migration::Type::Best, 1);
        m.addMigration(4, 3, Migration::Type::Best, 1);

        m.addMigration(4, 2, Migration::Type::Best, 1);
        m.addMigration(2, 4, Migration::Type::Best, 1);

        m.addMigration(4, 1, Migration::Type::Best, 1);
        m.addMigration(1, 4, Migration::Type::Best, 1);

    // fallthrough
    case 3:
        /*
         * 0  -  1
         *  \   /
         *    2
         */
        m.addMigration(0, 1, Migration::Type::Best, 1);
        m.addMigration(1, 0, Migration::Type::Best, 1);

        m.addMigration(1, 2, Migration::Type::Best, 1);
        m.addMigration(2, 1, Migration::Type::Best, 1);

        m.addMigration(2, 0, Migration::Type::Best, 1);
        m.addMigration(0, 2, Migration::Type::Best, 1);

        break;

    default:
        return false;
    }

    return true;
}

/*
 *   0 -> 1
 *   ^    |
 *   |    .
 *   3 <- 2
 *
 *   Topologia d
 */
bool ring(Migrator &m, int size)
{
    if (size < 2) {
        return false;
    }

    for (int i = 0; i < size; i++) {
        m.addMigration(i, (i + 1) % size, Migration::Type::Best, 1);
    }

    return true;
}

/*
 *      0
 *      ^
 *    / | \
 *   1  3  5
 *   ^  ^  ^
 *   |  |  |
 *   2  4  6
 *
 *   Topologia e
 */
bool tree(Migrator &m, int size)
{
    if (((size % 2) == 0) || size < 3) {
        return false;
    }

    for (int i = 0; i < size - 2; i += 2) {
        m.addMigration(i + 1, 0, Migration::Type::Best, 1);
        m.addMigration(i + 2, i + 1, Migration::Type::Best, 1);
    }

    return true;
}

/*
 *           0
 *           ^
 *       /   |   \
 *     1     3     5
 *    ^      ^      ^
 *   |   x   x   x   |
 *   2       4       6
 *
 *   Topologia f
 */
bool tree2(Migrator &m, int size)
{
    if (((size % 2) == 0) || size <= 3) {
        return false;
    }

    for (int i = 0; i <= size - 2; i += 2) {
        m.addMigration(i + 1, 0, Migration::Type::Best, 1);
        for (int j = 1; j <= size - 2; j += 2) {
            m.addMigration(i + 2, j, Migration::Type::Best, 1);
        }
    }

    return true;
}

#endif
