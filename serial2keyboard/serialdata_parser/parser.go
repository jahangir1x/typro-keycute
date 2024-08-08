package serialdata_parser

import (
	"fmt"
	"log"
	"strings"
	"time"

	"go.bug.st/serial"
)

func InitPort(devicePath string) serial.Port {
	mode := &serial.Mode{
		BaudRate: 9600,
	}
	port, err := serial.Open(devicePath, mode)
	if err != nil {
		log.Fatal(err)
	}

	return port
}

func Parse(port serial.Port) {
	defer port.Close()

	buf := make([]byte, 1000)

	for {
		dataLength, err := port.Read(buf)
		if err != nil {
			log.Fatal(err)
		}

		data := string(buf[:dataLength])

		// split the data based on newlines
		lines := strings.Split(data, "\n")
		for _, line := range lines {
			fmt.Println(line)
		}

		_, err = port.Write([]byte("ACK\n"))
		if err != nil {
			log.Fatal(err)
		}

		time.Sleep(100 * time.Millisecond)
	}
}