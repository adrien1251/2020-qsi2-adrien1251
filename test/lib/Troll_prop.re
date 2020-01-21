open Framework;
open QCheckRely;
open Generator.Fantasy;
open Lib.Troll;

let {describe} = extendDescribe(QCheckRely.Matchers.matchers);

describe("Troll Invariance", ({test}) => {
  test("Troll score should be 0 when all elves resurrected", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="Troll score should be 0 when all elves resurrected",
      troll_arbitrary,
      troll =>
      all_elves_resurrected(troll) |> scoring == 0
    )
    |> expect.ext.qCheckTest;
    ();
  });
  test("Troll score should always be >= 0", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="Troll value should always be positive",
      troll_arbitrary,
      troll => scoring(troll) >= 0
    )
    |> expect.ext.qCheckTest;
    ()
  });
});

describe("Troll Inverse", ({test}) => {
  test("oops_he_survived should always be inverse of i_got_one", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="Oops_he_survived should always be inverse of i_got_one",
      troll_elf_arbitrary,
      (troll, elf) => {
        let faeor = elf;
        let troll_before_score = scoring(troll);
        let troll_after_score = i_got_one(faeor, troll) |> oops_he_survived(faeor) |> scoring;
        troll_before_score == troll_after_score;
      }
    )
    |> expect.ext.qCheckTest;
    ()
  })
});

describe("Troll Analogy", ({test}) => {
  test("i_got_one and i_got should be consistent", ({expect}) => {
    /* Test go there */
    ()
  })
});

describe("Troll Idempotence", ({test}) => {
  test(
    "all_elves_of_a_kind_resurrected brings the Troll killing list to a stable state",
    ({expect}) => {
    /* Test go there */
    ()
  })
});