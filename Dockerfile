FROM rockylinux:9

EXPOSE 80

RUN dnf update -y && \
    dnf install -y httpd python3-mod_wsgi python3-webpy


COPY httpd-foreground /usr/local/bin/

CMD ["httpd-foreground"]