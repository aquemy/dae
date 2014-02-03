(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 - aircraft
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
; 1032.05 300
; 968.483 382.843
; 885.641 446.41
; 822.073 529.253
; 739.23 592.82
; 675.663 675.663
; 592.82 739.23
; 529.253 822.073
; 446.41 885.641
; 382.843 968.483
; 300 1032.05
