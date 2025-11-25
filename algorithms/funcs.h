//
// Created by ivanefremov on 24.11.2025.
//

#ifndef C_PROJECTS_FUNCS_H
#define C_PROJECTS_FUNCS_H

#define C_PROJECTS_SWAP(x, y, T) do \
    { T swm_temp = (x); \
    (x) = (y); \
    (y) = swm_temp; \
    } while (0)

#endif //C_PROJECTS_FUNCS_H