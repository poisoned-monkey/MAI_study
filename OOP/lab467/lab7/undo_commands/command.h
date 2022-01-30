#pragma once

struct command {
    virtual void undo() = 0;
    virtual ~command() = default;
};