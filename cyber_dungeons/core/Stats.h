#pragma once

#include "raylib.h"
#include <iostream>

struct Stats {
    int hp;
    int maxHp;
    int strength;
    bool isAlive;
    float damageCooldown;
    float damageDashTimer;
    float respawnCooldown;
    float respawnDashTimer;

    Stats(int hp, int maxHp, int strength, bool isAlive, float damageCooldown, float damageDashTimer, float respawnCooldown, float respawnDashTimer) :
        hp(hp), 
        maxHp(maxHp),
        strength(strength), 
        isAlive(isAlive), 
        damageCooldown(damageCooldown), 
        damageDashTimer(damageDashTimer), 
        respawnCooldown(respawnCooldown),
        respawnDashTimer(respawnDashTimer) {}

    void getDamaged(int damage)
    {
        if (damageDashTimer <= 0.0f && getIsAlive())
        { 
            hp = hp - damage;
            startDamageCooldown();
        }
    }

    void setHp(int value)
    {
        hp = value;
    }

    int getHp() const
    {
        return hp;
    }

    int getMaxHp() const
    {
        return maxHp;
    }

    int getStrength() const
    {
        return strength;
    }

    void startDamageCooldown()
    {
        damageDashTimer = damageCooldown;
    }

    void resetDamageDashTimer()
    {
        damageDashTimer = 0;
    }

    void decreaseDamageDashTimer()
    {
        if (damageDashTimer >= 0)
        {
            damageDashTimer -= GetFrameTime();
        }
    }

    float getDamageDashTimer() const
    {
        return damageDashTimer;
    }

    void die()
    {
        isAlive = false;
    }

    void setIsAlive(bool value)
    {
        isAlive = value;
    }

    bool getIsAlive() const
    {
        return isAlive;
    }

    void startRespawnCooldown()
    {
        respawnDashTimer = respawnCooldown;
    }

    void decreaseRespawnDashTimer()
    {
        if (respawnDashTimer >= 0 && !isAlive)
        {
            respawnDashTimer -= GetFrameTime();
        }
        //else if (respawnDashTimer <= 0 && !isAlive)
        //{
        //    respawn(maxHp);
        //}
    }

    float getRespawnDashTimer() const
    {
        return respawnDashTimer;
    }

    void respawn(int maxHp = 3)
    {
        isAlive = true;
        hp = maxHp;
    }

};
