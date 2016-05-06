default: pull run

pull: 
	docker pull cs50/cli:ubuntu

run: 
	docker run -i --rm -v `pwd`/:/root -t cs50/cli:ubuntu
