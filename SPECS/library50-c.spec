############################################################################
Summary: Simplifies user input for C.
Name: library50-c
Version: 5
Release: 0
License: BSD 3-Clause License
Group: Development/Libraries
Vendor: CS50
URL: https://manual.cs50.net/library/
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
Requires: binutils
Requires: clang
BuildArch: i386 x86_64
Conflicts: cs50-library-c


############################################################################
%define _srcdir /usr/src


############################################################################
# ensure library includes debuginfo
# http://lists.rpm.org/pipermail/rpm-list/2009-January/000127.html
%define debug_package %{nil}
%define __strip /bin/true


############################################################################
# ensure RPM is portable by avoiding rpmlib(FileDigests)
# http://lists.rpm.org/pipermail/rpm-list/2009-October/000401.html
%global _binary_filedigest_algorithm 1
%global _source_filedigest_algorithm 1


############################################################################
# ensure RPM is portable by avoiding rpmlib(PayloadIsXz)
# http://www.cmake.org/pipermail/cmake/2010-March/035580.html
%global _binary_payload w9.gzdio


############################################################################
%description
The CS50 Library for C is a suite of code designed to simplify user input.


############################################################################
%prep
rm -rf %{_builddir}/*
cp %{_sourcedir}/* %{_builddir}/


############################################################################
%build
clang -c -ggdb -std=c99 %{_builddir}/cs50.c -o %{_builddir}/cs50.o
ar rcs %{_builddir}/libcs50.a %{_builddir}/cs50.o


############################################################################
%install
rm -rf %{buildroot}
mkdir -p %{buildroot}%{_includedir}
mv %{_builddir}/cs50.h %{buildroot}%{_includedir}/
mkdir -p %{buildroot}%{_libdir}
mv %{_builddir}/libcs50.a %{buildroot}%{_libdir}/
mkdir -p %{buildroot}%{_srcdir}
mv %{_builddir}/cs50.c %{buildroot}%{_srcdir}/


############################################################################
%clean
rm -rf %{buildroot}


############################################################################
%files
%defattr(0644,root,root,0755)
%{_includedir}/*
%{_libdir}/*
%{_srcdir}/*
