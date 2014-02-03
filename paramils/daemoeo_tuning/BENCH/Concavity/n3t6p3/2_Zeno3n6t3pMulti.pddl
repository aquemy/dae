(define (problem MULTIZENO-A)
  (:domain  multi-zeno-travel)
  (:objects plane1 plane2 plane3 - aircraft
            person1 person2 person3 person4 person5 person6 - person
            city0 city1 city2 city3 city4 - city)
  (:init (= (total-cost) 0)
         (= (citythreat city0) 0)
         (= (citythreat city1) 50)
         (= (citythreat city2) 91.4214)
         (= (citythreat city3) 123.205)
         (= (citythreat city4) 0)
         
; city1
         (= (timeTerre city0 city1) 123.205)
         (= (timeTerre city1 city0) 123.205)
         (= (timeTerre city4 city1) 123.205)
         (= (timeTerre city1 city4) 123.205)
         
; city2
         (= (timeTerre city0 city2) 91.4214)
         (= (timeTerre city2 city0) 91.4214)
         (= (timeTerre city4 city2) 91.4214)
         (= (timeTerre city2 city4) 91.4214)
         
; city3
         (= (timeTerre city0 city3) 50)
         (= (timeTerre city3 city0) 50)
         (= (timeTerre city4 city3) 50)
         (= (timeTerre city3 city4) 50)
         
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
; 739.23 450
; 675.663 574.264
; 592.82 669.615
; 546.41 784.242
; 529.253 793.879
; 446.41 889.23
; 400 1003.86
; 382.843 1013.49
; 300 1108.85
