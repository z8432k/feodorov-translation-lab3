# Методы трансляции. ЛР №3

[![Build Status](https://travis-ci.org/z8432k/feodorov-translation-lab3.svg?branch=master)](https://travis-ci.org/z8432k/feodorov-translation-lab3)

Вариант №8

## Нисходящая трансляция методом рекурсивного спуска

LL(1) разбор

### Задание

Вынесение общего множителя за скобки

```ebnf
<S> ::= <E>
<E> ::= <T> <G>
<G> ::= <T> <G> | e
<T> ::= <F> <H>
<H> ::= * <F> <H> | e
<F> ::= k | m | n
```
