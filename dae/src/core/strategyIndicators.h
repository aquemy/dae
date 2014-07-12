#ifndef __STRATEGIES_INDICATORS_H__
#define __STRATEGIES_INDICATORS_H__

// The lower the better

// Somme améliorations relatives
double deltaPlus(PlanningObjectiveVector& x, PlanningObjectiveVector& r)
{
    double res = 0;
    for(unsigned i = 0; i < x.size(); i++)
    {
        res -= (r[i] - x[i]);
        if(r[i] > 0)
            res /= r[i];  
    }
    return res;    
}

// Hypervolume entre les deux points, seulement sur les axes améliorés,
// i.e. pour un vecteur de dimension trois, avec une amélioration sur deux axes seulement,
// le résultat sera la surface donnée par la projection des améliorations sur ces deux axes.
// On favorise ainsi largement les améliorations sur le plus d'axes possibles.
double deltaProd(PlanningObjectiveVector& x, PlanningObjectiveVector& r)
{
    double res = 1;
    for(unsigned i = 0; i < x.size(); i++)
    {
        if(r[i] - x[i] > 0)
        {
            res *= (r[i] - x[i]); 
            if(r[i] > 0)
                res /= r[i];  
        }
    }         
    if(res == 1)
        return 0; // It means no improvement at all.
        
    return -res;    
}

// Norme 1 du vecteur x par rapport à l'origine (on suppose une minimisation).
double manhattan(PlanningObjectiveVector& x, PlanningObjectiveVector& r)
{
    (void)r;
    double res = 0;
    for(unsigned i = 0; i < x.size(); i++)
        res += x[i];   

    return res;
}

// Norme 2 du vecteur x par rapport à l'origine (on suppose une minimisation).
double euclidian(PlanningObjectiveVector& x, PlanningObjectiveVector& r)
{
    (void)r;
    double res = 0;
    for(unsigned i = 0; i < x.size(); i++)
        res += x[i]*x[i];   

    return std::sqrt(res);
}

// Hypervolume from the origin
double surfaceToOrigin(PlanningObjectiveVector& x, PlanningObjectiveVector& r)
{
    (void)r;
    double res = 1;
    for(unsigned i = 0; i < x.size(); i++)
        res *= x[i];
        
    return res;
}

double f(PlanningObjectiveVector& x, PlanningObjectiveVector& r)
{
    return surfaceToOrigin(x,r) + deltaProd(x,r);
}

#endif // __STRATEGIES_H__
