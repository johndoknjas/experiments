export class Test {

  private readonly predicate = () => true;

  private readonly func1 = (param1: boolean, param2: boolean): boolean =>
    this.predicate() &&
    (this.predicate() || this.predicate());

  private readonly func2 = (
    param1: boolean,
    param2: boolean
  ): boolean =>
    this.predicate() &&
    (this.predicate() || this.predicate());
}
