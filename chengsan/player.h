//
//  player.h
//  chengsan
//
//  Created by Garnel Mao on 7/6/16.
//  Copyright © 2016 maogm12@gmail.com. All rights reserved.
//

#ifndef player_h
#define player_h

#include <random>
#include "utils.h"
#include "step.h"

class Player {
public:
    Player(bool first)
    :first(first), ai(false) {
        tag = first ? 1 : 2;
        opponentTag = first ? 2 : 1;
    }

    bool IsFirst() const {
        return first;
    }

    bool IsAI() const {
        return ai;
    }

    void SetAI() {
        ai = true;
    }

    int Tag() const {
        return tag;
    }

    Step Random(const Board& board, int round) {
        if (round < 9) {
            // place
            auto positions = board.FindEmpty();
            auto pos = Utils::random<size_t>(0, positions.size() - 1);
            if (board.CanMakeSan(tag, pos)) {
                // random eat a piece
                auto eatPositions = board.FindToEat(opponentTag);
                auto eatPos = Utils::random<size_t>(0, eatPositions.size() - 1);
                return Step::MakePlaceStep(tag, pos, eatPos);
            } else {
                return Step::MakePlaceStep(tag, pos);
            }
        } else {
            // move
            auto steps = board.FindMoveSteps(tag);
            auto chosen = steps[Utils::random<size_t>(0, steps.size() - 1)];
            if (board.CanMakeSan(tag, chosen.moveTo, chosen.moveFrom)) {
                // random eat a piece
                auto eatPositions = board.FindToEat(opponentTag);
                chosen.eatPos = Utils::random<size_t>(0, eatPositions.size() - 1);
            }
            return chosen;
        }
    }

private:
    bool first;
    bool ai;
    int tag;
    int opponentTag;
};

#endif /* player_h */