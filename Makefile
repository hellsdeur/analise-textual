.PHONY: run wrun

run:
	cd src/ && g++ -std=c++17 main.cpp -o main -lstdc++fs && ./main
	@echo "Finalizado"

wrun:
	cd src/ && g++ -std=c++17 main.cpp -o main && main.exe
	@echo "Finalizado"

clean:
	rm -rf resultados