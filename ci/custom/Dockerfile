ARG FROM_IMAGE
FROM $FROM_IMAGE

RUN rm -rf /var/lib/apt/lists/* /var/cache/apt/* /usr/share/man/*

RUN useradd -r -U app -d /srv/app -m
USER app:app

COPY ./run.sh /srv/app/run.sh
COPY ./build /srv/app/build
COPY ./external /srv/app/external

WORKDIR /srv/app
ENTRYPOINT ["./run.sh"]
CMD ["release"]
