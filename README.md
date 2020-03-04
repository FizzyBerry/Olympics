This program simulates fights between gladiators at Olympics. Gladiator can be human, beast or half human half beast (berserker). Gladiators are fighting between each other solo or in squads. After the battle Cesar judges if the loser is going to die or not, depending on the total number of fights that have already taken place at Olympics. If this number is divisible by 3 they die if not cesar will let them live. Winners are gaining plus 2 points on their base damage and rapidity.
Each breed have diffrent statistics :
- Human : 
        MAX_HEALTH = 200
        BASE_DAMAGE = 30
        BASE_RAPIDITY = 10
        BASE_DEFENCE = 10
        *no special effects*
- Beast :
        MAX_HEALTH = 150
        BASE_DAMAGE = 40
        BASE_RAPIDITY = 20
        BASE_DEFENCE = 0
        *When health is under 25% BASE_DAMAGE is multiply by two*
- Berserker :
        MAX_HEALTH = 200
        BASE_DAMAGE = 35
        BASE_RAPIDITY = 5
        BASE_DEFENCE = 15
        *When health is under 25% BASE_DAMAGE is multiply by two and BASE_DEFENCE equals zero (becouse he is throwing away his shield)*
