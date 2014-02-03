(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 plane3 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 30)
         (= (citythreat city2) 71.4214)
         (= (citythreat city3) 103.205)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 103.205)
         (= (timeTerre city1 city0) 103.205)
         (= (timeTerre city4 city1) 103.205)
         (= (timeTerre city1 city4) 103.205)
         
; city2
         (= (timeTerre city0 city2) 71.4214)
         (= (timeTerre city2 city0) 71.4214)
         (= (timeTerre city4 city2) 71.4214)
         (= (timeTerre city2 city4) 71.4214)
         
; city3
         (= (timeTerre city0 city3) 30)
         (= (timeTerre city3 city0) 30)
         (= (timeTerre city4 city3) 30)
         (= (timeTerre city3 city4) 30)
         
; plane init
         (at plane1 city0)
         (at plane2 city0)
         (at plane3 city0)
         (libre plane1)
         (libre plane2)
         (libre plane3)
         
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
; 619.23 270
; 555.663 394.264
; 472.82 489.615
; 469.253 572.458
; 412.82 604.242
; 409.253 613.879
; 386.41 677.447
; 326.41 709.23
; 322.843 792.073
; 266.41 823.857
; 262.843 833.495
; 240 855.641
; 180 928.846
