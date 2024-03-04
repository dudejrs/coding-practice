package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*
import kotlin.collections.*


fun parseTime(time: String): Int {
	val tokens = time.split(":")
		.map(String::toInt)
	return tokens[0] * 60 + tokens[1]
}

data class Customer(val name: String, val arrivedAt: Int){
}

fun solve(booked: Array<List<String>>, unbooked: Array<List<String>>): List<String> {

	val bookedCustomers = ArrayDeque<Customer>()
	val unbookedCustomers = ArrayDeque<Customer>()

	bookedCustomers.addAll(booked.map{
		Customer(it[1], parseTime(it[0]))
	})

	unbookedCustomers.addAll(unbooked.map{
		Customer(it[1], parseTime(it[0]))
	})

	val ret = mutableListOf<String>()

	var currentTime = 0

	while (!bookedCustomers.isEmpty() && !unbookedCustomers.isEmpty()) {
		
		val bookedCustomer = bookedCustomers.first()
		val unbookedCustomer = unbookedCustomers.first()

		if (bookedCustomer.arrivedAt <= currentTime) {
			ret.add(bookedCustomer.name)
			bookedCustomers.removeFirst()
			currentTime += 10
			continue;
		}

		if (bookedCustomer.arrivedAt <= currentTime) {
			ret.add(unbookedCustomer.name)
			unbookedCustomers.removeFirst()
			currentTime += 10
			continue;
		}

		val c = if (bookedCustomer.arrivedAt <= unbookedCustomer.arrivedAt)
			bookedCustomers.removeFirst() 
		else unbookedCustomers.removeFirst()

		ret.addLast(c.name)
		currentTime = c.arrivedAt + 10
	}

	if (bookedCustomers.isEmpty()) {
		ret.addAll(unbookedCustomers.map{it.name})
	} else if (unbookedCustomers.isEmpty()) {
		ret.addAll(bookedCustomers.map{it.name})
	}
	return ret
}

fun main() {
	val p = Paths.get(System.getProperty("user.dir") + "/data/상담예약제.txt")
	val reader = Files.newBufferedReader(p)

	repeat(reader.readLine().toInt()) {
		val numBooked = reader.readLine().toInt()
		val booked = IntRange(1, numBooked)
			.map{
				reader.readLine().split(" ")
			}
			.toTypedArray()
		val numUnbooked = reader.readLine().toInt()
		val unbooked = IntRange(1, numUnbooked)
			.map{
				reader.readLine().split(" ")
			}
			.toTypedArray()

		val answer = reader.readLine().split(" ")

		println("$answer ${solve(booked, unbooked)}")
	}
}