.PHONY: run

run:
	cd src/ && g++ -std=c++17 main.cpp -o main -lstdc++fs && ./main
	@echo "Finalizado"

clean:
	rm -rf resultados