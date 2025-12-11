1# Write your MySQL query statement below
2Select lastName, firstName, city , state
3From Person left join Address
4on Person.personId = Address.personId;