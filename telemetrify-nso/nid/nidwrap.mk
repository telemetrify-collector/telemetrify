
%:
	docker run -it --rm -v $(pwd):/src --net=container:$(CNT_PREFIX)-nso --volumes-from $(CNT_PREFIX)-nso $(NSO_IMAGE_PATH)cisco-nso-dev:$(NSO_VERSION) make -C /src $*

