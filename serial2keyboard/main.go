package main

import (
	"serial2keyboard/serialdata_parser"
)

func main() {
	// keyboard_emulation.Emulate()
	serialdata_parser.InitPort("/dev/ttyUSB0")
}