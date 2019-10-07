#!/bin/bash

TRAVIS_GEN_SCRIPT=".travis_gen.py"
DOCKER_GENERATED_PATH="tests/bombler.Dockerfile"
DOCKERFILE_ORIGIN="Dockerfile"

CONTENT_BASE_DOCKERFILE=$(cat ${DOCKERFILE_ORIGIN})
TRAVIS_GEN_OUT=$(python3 ${TRAVIS_GEN_SCRIPT} test)
TRAVIS_GEN_DEPS=$(echo "$TRAVIS_GEN_OUT" | head -n 1)
TRAVIS_GEN_CMDS=$(echo "$TRAVIS_GEN_OUT" | tail -n +2)

TEMPLATE_DOCKERFILE=$(cat <<EOF
BASE_DOCKERFILE

RUN \
		apt-get update \
	&&	apt-get install -y DEPS

RUN \
		git clone https://github.com/uncrustify/uncrustify.git /root/uncrustify \
	&&	mkdir /root/uncrustify/build \
	&&	(cd /root/uncrustify/build && cmake .. && make -j)

EOF
)

TEMPLATE_DOCKERFILE="${TEMPLATE_DOCKERFILE/BASE_DOCKERFILE/${CONTENT_BASE_DOCKERFILE}}"
TEMPLATE_DOCKERFILE="${TEMPLATE_DOCKERFILE/DEPS/${TRAVIS_GEN_DEPS}}"

echo "$TEMPLATE_DOCKERFILE" > "${DOCKER_GENERATED_PATH}"

docker build \
		--tag bombler \
		--file "${DOCKER_GENERATED_PATH}" \
		.

git submodule deinit --all
rm -rf venv
docker run \
		--rm \
		--detach \
		--workdir /code \
		--name bombler \
		bombler \
		tail -f /dev/null

docker cp "$(pwd)/." bombler:/code

docker exec -t bombler bash -c "rm -rf /code/uncrustify && ln -s /root/uncrustify /code/uncrustify"

echo "${TRAVIS_GEN_CMDS}" | while read -r line; do
	if echo "${line}" | grep uncrustify_check; then
		line="${line} UNCRUSTIFY=/root/uncrustify/build/uncrustify -o /root/uncrustify/build/uncrustify"
	fi
	docker exec -t bombler bash -c "(set -eux; ${line})"
	ret=$?
	# if [ "$ret" -ne 0 ]; then
	# 	break
	# fi
done

docker stop bombler
