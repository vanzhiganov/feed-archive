FROM rockylinux:9

RUN dnf update -y && dnf install -y httpd python3-webpy