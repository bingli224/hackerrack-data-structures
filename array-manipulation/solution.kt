import java.io.*
import java.math.*
import java.security.*
import java.text.*
import java.util.*
import java.util.concurrent.*
import java.util.function.*
import java.util.regex.*
import java.util.stream.*
import kotlin.collections.*
import kotlin.comparisons.*
import kotlin.io.*
import kotlin.jvm.*
import kotlin.jvm.functions.*
import kotlin.jvm.internal.*
import kotlin.ranges.*
import kotlin.sequences.*
import kotlin.text.*

// Complete the arrayManipulation function below.
/**
 * By BingLi224
 * 02/2019
 */
fun arrayManipulation(n: Int, queries: Array<Array<Int>>): Long {
    var row = LongArray ( n )

    queries.forEach { q ->
        val add = q [ 2 ].toLong ( )
        val down = q [ 1 ]
        row [ q [ 0 ] - 1 ] += add
        if ( down < n )
            row [ down ] -= add
    }

    var max = 0L
    var sum = 0L
    for ( r in row ) {
        sum += r
        if ( max < sum )
            max = sum
    }

    return max
}

fun main(args: Array<String>) {
    val scan = Scanner(System.`in`)

    val nm = scan.nextLine().split(" ")

    val n = nm[0].trim().toInt()

    val m = nm[1].trim().toInt()

    val queries = Array<Array<Int>>(m, { Array<Int>(3, { 0 }) })

    for (i in 0 until m) {
        queries[i] = scan.nextLine().split(" ").map{ it.trim().toInt() }.toTypedArray()
    }

    val result = arrayManipulation(n, queries)

    println(result)
}
