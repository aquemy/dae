(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 1.41421)
         (= (citythreat city2) 100.01)
         (= (citythreat city3) 141.428)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 141.428)
         (= (timeTerre city1 city0) 141.428)
         (= (timeTerre city4 city1) 141.428)
         (= (timeTerre city1 city4) 141.428)
         
; city2
         (= (timeTerre city0 city2) 100.01)
         (= (timeTerre city2 city0) 100.01)
         (= (timeTerre city4 city2) 100.01)
         (= (timeTerre city2 city4) 100.01)
         
; city3
         (= (timeTerre city0 city3) 1.41421)
         (= (timeTerre city3 city0) 1.41421)
         (= (timeTerre city4 city3) 1.41421)
         (= (timeTerre city3 city4) 1.41421)
         
; plane init
         (at plane1 city0)
         (at plane2 city0)
         (libre plane1)
         (libre plane2)
         
; person init
         (at person1 city0)
         (at person2 city0)
         (at person3 city0)
         (at person4 city0)
         (at person5 city0)
         (at person6 city0)
         
)
(:goal (and 
         (at person1 city4)
         (at person2 city4)
         (at person3 city4)
         (at person4 city4)
         (at person5 city4)
         (at person6 city4)
         ))
  (:metric (and (minimize (total-time)) (minimize (total-cost)))))

; Pareto points : Makespan - Cost
; 1414.28 14.1421
; 1331.45 211.334
; 1134.26 294.171
; 1051.42 491.362
; 854.227 574.199
; 771.391 771.391
; 574.199 854.227
; 491.362 1051.42
; 294.171 1134.26
; 211.334 1331.45
; 211.334 1372.87
; 14.1421 1414.28
