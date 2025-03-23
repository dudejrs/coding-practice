plugins {
    `java-library`
    id("application")
    id("com.diffplug.spotless").version("6.19.0")
}

repositories {
    mavenCentral()
    gradlePluginPortal() 
}

dependencies {
    testImplementation(libs.junit.junit)
}

group = "com.example."
version = "1.0-SNAPSHOT"
description = "java"
java.sourceCompatibility = JavaVersion.VERSION_17

tasks.withType<JavaCompile>() {
    options.encoding = "UTF-8"
}

spotless {
    java {
        target("src/**/*.java") 
        googleJavaFormat()      
        removeUnusedImports()   
        trimTrailingWhitespace() 
        indentWithSpaces(4)
        endWithNewline()
    }
}        